
import cv2
import numpy as np

def detect_first_image_block(image):
    """
    检测第一个图片块的位置和尺寸
    利用图片块有淡色背景，与PDF白色背景有对比度
    """
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    
    # 反转图像：白色背景变黑，淡色块变亮
    inverted = 255 - gray
    
    # 轻微模糊去噪
    blurred = cv2.GaussianBlur(inverted, (5, 5), 0)
    
    # 使用Otsu自动阈值
    _, binary = cv2.threshold(blurred, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    
    # 形态学操作：闭运算填充小空洞
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (15, 15))
    closed = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel)
    
    # 查找轮廓
    contours, _ = cv2.findContours(closed, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    # 过滤出合理大小的矩形
    valid_rects = []
    h, w = image.shape[:2]
    min_area = (w * h) * 0.02  # 至少占总面积的2%
    max_area = (w * h) * 0.15  # 最多占总面积的15%
    
    for contour in contours:
        x, y, cw, ch = cv2.boundingRect(contour)
        area = cw * ch
        aspect_ratio = cw / ch if ch > 0 else 0
        
        # 过滤条件：面积合理、宽高比接近正方形
        if min_area < area < max_area and 0.7 < aspect_ratio < 1.5:
            valid_rects.append((x, y, cw, ch))
    
    if not valid_rects:
        return None
    
    # 找到最左上角的矩形（第一个图片块）
    valid_rects.sort(key=lambda r: (r[1], r[0]))
    return valid_rects[0]


def detect_image_grid_smart(image, rows=3, cols=4):
    """
    智能检测网格：先找第一个图片块，再根据其尺寸切割整个网格
    
    返回:
        rectangles: 图片坐标列表，空位置返回None
    """
    # 检测第一个图片块
    first_block = detect_first_image_block(image)
    
    if first_block is None:
        print("警告：无法检测到图片块，使用固定网格")
        return detect_image_grid_fallback(image, rows, cols)
    
    x0, y0, block_w, block_h = first_block
    
    # 计算网格的起始位置和间距
    # 假设第一个块在第一行第一列
    h, w = image.shape[:2]
    
    # 估算列间距：从第一个块位置推算
    col_spacing = block_w + (w - x0 - cols * block_w) / (cols - 1) if cols > 1 else block_w
    row_spacing = block_h + 20  # 行间距大约是块高度加一些空白
    
    rectangles = []
    
    for row in range(rows):
        for col in range(cols):
            # 计算当前块的位置
            x = int(x0 + col * col_spacing)
            y = int(y0 + row * row_spacing)
            
            # 检查是否超出图片范围
            if x + block_w > w or y + block_h > h:
                rectangles.append(None)
                continue
            
            # 验证该位置是否真的有内容（检测是否为空白）
            roi = image[y:y+block_h, x:x+block_w]
            if is_blank_region(roi):
                rectangles.append(None)
            else:
                rectangles.append((x, y, block_w, block_h))
    
    return rectangles


def is_blank_region(roi, threshold=0.98):
    """
    判断区域是否为空白
    检查该区域是否接近纯白色
    """
    gray = cv2.cvtColor(roi, cv2.COLOR_RGB2GRAY)
    white_ratio = np.sum(gray > 240) / gray.size
    return white_ratio > threshold


def detect_image_grid_fallback(image, rows=3, cols=4):
    """
    后备方案：固定网格切割
    当智能检测失败时使用
    """
    h, w = image.shape[:2]
    
    # 尝试检测页眉底部位置
    header_bottom = detect_header_bottom(image)
    
    # 计算可用区域
    usable_height = h - header_bottom
    cell_w = w // cols
    cell_h = usable_height // rows
    
    # 添加边距
    padding = int(min(cell_w, cell_h) * 0.03)
    
    rectangles = []
    for row in range(rows):
        for col in range(cols):
            x = col * cell_w + padding
            y = header_bottom + row * cell_h + padding
            width = cell_w - 2 * padding
            height = cell_h - 2 * padding
            
            rectangles.append((x, y, width, height))
    
    return rectangles


def detect_header_bottom(image):
    """
    检测页眉底部位置
    查找图片上部大片白色区域的结束位置
    """
    gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    h, w = gray.shape
    
    # 计算每一行的平均亮度
    row_brightness = np.mean(gray, axis=1)
    
    # 找到第一个亮度明显下降的位置（从白色背景进入内容区）
    threshold = 250
    for i in range(int(h * 0.1), int(h * 0.3)):  # 在图片上部10%-30%区域搜索
        if row_brightness[i] < threshold:
            # 找到连续5行都低于阈值，确认进入内容区
            if all(row_brightness[i:i+5] < threshold):
                return max(0, i - 10)  # 留一点余量
    
    return int(h * 0.1)  # 默认返回10%高度


def visualize_detection(image, rectangles):
    """
    可视化检测结果，方便调试
    """
    vis = image.copy()
    for i, rect in enumerate(rectangles):
        if rect is not None:
            x, y, w, h = rect
            cv2.rectangle(vis, (x, y), (x+w, y+h), (0, 255, 0), 2)
            cv2.putText(vis, str(i+1), (x+10, y+30), 
                       cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
    return vis


# 使用示例
"""
rectangles = detect_image_grid_smart(image, rows=3, cols=4)

# 提取非空图片
for i, rect in enumerate(rectangles):
    if rect is not None:
        x, y, w, h = rect
        small_image = image[y:y+h, x:x+w]
        # 处理 small_image...
"""