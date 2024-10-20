#ifndef QIPMSG_H
#define QIPMSG_H

#define QIPMSG_SERVER_PORT  0x00001167

#define QIPMSG_UPD_NOP              0x0000000
#define QIPMSG_UPD_PROBE            0x0000001
#define QIPMSG_UPD_EXIT             0x0000002
#define QIPMSG_UPD_TXT              0x0000003
#define QIPMSG_UPD_TCPSERVER        0x0000004


#define QIPMSG_UPD_FILE_ADD         0x0000006
#define QIPMSG_UPD_FILE_DEL         0x0000007
#define QIPMSG_UPD_FILE_SENDACK     0x0000008
#define QIPMSG_UPD_FILE_RECEIVEACK  0x0000009

#define QIPMSG_TCP_FILE_BEGIN       0x000000a
#define QIPMSG_TCP_FILE_SCHEDULE    0x000000b
#define QIPMSG_TCP_FILE_END         0x000000c

#define QIPMSG_VERSION              "0.1.1"
/*
 * 修复(TLS) 多对一同时发送文件时 线程资源竞争问题，
 * FilesTcpClient::readSocketData 使用了静态局部变量，
 * 导致多个线程对同一个变量操作，触发线程安全问题
void FilesTcpClient::readSocketData()
        ...
        static QFile *pFile;
        static qint64 bytesToWriten=0;
        static qint64 fileSize = 0;
        switch (jsonObj["type"].toInt())
 */

//#define QIPMSG_VERSION              "0.1.0"


#endif // QIPMSG_H
