#include "ZLogWriter.h"
#include <ctime>
#include <unistd.h> //access
#include <sys/stat.h> //mkdir

const int FILE_MAX_SIZE_KB = 512; //待优化,从配置文件读取

ZLogWriter::ZLogWriter()
        : m_uiTxtSize(0)
{
    m_strPath = "./log";
    m_strLogName = "";
    m_strOldName = "old";
    m_iOldNameIndex = 0;
}

ZLogWriter::~ZLogWriter(){}

ZLogWriter* ZLogWriter::Instance()
{
    static ZLogWriter instance;
    return &instance;
}

bool ZLogWriter::CreatLogPath()
{
    if (access(m_strPath.c_str(), F_OK) != 0)
    {

        int b_ret = mkdir (m_strPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (b_ret == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }

    return false;
}

std::string ZLogWriter::GetLogName()
{
    std::time_t t = std::time(nullptr);
    char time_buf[128];
    strftime(time_buf, sizeof(time_buf), "%F_%H_%M_%S", std::localtime(&t));

    std::string str_log_name = time_buf;


    if (m_strOldName == str_log_name)
    {
        ++m_iOldNameIndex;
        str_log_name += "_" + std::to_string(m_iOldNameIndex);
    }
    else
    {
        m_strOldName = str_log_name;
        m_iOldNameIndex = 0;
    }

    str_log_name += ".log";
    return str_log_name;
}

bool ZLogWriter::Write(std::string strLogLine)
{
    //1.线程加锁
    m_mutex.lock();

    //2.判断文件名是否为空,以及是否打开,未打开则打开文件
    if (m_strLogName.empty())
    {
        m_strLogName = GetLogName();
    }

    std::string str_log_path = m_strPath + "/" + m_strLogName;

    if (!ZLogWriter::CreatLogPath())
    {
        return false;
    }

    if (!m_fstream.is_open())
    {
        m_fstream.clear();
        m_fstream.open(str_log_path, std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary);
    }


    //3.将日志信息写入文本
    m_fstream << strLogLine <<"\n";
    m_uiTxtSize += strLogLine.size();

    //4.如果文件大于512KB则关闭文件,并重新打开一个文件
    if (m_uiTxtSize >= FILE_MAX_SIZE_KB * 1024)
    {
        m_uiTxtSize = 0;
        m_fstream.close();
        m_strLogName = "";
    }

    //5.线程解锁
    m_mutex.unlock();

    return true;
}

