/* zhanglj 2020-09-06
 * 目的:输出日志
 * 日志输出路径:应用程序下log目录,以日期命名,最长不得超过512KB,超过512KB的重新写一个文本
 * 日志格式: [时间][等级]文件名,行数:日志信息
 */
#pragma once

#include <string>
#define __LINUX__ 1

enum E_LOG_LEVEL
{
    E_LOG_INVALID = 0,
    E_LOG_INFO,
    E_LOG_WARNING,
    E_LOG_USER_ERROR,
    E_LOG_SYS_ERROR
};

enum E_LOG_PRINT_WAY
{
    E_LOG_PRINT_INVALID = 0,
    E_LOG_PRINT_STDOUT,
    E_LOG_PRINT_TXT
};

//日志文件配置选项, 后续从配置文件读取,待优化.
#define PRINT_LOG_LEVEL 1
#define PRINT_LOG_WAY E_LOG_PRINT_TXT


#define LOGINFO(fmt, ...) logInfo(__FILE__,__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGWARNING(fmt, ...) logWarning(__FILE__,__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGERROR(fmt, ...) logError(__FILE__,__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define SYSERROR(fmt, ...) sysError(__FILE__,__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSTR(level, file, function, line, fmt, args) logStr(level, file, function, line, fmt, args)


std::string logStr(E_LOG_LEVEL level, const char* file, const char* function, int line, const char *fmt, va_list args);
void logInfo(const char* file, const char* function, int line, const char *fmt, ...);
void logWarning(const char* file, const char* function, int line, const char *fmt, ...);
void logError(const char* file, const char* function, int line, const char *fmt, ...);
void sysError(const char* file, const char* function, int line, const char *fmt, ...);
void pringLog(E_LOG_LEVEL level, std::string log);

