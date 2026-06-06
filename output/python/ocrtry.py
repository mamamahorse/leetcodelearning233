# process_rebus_pdfs.py
import os
# MUST set env vars BEFORE importing paddleocr/paddle related modules
os.environ["USE_PADDLEX"] = "0"                # disable paddlex usage (avoid inference.json mismatch)
os.environ["PADDLE_HOME"] = r"D:\paddle_home"  # change to a path without Chinese
os.environ["PPLINES_HOME"] = r"D:\paddle_home"

from pathlib import Path
import re
import time
from paddleocr import PaddleOCRVL

# -------------------- User config --------------------
INPUT_DIR = Path(r"E:\rebus")           # 你的 pdf 文件夹
OUTPUT_ROOT = Path(r"E:\rebus_output")  # 输出根目录
OUTPUT_ROOT.mkdir(parents=True, exist_ok=True)

# optional: logger simple
def log(*args):
    print(time.strftime("[%Y-%m-%d %H:%M:%S]"), *args)

# -------------------- helper funcs --------------------
def clean_filename(s, max_len=100):
    # remove illegal chars and trim
    s = re.sub(r'[\\/:*?"<>|]', '', s)
    s = re.sub(r'\s+', '_', s.strip())
    if len(s) > max_len:
        s = s[:max_len]
    return s or "unknown"

def is_answer_page(text):
    """Heuristics: contains 'answer' or many lines starting with numbers like '1.'"""
    t = text.lower()
    if "answer" in t or "answers" in t or "solution" in t:
        return True
    # count numeric-lines
    lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
    num_lines = sum(1 for ln in lines if re.match(r'^\d{1,3}\s*[\.\)]?\s*\S+', ln))
    if num_lines >= 3:  # >=3 numeric lines => likely answers page
        return True
    return False

def extract_answers_from_text(text):
    """
    Return dict {int_num: str_answer}
    Accepts lines like:
      1. ONION RINGS
      2 PANCAKE
      3) HOTDOG
      4  RICE
    """
    answers = {}
    for ln in text.splitlines():
        ln = ln.strip()
        if not ln:
            continue
        m = re.match(r'^(\d{1,3})\s*[\.\)]?\s*(.+)$', ln)
        if m:
            idx = int(m.group(1))
            ans = m.group(2).strip()
            # remove trailing punctuation
            ans = re.sub(r'[\.:]$', '', ans).strip()
            if ans:
                answers[idx] = ans
    return answers

