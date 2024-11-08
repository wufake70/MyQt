# RGB视频裸数据H264编码

## 像素格式数据
1. RGB(RGBA,BGR,BGRA)格式 红绿蓝三个颜色通道，A是透明通道
2. YUV格式 亮度和色度

## H264编码相关参数
### I帧、P帧、B帧
1. **`I帧即关键帧`**，完整的图像信息，不需要以来其他帧数据。
2. **`P帧即预测帧`**，依赖于前面已经解码数据帧，存储前面数据帧的差异。
3. **`B帧即双向预测帧`**，依赖前后帧进行编码，B帧越多压缩比越大

## RGB视频裸数据获取 
```
# Python
import cv2
import numpy as np

# 读取视频文件
video_capture = cv2.VideoCapture('./test.mkv')

# 存储RGB裸数据的列表
rgb_data = []

# 逐帧读取视频并转换为RGB数据
i = 0
while video_capture.isOpened():
    ret, frame = video_capture.read() # 得到bgr数据格式
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

```
```
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
```

## FFmpeg SDK
1. **AVCodec**
   - 用于表示编解码器的数据结构。
   - 通过`avcodec_find_encoder`函数查找特定编码器。

2. **AVCodecContext**
   - 描述编解码器上下文的数据结构。
   - 包含了编解码器的所有参数和状态信息。
   - 通过`avcodec_alloc_context3`函数进行分配。

3. **AVFormatContext**
   - 用于表示封装格式的上下文。
   - 包含了封装格式相关的信息。
   - 通过`avformat_alloc_output_context2`函数进行分配。

4. **AVStream**
   - 表示音视频流的数据结构。
   - 在封装格式上下文中，可以通过`avformat_new_stream`创建新的数据流。

5. **AVCodecParameters**
   - 描述编解码器参数的数据结构。
   - 可以通过`avcodec_parameters_from_context`将`AVCodecContext`的参数复制到`AVCodecParameters`中。

6. **SwsContext**
   - 用于进行图像转换的数据结构。
   - 通过`sws_getCachedContext`获取。

7. **AVFrame**
   - 表示帧的数据结构。
   - 用于存储图像帧数据。
   - 可以通过`av_frame_alloc`进行分配。

8. **AVPacket**
   - 表示编码数据包的数据结构。
   - 存储编码后的数据。
