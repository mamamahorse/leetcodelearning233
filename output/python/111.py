def pdf_page_to_image(page):
    """将PDF页面转换为numpy图像数组"""
    mat = fitz.Matrix(2, 2)  # 放大2倍以获得更好的质量
    pix = page.get_pixmap(matrix=mat)
    img = Image.frombytes("RGB", [pix.width, pix.height], pix.samples)
    return np.array(img)


def detect_image_grid(image):
    """
    检测图片网格位置
    返回12个小图片的坐标 (x, y, w, h)
    """
    # 转换为灰度图
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    
    # 使用自适应阈值处理
    binary = cv2.adaptiveThreshold(
        gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, 
        cv2.THRESH_BINARY_INV, 21, 10
    )
    
    # 查找轮廓
    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # 过滤出符合大小要求的矩形区域
    rectangles = []
    for contour in contours:
        x, y, w, h = cv2.boundingRect(contour)
        area = w * h
        
        # 过滤：面积要足够大，且宽高比合理
        if area > 10000 and 0.5 < w/h < 2:
            rectangles.append((x, y, w, h))
    
    # 按位置排序（从上到下，从左到右）
    rectangles.sort(key=lambda r: (r[1] // 100, r[0]))  # 先按y坐标分组，再按x坐标排序
    
    return rectangles[:12]  # 返回前12个