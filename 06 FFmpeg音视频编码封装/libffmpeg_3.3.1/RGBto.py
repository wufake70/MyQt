import cv2
import numpy as np

# 加载保存的RGB数据
rgb_data = np.load('rgb_data.npy')

# 获取视频帧的宽度和高度
height, width, _ = rgb_data[0].shape

# 创建VideoWriter对象来保存视频
output_filename = 'output_video.mp4'
fourcc = cv2.VideoWriter_fourcc(*'mp4v')  # 使用MP4的编解码器
out = cv2.VideoWriter(output_filename, fourcc, 30.0, (width, height))

# 将RGB数据转换为视频帧并写入输出视频文件
for frame in rgb_data:
    bgr_frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
    out.write(bgr_frame)

# 释放输出视频对象
out.release()