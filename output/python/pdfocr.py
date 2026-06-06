# import os
# import re
# from pathlib import Path
# import fitz  # PyMuPDF
# from PIL import Image
# import numpy as np
# import cv2
# import pytesseract

# # 如果tesseract不在系统PATH中，需要指定路径
# # pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'


# def extract_answers_from_last_page(pdf_path):
#     """从PDF最后一页使用OCR提取谜底文本"""
#     doc = fitz.open(pdf_path)
#     last_page = doc[-1]
    
#     # 将最后一页转换为高分辨率图像以提高OCR准确率
#     mat = fitz.Matrix(3, 3)  # 放大3倍
#     pix = last_page.get_pixmap(matrix=mat)
#     img = Image.frombytes("RGB", [pix.width, pix.height], pix.samples)
#     img_array = np.array(img)
    
#     doc.close()
    
#     # 图像预处理以提高OCR准确率
#     gray = cv2.cvtColor(img_array, cv2.COLOR_RGB2GRAY)
    
#     # 去噪
#     denoised = cv2.fastNlMeansDenoising(gray)
    
#     # 二值化
#     _, binary = cv2.threshold(denoised, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    
#     # 使用pytesseract进行OCR识别（中文+英文）
#     custom_config = r'--oem 3 --psm 6'
#     text = pytesseract.image_to_string(binary, lang='chi_sim+eng', config=custom_config)
    
#     # 清理文本，分割成列表
#     lines = [line.strip() for line in text.split('\n') if line.strip()]
    
#     # 只提取以数字编号开头的行作为谜底
#     answers = []
#     for line in lines:
#         # 匹配以数字开头的行（支持多种格式：1. 1、1) 1， 等）
#         # 匹配后提取编号后面的文本作为谜底
#         match = re.match(r'^(\d+)[.、)）,，\s]+(.+)


# def pdf_page_to_image(page):
#     """将PDF页面转换为numpy图像数组"""
#     mat = fitz.Matrix(2, 2)  # 放大2倍以获得更好的质量
#     pix = page.get_pixmap(matrix=mat)
#     img = Image.frombytes("RGB", [pix.width, pix.height], pix.samples)
#     return np.array(img)


# def detect_image_grid(image):
#     """
#     检测图片网格位置
#     返回12个小图片的坐标 (x, y, w, h)
#     """
#     # 转换为灰度图
#     gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    
#     # 使用自适应阈值处理
#     binary = cv2.adaptiveThreshold(
#         gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, 
#         cv2.THRESH_BINARY_INV, 21, 10
#     )
    
#     # 查找轮廓
#     contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
#     # 过滤出符合大小要求的矩形区域
#     rectangles = []
#     for contour in contours:
#         x, y, w, h = cv2.boundingRect(contour)
#         area = w * h
        
#         # 过滤：面积要足够大，且宽高比合理
#         if area > 10000 and 0.5 < w/h < 2:
#             rectangles.append((x, y, w, h))
    
#     # 按位置排序（从上到下，从左到右）
#     rectangles.sort(key=lambda r: (r[1] // 100, r[0]))  # 先按y坐标分组，再按x坐标排序
    
#     return rectangles[:12]  # 返回前12个


# def extract_puzzles_from_pdf(pdf_path, output_dir):
#     """处理单个PDF文件"""
#     print(f"\n处理文件: {pdf_path}")
    
#     # 创建输出目录
#     pdf_name = Path(pdf_path).stem
#     pdf_output_dir = Path(output_dir) / pdf_name
#     pdf_output_dir.mkdir(parents=True, exist_ok=True)
    
#     # 提取谜底
#     answers = extract_answers_from_last_page(pdf_path)
#     print(f"提取到 {len(answers)} 个谜底")
    
#     if len(answers) < 12:
#         print(f"警告: 谜底数量不足12个，实际只有 {len(answers)} 个")
    
#     # 打开PDF
#     doc = fitz.open(pdf_path)
    
#     puzzle_count = 0
    
#     # 遍历除最后一页外的所有页面
#     for page_num in range(len(doc) - 1):
#         page = doc[page_num]
#         print(f"处理第 {page_num + 1} 页...")
        
#         # 转换为图像
#         img_array = pdf_page_to_image(page)
        
