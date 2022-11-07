import cv2
import numpy as np

cap = cv2.VideoCapture("video.mp4")

# 去背景模块
bgsubmog = cv2.createBackgroundSubtractorMOG2()
# 5*5卷积核
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))

# 默认参数
min_w = 90 
min_h = 90
line_h = 550
offset = 7
cars = []
carno = 0

# 计算矩形的中心点
def center(x, y, w, h):
    cx = x + int(w / 2)
    cy = y + int(h / 2)
    return cx, cy

while True:
    # 读取视频帧
    ret, frame = cap.read()
    if ret == True:
        # print(frame.shape)
        # 灰度化
        cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        # 高斯去噪
        blur = cv2.GaussianBlur(frame, (3,3), 5)
        # 去背景
        mask = bgsubmog.apply(blur)
        # 腐蚀
        erode = cv2.erode(mask, kernel, iterations=2)
        # 膨胀
        dilate = cv2.dilate(erode, kernel, iterations=3)
        # 闭运算
        close = cv2.morphologyEx(dilate, cv2.MORPH_CLOSE, kernel)
        # 查找轮廓
        cnts, h = cv2.findContours(close, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        # 画线
        cv2.line(frame, (10, line_h), (1260, line_h), (255,255,0), 3)
        for i in cnts:
            # 外接矩形
            (x, y, w, h) = cv2.boundingRect(i)
            # 如果宽高过小 则忽略不计
            if w <= min_w and h <= min_h:
                continue
            # 此时认为外接矩形为车辆
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255,0,0), 2)
            points = center(x, y, w, h)
            cars.append(points) 
            # 如果每一帧的图像中有在直线附近的车辆中心点
            # 则carno + 1 随后从列表中移除这个点
            for x, y in cars:
               if y > line_h - offset and y < line_h + offset:
                    carno += 1
                    cars.remove((x, y))
                    print(carno)
                
        cv2.putText(frame, "Cars Count:" + str(carno), (500, 60), cv2.FONT_HERSHEY_SIMPLEX, 2, (255,0,0), 5)
        cv2.imshow("video", frame) 
        # cv2.imshow("videos", close) 

    key = cv2.waitKey(10)
    # 按Esc键退出
    if key == 27:
        break

# 释放资源
cap.release()
cv2.destroyAllWindows()