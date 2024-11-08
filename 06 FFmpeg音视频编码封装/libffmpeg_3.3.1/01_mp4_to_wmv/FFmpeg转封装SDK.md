# FFmpeg转封装相关api

## 相关数据类型
1. **`AVFormatContext`**:
    - 代表音视频格式的容器，包含了整个音视频文件的格式信息，如视频流、音频流等。
    - 通过 avformat_open_input() 打开输入文件，avformat_alloc_output_context2() 分配输出文件的 AVFormatContext。
    - 使用 avformat_new_stream() 创建新的音视频流，将音视频流添加到 AVFormatContext 中。
2. **`AVStream`**:
    - 代表音频流或视频流，包含了流的详细信息，如编码器参数、时间基等。
    - 通过 avformat_new_stream() 创建音视频流，然后将编码器参数复制到对应的流中。
3. **`AVCodecParameters`**:
    - 用于描述编解码器的参数，如编解码器类型、码率、分辨率等。
    - 在这段代码中，通过 avcodec_parameters_copy() 复制输入流的参数到输出流中。
4. **`AVPacket`**:
    - 代表一个音视频数据包，包含了编码后的音视频帧数据以及时间戳等信息。
    - 在处理音视频数据时，通过 av_rescale_q_rnd() 重新计算时间戳，然后使用 av_write_frame() 写入帧数据。
5. **`其他关系`**:
    - AVFormatContext 包含多个 AVStream，每个 AVStream 对应一个音频或视频流。
    - 在处理音视频数据时，需要根据时间戳将数据包写入正确的流中，保持音视频同步。


## 相对应的API分类:
1. **AVFormatContext**:
   - `avformat_open_input()`: 打开输入文件。
   - `avformat_alloc_output_context2()`: 为输出文件分配 AVFormatContext。
   - `avformat_new_stream()`: 创建新的音视频流。
   - `av_dump_format()`: 打印输入输出流的详细信息。
   - `avformat_write_header()`: 写入输出文件的头部信息。
   - `av_write_frame()`: 写入一个帧。
   - `av_write_trailer()`: 写入输出文件的尾部信息。

2. **AVStream**:
   - 操作视频流和音频流的相关函数。

3. **AVCodecParameters**:
   - `avcodec_parameters_copy()`: 复制编码器参数。

4. **AVPacket**:
   - `av_rescale_q_rnd()`: 重新计算时间戳。
   - `av_packet_unref()`: 释放 AVPacket。

5. **其他**:
   - `av_register_all()`: 注册 FFmpeg 中的所有可用 Muxer 和 Demuxer。
   - `avio_open()`: 打开文件以进行写入操作。
   - `avio_close()`: 关闭文件 I/O。