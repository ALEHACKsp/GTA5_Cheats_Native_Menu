#include "main.h"

void Log::Info(const char* str,...){
    va_list list;
    //日志主体
    char logStr[1024];
    //参数
    char logParams[1024];
    va_start(list, str);
    _vsnprintf_s(logParams, sizeof(logParams), str, list);
    va_end(list);
    sprintf_s(logStr, "[Info] %s\n", logParams);
    printf(logStr);
}
void Log::Error(const char* str,...){
    va_list list;
    //日志主体
    char LogStr[1024];
    //参数
    char Params[1024];
    va_start(list, str);
    _vsnprintf_s(Params, sizeof(Params), str, list);
    va_end(list);
    sprintf_s(LogStr, "[Error] %s\n", Params);
    printf(LogStr);
}
void Log::Debug(const char* str,...){
    va_list list;
    //日志主体
    char LogStr[1024];
    //参数
    char Params[1024];
    va_start(list, str);
    _vsnprintf_s(Params, sizeof(Params), str, list);
    va_end(list);
    sprintf_s(LogStr, "[Debug] %s\n", Params);
    printf(LogStr);
}