# -------------------- Main processing --------------------
def process_pdf(pdf_path: Path, pipeline: PaddleOCRVL, out_root: Path):
    log("Processing", pdf_path.name)
    try:
        output = pipeline.predict(input=str(pdf_path))
    except Exception as e:
        log("ERROR running pipeline on", pdf_path, ":", e)
        return

    # collect per-page markdown dicts and images
    page_markdowns = []   # each is the md dict returned by pipeline
    page_images = []      # each is dict mapping relative path -> PIL.Image
    for res in output:
        md = res.markdown
        page_markdowns.append(md)
        page_images.append(md.get("markdown_images", {}))

    # helper to convert a single-page md dict to text using pipeline helper
    # pipeline.concatenate_markdown_pages accepts list of page dicts
    page_texts = []
    for md in page_markdowns:
        try:
            page_text = pipeline.concatenate_markdown_pages([md])
        except Exception:
            # fallback: try to get 'markdown_text' key or str()
            page_text = md.get("markdown_text") if isinstance(md, dict) else str(md)
            if not page_text:
                page_text = str(md)
        page_texts.append(page_text)

    # Determine which pages are answer pages
    answer_pages_idx = [i for i, txt in enumerate(page_texts) if is_answer_page(txt)]
    if not answer_pages_idx:
        # fallback: assume last page is answer
        answer_pages_idx = [len(page_texts) - 1]

    # Extract answers map from all detected answer pages
    answers_map = {}
    for idx in answer_pages_idx:
        answers_map.update(extract_answers_from_text(page_texts[idx]))

    # If no answers parsed, try to look across whole doc text
    if not answers_map:
        whole = "\n".join(page_texts)
        answers_map.update(extract_answers_from_text(whole))

    # Prepare output directory for this PDF
    pdf_out_dir = out_root / pdf_path.stem
    pdf_out_dir.mkdir(parents=True, exist_ok=True)

    # Save a text file of answers for checking
    answers_txt_path = pdf_out_dir / "answers.txt"
    with open(answers_txt_path, "w", encoding="utf-8") as f:
        if answers_map:
            for k in sorted(answers_map.keys()):
                f.write(f"{k}. {answers_map[k]}\n")
        else:
            f.write("# No answers extracted\n")

    # Now build mapping image_path -> number
    # For each image on each page, attempt to find a nearby number in that same page's text
    img_to_number = {}  # rel_img_path -> int num (if found)
    # pattern: number before img tag OR number on same line adjacent; handle multiple variants
    pattern_before = re.compile(r'(\d{1,3})\s*[\r\n\s]*<img[^>]*src="([^"]+)"', re.IGNORECASE)
    pattern_after = re.compile(r'<img[^>]*src="([^"]+)"[^>]*>[\r\n\s]*([^\n<]+)', re.IGNORECASE)
    pattern_number_line = re.compile(r'^\s*(\d{1,3})\s*[\.\)]?\s*$', re.IGNORECASE | re.MULTILINE)

    for page_idx, page_txt in enumerate(page_texts):
        # try 'number before img' pattern
        for m in pattern_before.finditer(page_txt):
            num = int(m.group(1))
            img_path = m.group(2)
            img_to_number[img_path] = num
        # try 'img then text' pattern (some MD has image then below a number or text)
        for m in pattern_after.finditer(page_txt):
            img_path = m.group(1)
            trailing = m.group(2).strip()
            # if trailing is a number or looks like number label
            m2 = re.match(r'^(\d{1,3})$', trailing)
            if m2:
                img_to_number[img_path] = int(m2.group(1))
            # else maybe not a number; try find a nearby line above this img occurrence for a number
        # fallback: find stand-alone lines that are numbers and map in reading order
        # Extract list of img keys in this page
        imgs_here = list(page_images[page_idx].keys())
        if imgs_here and page_txt:
            # If there are explicit number-only lines, map them in vertical order to images in encountered order
            nums_on_page = [int(m.group(1)) for m in re.finditer(r'^\s*(\d{1,3})\s*$', page_txt, re.MULTILINE)]
            if nums_on_page and len(nums_on_page) == len(imgs_here):
                for img_k, num_k in zip(imgs_here, nums_on_page):
                    img_to_number[img_k] = num_k

    # If still missing mapping, as last resort map by image filename order to lowest unused numbers
    all_image_keys = []
    for d in page_images:
        all_image_keys.extend(list(d.keys()))
    # dedupe while preserving order
    seen = set(); all_image_keys = [x for x in all_image_keys if not (x in seen or seen.add(x))]

    assigned = set(img_to_number.values())
    next_num = 1
    for img_k in all_image_keys:
        if img_k in img_to_number:
            continue
        # find next free number
        while next_num in assigned:
            next_num += 1
        img_to_number[img_k] = next_num
        assigned.add(next_num)
        next_num += 1

    # Save images using answers_map when possible
    problems = []
    for page_idx, img_dict in enumerate(page_images):
        for rel_path, pil_img in img_dict.items():
            num = img_to_number.get(rel_path)
            if num is None:
                problems.append(f"No number for image {rel_path}")
                num = 0
            ans = answers_map.get(num)
            if ans:
                name = f"{num:02d}_{clean_filename(ans)}.png"
            else:
                # fallback name from rel_path
                base = Path(rel_path).name
                name = f"{num:02d}_{clean_filename(base)}.png"
            save_path = pdf_out_dir / name
            try:
                pil_img.save(save_path)
            except Exception as e:
                problems.append(f"Failed saving {save_path}: {e}")

    # log result
    log("Saved images to", pdf_out_dir)
    if problems:
        log("Warnings / issues:")
        for p in problems:
            log(" -", p)

# Entry point
def main():
    pipeline = PaddleOCRVL()
    pdfs = list(INPUT_DIR.glob("*.pdf"))
    if not pdfs:
        log("No pdf files found in", INPUT_DIR)
        return
    for pdf in sorted(pdfs):
        process_pdf(pdf, pipeline, OUTPUT_ROOT)
    log("All done. Output at", OUTPUT_ROOT)

if __name__ == "__main__":
    main()
