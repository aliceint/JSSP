/* zhanglj 2020-09-06
 * 目的:输出日志
 * 日志输出路径:应用程序下log目录,以日期命名,最长不得超过512KB,超过512KB的重新写一个文本
 * 日志格式: [时间][等级]文件名,行数:日志信息
 */
#pragma once

#include <iostream>
#include <string>

enum E_LOG_LEVEL
{
    E_LOG_INVALID = 0,
    E_LOG_INFO,
    E_LOG_WARNING,
    E_LOG_ERROR
};


#define LOGINFO(fmt, ...) logInfo(__FILE__,__FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGSTR(level, file, function, line, fmt, args) logStr(level, file, function, line, fmt, args)


std::string logStr(E_LOG_LEVEL level, const char* file, const char* function, int line, const char *fmt, va_list args);
void logInfo(const char* file, const char* function, int line, const char *fmt, ...);

