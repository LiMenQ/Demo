import cv2
import numpy as np

# 获取单应性矩阵
def get_homo(img1, img2):
    # 获取特征转换对象
    sift = cv2.SIFT_create()
    # 获取特征点和描述子
    k1, d1 = sift.detectAndCompute(img1, None)
    k2, d2 = sift.detectAndCompute(img2, None)
    # 创建特征匹配器
    bf = cv2.BFMatcher()
    # 进行特征匹配
    matches = bf.knnMatch(d1, d2, k=2)
    # 过滤特征点
    goods = []
    for m1, m2 in matches:
        if m1.distance < 0.8 * m2.distance:
            goods.append(m1)
    
    min_matches = 8
    if len(goods) > min_matches:
        # 获取单应性矩阵
        img1_pts = []
        img2_pts = []

        for m in goods:
            img1_pts.append(k1[m.queryIdx].pt)
            img2_pts.append(k2[m.trainIdx].pt)
        
        img1_pts = np.float32(img1_pts).reshape(-1, 1, 2)
        img2_pts = np.float32(img2_pts).reshape(-1, 1, 2)
        H, mask = cv2.findHomography(img1_pts, img2_pts, cv2.RANSAC, 5.0)
        return H
    else:
        print("err: Not enough")
        exit()
    
# 图像拼接函数
def stitch_img(img1, img2, H):

    # 获得角点
    h1, w1 = img1.shape[:2]
    h2, w2 = img2.shape[:2]

    img1_dims = np.float32([[0, 0], [0, h1], [w1, h1], [w1, 0]]).reshape(-1, 1, 2)
    img2_dims = np.float32([[0, 0], [0, h2], [w2, h2], [w2, 0]]).reshape(-1, 1, 2)

    # 图片旋转平移
    img1_transform = cv2.perspectiveTransform(img1_dims, H)
    result_dims = np.concatenate((img2_dims, img1_transform), axis=0)

    [x_min, y_min] = np.int32(result_dims.min(axis=0).ravel()-0.5)
    [x_max, y_max] = np.int32(result_dims.max(axis=0).ravel()+0.5)

    transform_dist = [-x_min, -y_min]
    transform_array = np.array([[1, 0, transform_dist[0]], 
                                [0, 1, transform_dist[1]], [0, 0, 1]])
    result_img = cv2.warpPerspective(img1, transform_array.dot(H), (x_max - x_min, y_max - y_min))

    # 创建一张大图片 拼接 
    result_img[transform_dist[1]:transform_dist[1] + h2, 
            transform_dist[0]:transform_dist[0] + w2] = img2  
    # 输出 
    return result_img

# 读取文件 设置成 640 * 480
img1 = cv2.imread("map1.png")
img2 = cv2.imread("map2.png")

img1 = cv2.resize(img1, (640, 480))
img2 = cv2.resize(img2, (640, 480))
# 横向拼接
inputs = np.hstack((img1, img2))

# 获取单应性矩阵
H = get_homo(img1, img2)

# 根据单应性矩阵进行变换 平移
result_img = stitch_img(img1, img2, H) 

cv2.imshow("inputs", result_img)
cv2.waitKey(0)