#         # 检测图片网格
#         rectangles = detect_image_grid(img_array)
#         print(f"  检测到 {len(rectangles)} 个图片区域")
        
#         # 提取并保存每个小图片
#         for i, (x, y, w, h) in enumerate(rectangles):
#             if puzzle_count >= len(answers):
#                 print(f"  警告: 谜底已用完，跳过剩余图片")
#                 break
            
#             # 添加一些边距
#             margin = 5
#             x1 = max(0, x - margin)
#             y1 = max(0, y - margin)
#             x2 = min(img_array.shape[1], x + w + margin)
#             y2 = min(img_array.shape[0], y + h + margin)
            
#             # 裁剪图片
#             cropped = img_array[y1:y2, x1:x2]
            
#             # 使用谜底作为文件名（不加编号）
#             answer = answers[puzzle_count]
#             # 清理文件名中的非法字符
#             safe_filename = re.sub(r'[<>:"/\\|?*]', '_', answer)
#             filename = f"{safe_filename}.png"
            
#             # 保存图片
#             output_path = pdf_output_dir / filename
#             Image.fromarray(cropped).save(output_path)
#             print(f"  保存: {filename}")
            
#             puzzle_count += 1
    
#     doc.close()
#     print(f"完成! 共提取 {puzzle_count} 张图片")
#     return puzzle_count


# def batch_process_pdfs(input_dir, output_dir):
#     """批量处理目录中的所有PDF文件"""
#     input_path = Path(input_dir)
#     output_path = Path(output_dir)
#     output_path.mkdir(parents=True, exist_ok=True)
    
#     # 查找所有PDF文件
#     pdf_files = list(input_path.glob("*.pdf"))
    
#     if not pdf_files:
#         print(f"在 {input_dir} 中没有找到PDF文件")
#         return
    
#     print(f"找到 {len(pdf_files)} 个PDF文件")
    
#     total_puzzles = 0
#     for pdf_file in pdf_files:
#         try:
#             count = extract_puzzles_from_pdf(str(pdf_file), str(output_path))
#             total_puzzles += count
#         except Exception as e:
#             print(f"处理 {pdf_file.name} 时出错: {str(e)}")
#             import traceback
#             traceback.print_exc()
    
#     print(f"\n全部完成! 共处理 {total_puzzles} 张谜题图片")


# if __name__ == "__main__":
#     # 使用示例
#     INPUT_DIR = r"E:\rebus"         # 输入PDF文件所在目录
#     OUTPUT_DIR = r"E:\rebus\output"  # 输出图片保存目录
    
#     # 如果需要处理单个文件，使用：
#     # extract_puzzles_from_pdf(r"E:\rebus\example.pdf", OUTPUT_DIR)
    
#     # 批量处理整个目录：
#     batch_process_pdfs(INPUT_DIR, OUTPUT_DIR)
# , line)
#         if match:
#             number = int(match.group(1))
#             answer_text = match.group(2).strip()
#             if answer_text:  # 确保谜底不为空
#                 answers.append((number, answer_text))
    
#     # 按编号排序
#     answers.sort(key=lambda x: x[0])
    
#     # 只返回谜底文本（去掉编号）
#     answer_texts = [answer[1] for answer in answers]
    
#     print(f"OCR识别到 {len(answer_texts)} 个谜底:")
#     for i, ans in enumerate(answer_texts[:12], 1):
#         print(f"  {i}. {ans}")
    
#     return answer_texts[:12]  # 只取前12个


# def pdf_page_to_image(page):
#     """将PDF页面转换为numpy图像数组"""
#     mat = fitz.Matrix(2, 2)  # 放大2倍以获得更好的质量
#     pix = page.get_pixmap(matrix=mat)
#     img = Image.frombytes("RGB", [pix.width, pix.height], pix.samples)
#     return np.array(img)


# def detect_image_grid(image):
#     """
#     检测图片网格位置
#     返回12个小图片的坐标 (x, y, w, h)
#     """
#     # 转换为灰度图
#     gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    
#     # 使用自适应阈值处理
#     binary = cv2.adaptiveThreshold(
#         gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, 
#         cv2.THRESH_BINARY_INV, 21, 10
#     )
    
#     # 查找轮廓
#     contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
#     # 过滤出符合大小要求的矩形区域
#     rectangles = []
#     for contour in contours:
#         x, y, w, h = cv2.boundingRect(contour)
#         area = w * h
        
