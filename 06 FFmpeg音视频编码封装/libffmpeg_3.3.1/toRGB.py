import cv2
import numpy as np

# 读取视频文件
video_capture = cv2.VideoCapture('./test.mkv')

# 存储RGB裸数据的列表
rgb_data = []

# 逐帧读取视频并转换为RGB数据
i = 0
while video_capture.isOpened():
    ret, frame = video_capture.read() # frame 得到bgr数据格式
    if not ret:
        break

    # i=i+1
    # cv2.imwrite(f'./output_image{i}.jpg', frame);

    # 将BGR数据转换为RGB数据
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGBA)

    # 将RGB数据存储在列表中
    rgb_data.append(rgb_frame)
    # rgb_data.append(frame)

# 释放视频捕获对象
video_capture.release()

# 保存RGB数据为新文件
np.save('rgb_data.npy', np.array(rgb_data))
