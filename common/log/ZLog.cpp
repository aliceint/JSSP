/* zhanglj 2020-09-06
 * 目的:输出日志
 * 日志输出路径:应用程序下log目录,以日期命名,最长不得超过512KB,超过512KB的重新写一个文本
 * 日志格式: [时间][等级]文件名,行数:日志信息
 */
#include "ZLog.h"
#include <cstdarg>
#include <vector>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>
#include "ZLogWriter.h"

#ifdef __LINUX__
#include <unistd.h> //access
#include <sys/stat.h> //mkdir
#include <errno.h> //errno
#include <string.h> //strerror
#endif

std::string LOG_MAP_[5]= {
    "INVALID",
    "INFO",
    "WARNING",
    "USER ERROR",
    "SYSTEM ERROR"
    };

void logInfo(const char* file, const char* function, int line, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    std::string res = LOGSTR(E_LOG_INFO, file, function, line, fmt, args);

    pringLog(E_LOG_INFO, res);

    va_end(args);
}

void logWarning(const char* file, const char* function, int line, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    std::string res = logStr(E_LOG_WARNING, file, function, line, fmt , args);

    pringLog(E_LOG_WARNING, res);

    va_end(args);
}

void logError(const char* file, const char* function, int line, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    std::string res = logStr(E_LOG_USER_ERROR, file, function, line, fmt , args);

    pringLog(E_LOG_USER_ERROR, res);

    va_end(args);
}

void sysError(const char* file, const char* function, int line, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    std::string res = logStr(E_LOG_SYS_ERROR, file, function, line, fmt , args);

    char sys_err_buf[1024];
    sprintf(sys_err_buf, "%s", strerror(errno));

    std::cout<< res << sys_err_buf <<std::endl;

    va_end(args);
    exit(1);
}

std::string logStr(E_LOG_LEVEL level, const char* file, const char* function, int line, const char *fmt, va_list args)
{
    //1. print msg
    va_list args_back;

    //All these functions(vprintf/vfprintf/vsprintf/vsnprintf) invoke va_arg at least once,
    //the value of arg is indeterminate after the return.
    //so copy first
    va_copy(args_back, args);

/*
 *   char buf[1024];
 *    vsprintf(buf, fmt, args);
*/

    // Get Size of all string
    std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, fmt, args_back));
    std::vsnprintf(buf.data(), buf.size(), fmt, args);

    //2. print time
    std::time_t t = std::time(nullptr);
    char time_buf[100];
    std::strftime(time_buf, sizeof(time_buf), "%F %T", std::gmtime(&t));



    std::stringstream stream;
    stream <<"["<<time_buf<<"] "<<"[" << LOG_MAP_[(int)level] <<"] "<<file<<":"<<line<<", INFO:"<<buf.data();

    std::string results;
    results = stream.str();

    return results;
}



void pringLog(E_LOG_LEVEL level, std::string log)
{
    if (level >= PRINT_LOG_LEVEL)
    {
        if (PRINT_LOG_WAY == E_LOG_PRINT_STDOUT)
        {
            std::cout<<log<<std::endl;
        }
        else
        {
            /*std::string log_path = "./log";
            #ifdef __LINUX__
            if (access (log_path.c_str(), F_OK) != 0)
            {
                std::cout<<"dir is not exist"<<std::endl;
                int b_ret = mkdir (log_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (b_ret == 0)
                {
                    std::cout<<"log dir is created"<<std::endl;
                }
                else
                {
                    SYSERROR("log dir is created failed");
                }
            }
            #endif

            #ifdef __WINDOWS_


            #endif

            std::time_t t = std::time(nullptr);
            char time_buf[20];
            strftime(time_buf, sizeof(time_buf), "%F", std::gmtime(&t));
            std::string log_file = log_path + "/" + time_buf;
            log_file += ".log";

            std::ofstream ofs(log_file, std::ios::binary | std::ios::app);
            ofs<<log<<"\n";
            ofs.close();*/

            ZLogWriter::Instance()->Write(log);
        }
    }
}
