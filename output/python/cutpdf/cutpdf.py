import os
from pypdf import PdfReader, PdfWriter

def split_pdf_by_bookmarks(pdf_path, output_folder="chapters"):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    reader = PdfReader(pdf_path)
    
    # 存储提取出的章节信息
    sections = []

    def get_sections_recursive(outline_list):
        """递归遍历书签树，将所有书签展平为一个线性列表"""
        for item in outline_list:
            if isinstance(item, list):
                # 如果是列表，递归处理子书签
                get_sections_recursive(item)
            else:
                try:
                    # 获取页码
                    page_num = reader.get_destination_page_number(item)
                    # 清理文件名非法字符
                    title = item.title.strip().replace("/", "-").replace(":", "_").replace("|", "_")
                    sections.append({'title': title, 'start_page': page_num})
                except Exception as e:
                    print(f"跳过书签 {item.title}: {e}")

    # 开始提取
    get_sections_recursive(reader.outline)

    # 按页码排序（防止 PDF 书签顺序与物理页码不一致）
    sections.sort(key=lambda x: x['start_page'])

    # 如果没有找到书签，直接退出
    if not sections:
        print("未能在PDF中找到有效书签，请检查PDF是否有目录索引。")
        return

    # 循环遍历章节进行切割
    for i in range(len(sections)):
        start = sections[i]['start_page']
        # 结束页码是下一项的开始。如果是最后一项，则到文档最后一页
        end = sections[i+1]['start_page'] if i + 1 < len(sections) else len(reader.pages)
        
        # 避免起始页和结束页相同（针对某些指向同一页的多个书签）
        if start >= end and i + 1 < len(sections):
            print(f"跳过重叠书签: {sections[i]['title']}")
            continue

        writer = PdfWriter()
        for page_num in range(start, end):
            writer.add_page(reader.pages[page_num])
            
        # 生成带编号的文件名
        output_filename = f"{i+1:02d}_{sections[i]['title']}.pdf"
        output_path = os.path.join(output_folder, output_filename)
        
        with open(output_path, "wb") as output_file:
            writer.write(output_file)
        print(f"成功导出: {output_filename} (第 {start+1} 页 到 第 {end} 页)")

# 使用方法
pdf_file = "计算机组成原理 第6版 白中英 戴志涛 2019 科学出版社.pdf"
split_pdf_by_bookmarks(pdf_file)