#         # 过滤：面积要足够大，且宽高比合理
#         if area > 10000 and 0.5 < w/h < 2:
#             rectangles.append((x, y, w, h))
    
#     # 按位置排序（从上到下，从左到右）
#     rectangles.sort(key=lambda r: (r[1] // 100, r[0]))  # 先按y坐标分组，再按x坐标排序
    
#     return rectangles[:12]  # 返回前12个


# def extract_puzzles_from_pdf(pdf_path, output_dir):
#     """处理单个PDF文件"""
#     print(f"\n处理文件: {pdf_path}")
    
#     # 创建输出目录
#     pdf_name = Path(pdf_path).stem
#     pdf_output_dir = Path(output_dir) / pdf_name
#     pdf_output_dir.mkdir(parents=True, exist_ok=True)
    
#     # 提取谜底
#     answers = extract_answers_from_last_page(pdf_path)
#     print(f"提取到 {len(answers)} 个谜底")
    
#     if len(answers) < 12:
#         print(f"警告: 谜底数量不足12个，实际只有 {len(answers)} 个")
    
#     # 打开PDF
#     doc = fitz.open(pdf_path)
    
#     puzzle_count = 0
    
#     # 遍历除最后一页外的所有页面
#     for page_num in range(len(doc) - 1):
#         page = doc[page_num]
#         print(f"处理第 {page_num + 1} 页...")
        
#         # 转换为图像
#         img_array = pdf_page_to_image(page)
        
#         # 检测图片网格
#         rectangles = detect_image_grid(img_array)
#         print(f"  检测到 {len(rectangles)} 个图片区域")
        
#         # 提取并保存每个小图片
#         for i, (x, y, w, h) in enumerate(rectangles):
#             if puzzle_count >= len(answers):
#                 print(f"  警告: 谜底已用完，跳过剩余图片")
#                 break
            
#             # 添加一些边距
#             margin = 5
#             x1 = max(0, x - margin)
#             y1 = max(0, y - margin)
#             x2 = min(img_array.shape[1], x + w + margin)
#             y2 = min(img_array.shape[0], y + h + margin)
            
#             # 裁剪图片
#             cropped = img_array[y1:y2, x1:x2]
            
#             # 使用谜底作为文件名（不加编号）
#             answer = answers[puzzle_count]
#             # 清理文件名中的非法字符
#             safe_filename = re.sub(r'[<>:"/\\|?*]', '_', answer)
#             filename = f"{safe_filename}.png"
            
#             # 保存图片
#             output_path = pdf_output_dir / filename
#             Image.fromarray(cropped).save(output_path)
#             print(f"  保存: {filename}")
            
#             puzzle_count += 1
    
#     doc.close()
#     print(f"完成! 共提取 {puzzle_count} 张图片")
#     return puzzle_count


# def batch_process_pdfs(input_dir, output_dir):
#     """批量处理目录中的所有PDF文件"""
#     input_path = Path(input_dir)
#     output_path = Path(output_dir)
#     output_path.mkdir(parents=True, exist_ok=True)
    
#     # 查找所有PDF文件
#     pdf_files = list(input_path.glob("*.pdf"))
    
#     if not pdf_files:
#         print(f"在 {input_dir} 中没有找到PDF文件")
#         return
    
#     print(f"找到 {len(pdf_files)} 个PDF文件")
    
#     total_puzzles = 0
#     for pdf_file in pdf_files:
#         try:
#             count = extract_puzzles_from_pdf(str(pdf_file), str(output_path))
#             total_puzzles += count
#         except Exception as e:
#             print(f"处理 {pdf_file.name} 时出错: {str(e)}")
#             import traceback
#             traceback.print_exc()
    
#     print(f"\n全部完成! 共处理 {total_puzzles} 张谜题图片")


# if __name__ == "__main__":
#     # 使用示例
#     INPUT_DIR = r"E:\rebus"         # 输入PDF文件所在目录
#     OUTPUT_DIR = r"E:\rebus\output"  # 输出图片保存目录
    
#     # 如果需要处理单个文件，使用：
#     # extract_puzzles_from_pdf(r"E:\rebus\example.pdf", OUTPUT_DIR)
    
#     # 批量处理整个目录：
#     batch_process_pdfs(INPUT_DIR, OUTPUT_DIR)