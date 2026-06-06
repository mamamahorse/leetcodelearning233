import os
import re
from pathlib import Path
import fitz  # PyMuPDF
from PIL import Image
import numpy as np
import cv2
import pytesseract

# 如果tesseract不在系统PATH中，需要指定路径
# pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'


def extract_answers_from_last_page(pdf_path):
    """从PDF最后一页使用OCR提取以数字开头的谜底文本"""
    doc = fitz.open(pdf_path)
    last_page = doc[-1]

    # 将最后一页转换为高分辨率图像以提高OCR准确率
    mat = fitz.Matrix(3, 3)  # 放大3倍
    pix = last_page.get_pixmap(matrix=mat)
    img = Image.frombytes("RGB", [pix.width, pix.height], pix.samples)
    img_array = np.array(img)
    doc.close()

    # 图像预处理
    gray = cv2.cvtColor(img_array, cv2.COLOR_RGB2GRAY)
    denoised = cv2.fastNlMeansDenoising(gray)
    _, binary = cv2.threshold(denoised, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

    # OCR识别
    custom_config = r'--oem 3 --psm 6'
    text = pytesseract.image_to_string(binary, lang='chi_sim+eng', config=custom_config)

    # 清理文本
    lines = [line.strip() for line in text.split('\n') if line.strip()]

    # ✅ 只保留以数字开头的谜底
    answers = []
    for line in lines:
        match = re.match(r'^(\d+)[.\s、)）]*\s*(.+)$', line)
        if match:
            number = int(match.group(1))
            answer_text = match.group(2).strip()
            if answer_text:
                answers.append((number, answer_text))

    # ✅ 按编号排序
    answers.sort(key=lambda x: x[0])

    # ✅ 只保留文本部分
    answer_texts = [item[1] for item in answers]

    print(f"OCR识别到 {len(answer_texts)} 个谜底:")
    for i, ans in enumerate(answer_texts[:12], 1):
        print(f"  {i}. {ans}")

    return answer_texts[:12]


def pdf_page_to_image(page):
    """将PDF页面转换为numpy图像数组"""
    mat = fitz.Matrix(2, 2)  # 放大2倍以获得更好的质量
    pix = page.get_pixmap(matrix=mat)
    img = Image.frombytes("RGB", [pix.width, pix.height], pix.samples)
    return np.array(img)


def preprocess_pdf_image(image):
    """
    预处理PDF图像，增强淡色背景与白色背景的对比度
    """
    # 转换为LAB色彩空间
    lab = cv2.cvtColor(image, cv2.COLOR_RGB2LAB)
    l, a, b = cv2.split(lab)
    
    # CLAHE增强对比度
    clahe = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(8, 8))
    l_enhanced = clahe.apply(l)
    
    # 合并回RGB
    enhanced_lab = cv2.merge([l_enhanced, a, b])
    enhanced = cv2.cvtColor(enhanced_lab, cv2.COLOR_LAB2RGB)
    
    # 转灰度并拉伸对比度
    gray = cv2.cvtColor(enhanced, cv2.COLOR_RGB2GRAY)
    
    # 只对非白色区域拉伸对比度
    non_white_pixels = gray[gray < 250]
    if len(non_white_pixels) > 0:
        min_val = np.percentile(non_white_pixels, 5)
        max_val = np.percentile(non_white_pixels, 95)
        stretched = np.clip((gray - min_val) * (255 / (max_val - min_val)), 0, 255).astype(np.uint8)
    else:
        stretched = gray
    
    return enhanced, stretched


def detect_content_region(image):
    """
    检测内容区域的起始位置，排除标题栏
    """
    h, w = image.shape[:2]
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    
    # 寻找标题栏底部
    search_start = int(h * 0.08)
    search_end = int(h * 0.30)
    
    # 计算每一行的平均亮度
    row_mean = np.mean(gray[search_start:search_end, :], axis=1)
    
    # 寻找亮度模式：淡色 -> 白色 -> 淡色
    transitions = []
    for i in range(10, len(row_mean) - 10):
        # 检测亮度突然升高（进入白色区域）
        if row_mean[i] > 240 and row_mean[i-5] < 230:
            # 检查后面是否又变暗（进入图片区域）
            for j in range(i+5, min(i+50, len(row_mean))):
                if row_mean[j] < 230:
                    transitions.append(search_start + j)
                    break
    
    if transitions:
        content_start_y = min(transitions)
    else:
        # 如果检测不到，使用固定比例
        content_start_y = int(h * 0.15)
    
    return content_start_y


