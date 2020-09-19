/* zhanglj 2020-09-06
 * 目的:输出日志
 * 日志输出路径:应用程序下log目录,以日期命名,最长不得超过512KB,超过512KB的重新写一个文本
 * 日志格式: [时间][等级]文件名,行数:日志信息
 */
#include "ZLog.h"
#include <cstdarg>
#include <vector>
#include <sstream>

std::string LOG_MAP_[4]= {
    "INVALID",
    "INFO",
    "WARNING",
    "ERROR"
    };

std::string logStr(E_LOG_LEVEL level, const char* file, const char* function, int line, const char *fmt, va_list args)
{
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


    std::stringstream stream;
    stream << "[" << LOG_MAP_[(int)level] <<"]"<<file<<":"<<line<<", INFO:"<<buf.data();

    std::string results;
    results = stream.str();

    return results;
}

void logInfo(const char* file, const char* function, int line, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    std::string res = LOGSTR(E_LOG_INFO, file, function, line, fmt, args);

    std::cout<<res<<std::endl;

    va_end(args);
}

