import os
import time
import requests
from selenium import webdriver
from selenium.webdriver.edge.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.edge.options import Options

# ============= 浏览器初始化 =============
edge_options = Options()
edge_options.add_argument("--start-maximized")
edge_options.add_argument("--disable-blink-features=AutomationControlled")

# 可选：无头模式（不显示浏览器）
# edge_options.add_argument("--headless")

service = Service(r"E:\edgedriver\msedgedriver.exe")  # ← 修改成你的路径
driver = webdriver.Edge(service=service, options=edge_options)
driver.set_page_load_timeout(60)

url = "https://www.postermywall.com/index.php/sizes/poster-template?safe_content=safe"
driver.get(url)
time.sleep(5)

# ============= 模拟慢速滚动加载 =============
target_count = 1000   # 希望下载的图片数量
scroll_pause = 3      # 每次滚动后等待时间
img_urls = set()
last_count = 0
no_change_rounds = 0
step = 1000  # 每次滚动像素数

while len(img_urls) < target_count:
    driver.execute_script(f"window.scrollBy(0, {step});")
    time.sleep(scroll_pause)

    # 收集当前图片
    imgs = driver.find_elements(By.CSS_SELECTOR, "img[src*='https://d1csarkz8obe9u.cloudfront.net']")
    for img in imgs:
        src = img.get_attribute("src")
        src = src.replace("small", "large").replace("medium", "large")
        img_urls.add(src)

    print(f"当前已加载 {len(img_urls)} 张图片...")

    # 检测是否还在加载新图
    if len(img_urls) == last_count:
        no_change_rounds += 1
        if no_change_rounds >= 5:
            print("⚠️ 页面似乎加载完毕或停止更新。")
            break
    else:
        no_change_rounds = 0
    last_count = len(img_urls)

print(f"✅ 加载完成，共收集到 {len(img_urls)} 张图片。")
driver.quit()

# ============= 下载图片 =============
save_dir = "downloaded_posters"
os.makedirs(save_dir, exist_ok=True)

for i, url in enumerate(list(img_urls)[:target_count]):  # 只取前 target_count 张
    try:
        response = requests.get(url, timeout=10)
        if response.status_code == 200:
            path = os.path.join(save_dir, f"poster_{i+1}.jpg")
            with open(path, "wb") as f:
                f.write(response.content)
            print(f"✅ 下载成功 ({i+1}/{target_count})")
        else:
            print(f"❌ 状态码异常: {response.status_code}")
    except Exception as e:
        print(f"⚠️ 下载出错: {e}")

print("🎉 所有图片下载完成！")