def detect_single_block_size(image):
    """
    检测单个图片块的尺寸
    返回: (width, height, start_x, start_y) 或 None
    """
    h, w = image.shape[:2]
    
    # 1. 检测内容区域起始位置
    content_start_y = detect_content_region(image)
    
    # 2. 只处理内容区域
    content_region = image[content_start_y:, :]
    
    # 3. 预处理增强对比度
    enhanced, gray_stretched = preprocess_pdf_image(content_region)
    
    # 4. 创建二值图像 - 反转后淡色块变白
    inverted = 255 - gray_stretched
    
    # 5. 多阈值尝试
    best_blocks = []
    best_score = 0
    
    for thresh_val in [15, 20, 25, 30, 35, 40]:
        _, binary = cv2.threshold(inverted, thresh_val, 255, cv2.THRESH_BINARY)
        
        # 形态学操作：填充小孔
        kernel_close = cv2.getStructuringElement(cv2.MORPH_RECT, (25, 25))
        closed = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel_close)
        
        # 膨胀连接相近区域
        kernel_dilate = cv2.getStructuringElement(cv2.MORPH_RECT, (15, 15))
        dilated = cv2.dilate(closed, kernel_dilate, iterations=1)
        
        # 查找轮廓
        contours, _ = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        ch, cw = content_region.shape[:2]
        valid_blocks = []
        
        for contour in contours:
            x, y, bw, bh = cv2.boundingRect(contour)
            area = bw * bh
            
            # 预期单个块约占内容区域的 1/12
            expected_area = (cw * ch) / 12
            area_ratio = area / expected_area
            aspect_ratio = bw / bh if bh > 0 else 0
            
            # 过滤条件
            if (0.4 < area_ratio < 1.5 and 
                0.6 < aspect_ratio < 1.7 and
                y > ch * 0.02 and
                bw > cw * 0.15 and
                bh > ch * 0.2):
                valid_blocks.append((x, y, bw, bh, area))
        
        # 评分系统
        if len(valid_blocks) > 0:
            widths = [b[2] for b in valid_blocks]
            heights = [b[3] for b in valid_blocks]
            width_std = np.std(widths)
            height_std = np.std(heights)
            
            score = len(valid_blocks) - (width_std + height_std) / 100
            
            if score > best_score:
                best_score = score
                best_blocks = valid_blocks
    
    if len(best_blocks) == 0:
        return None
    
    # 6. 使用中位数确定标准尺寸
    widths = [b[2] for b in best_blocks]
    heights = [b[3] for b in best_blocks]
    
    median_width = int(np.median(widths))
    median_height = int(np.median(heights))
    
    # 7. 找到最左上角的块
    best_blocks.sort(key=lambda b: (b[1], b[0]))
    start_x, start_y_in_content = best_blocks[0][0], best_blocks[0][1]
    
    # 转换回原图坐标
    start_y = content_start_y + start_y_in_content
    
    return median_width, median_height, start_x, start_y


def is_blank_region(roi, threshold=0.95):
    """判断区域是否为空白（接近纯白）"""
    gray = cv2.cvtColor(roi, cv2.COLOR_RGB2GRAY)
    white_ratio = np.sum(gray > 245) / gray.size
    return white_ratio > threshold


def detect_image_grid(image, rows=3, cols=4):
    """
    检测图片网格位置
    返回12个小图片的坐标 (x, y, w, h)，空白位置返回None
    """
    result = detect_single_block_size(image)
    
    if result is None:
        print("  ⚠️ 无法检测到图片块，跳过此页")
        return []
    
    block_w, block_h, start_x, start_y = result
    print(f"  ✓ 图片块尺寸: {block_w}x{block_h}, 起始位置: ({start_x}, {start_y})")
    
    h, w = image.shape[:2]
    
    # 计算间距
    remaining_width = w - start_x - cols * block_w
    remaining_height = h - start_y - rows * block_h
    
    h_gap = remaining_width / (cols + 1) if cols > 0 else 0
    v_gap = remaining_height / (rows + 1) if rows > 0 else 0
    
    rectangles = []
    
    for row in range(rows):
        for col in range(cols):
            # 计算位置
            x = int(start_x + col * (block_w + h_gap))
            y = int(start_y + row * (block_h + v_gap))
            
            # 边界检查
            if x + block_w > w or y + block_h > h:
                continue
            
            # 检查是否为空白
            roi = image[y:y+block_h, x:x+block_w]
            if not is_blank_region(roi):
                rectangles.append((x, y, block_w, block_h))
    
    return rectangles


