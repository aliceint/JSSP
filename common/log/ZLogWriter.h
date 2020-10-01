/* zhanglj 2020-09-26
 * 目的:提供写文本功能,多线程互斥,超出一定长度自动关闭
 * 日志输出路径:应用程序下log目录,以日期命名,最长不得超过512KB,超过512KB的重新写一个文本
 */
#pragma once
#include <string>
#include <mutex>
#include <fstream>

class ZLogWriter
{
public:
    ~ZLogWriter();

    static ZLogWriter* Instance();
    bool Write(std::string strLogLine);
private:
    ZLogWriter();
    bool CreatLogPath();
    std::string GetLogName();

    unsigned int m_uiTxtSize;

    std::string m_strPath;
    std::string m_strLogName;

    std::string m_strOldName;
    int m_iOldNameIndex;

    std::mutex m_mutex;
    std::fstream m_fstream;
};