def extract_puzzles_from_pdf(pdf_path, output_dir):
    """处理单个PDF文件"""
    print(f"\n处理文件: {pdf_path}")
    
    # 创建输出目录
    pdf_name = Path(pdf_path).stem
    pdf_output_dir = Path(output_dir) / pdf_name
    pdf_output_dir.mkdir(parents=True, exist_ok=True)
    
    # 提取谜底
    answers = extract_answers_from_last_page(pdf_path)
    print(f"提取到 {len(answers)} 个谜底")
    
    if len(answers) < 12:
        print(f"警告: 谜底数量不足12个，实际只有 {len(answers)} 个")
    
    # 打开PDF
    doc = fitz.open(pdf_path)
    
    puzzle_count = 0
    
    # 遍历除最后一页外的所有页面
    for page_num in range(len(doc) - 1):
        page = doc[page_num]
        print(f"处理第 {page_num + 1} 页...")
        
        # 转换为图像
        img_array = pdf_page_to_image(page)
        
        # 检测图片网格
        rectangles = detect_image_grid(img_array)
        print(f"  检测到 {len(rectangles)} 个图片区域")
        
        # 提取并保存每个小图片
        for i, (x, y, w, h) in enumerate(rectangles):
            if puzzle_count >= len(answers):
                print(f"  警告: 谜底已用完，跳过剩余图片")
                break
            
            # 添加一些边距
            margin = 5
            x1 = max(0, x - margin)
            y1 = max(0, y - margin)
            x2 = min(img_array.shape[1], x + w + margin)
            y2 = min(img_array.shape[0], y + h + margin)
            
            # 裁剪图片
            cropped = img_array[y1:y2, x1:x2]
            
            # 使用谜底作为文件名
            answer = answers[puzzle_count]
            # 清理文件名中的非法字符
            safe_filename = re.sub(r'[<>:"/\\|?*]', '_', answer)
            filename = f"{safe_filename}.png"
            
            # 保存图片
            output_path = pdf_output_dir / filename
            Image.fromarray(cropped).save(output_path)
            print(f"  保存: {filename}")
            
            puzzle_count += 1
    
    doc.close()
    print(f"完成! 共提取 {puzzle_count} 张图片")
    return puzzle_count


def batch_process_pdfs(input_dir, output_dir):
    """批量处理目录中的所有PDF文件"""
    input_path = Path(input_dir)
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    
    # 查找所有PDF文件
    pdf_files = list(input_path.glob("*.pdf"))
    
    if not pdf_files:
        print(f"在 {input_dir} 中没有找到PDF文件")
        return
    
    print(f"找到 {len(pdf_files)} 个PDF文件")
    
    total_puzzles = 0
    for pdf_file in pdf_files:
        try:
            count = extract_puzzles_from_pdf(str(pdf_file), str(output_path))
            total_puzzles += count
        except Exception as e:
            print(f"处理 {pdf_file.name} 时出错: {str(e)}")
            import traceback
            traceback.print_exc()
    
    print(f"\n全部完成! 共处理 {total_puzzles} 张谜题图片")


if __name__ == "__main__":
    # 使用示例
    INPUT_DIR = r"E:\桌面\pdf"      # 输入PDF文件所在目录
    OUTPUT_DIR = r"E:\桌面\pdf\output"  # 输出图片保存目录
    
    # 如果需要处理单个文件，使用：
    # extract_puzzles_from_pdf(r"E:\rebus\example.pdf", OUTPUT_DIR)
    
    # 批量处理整个目录：
    batch_process_pdfs(INPUT_DIR, OUTPUT_DIR)