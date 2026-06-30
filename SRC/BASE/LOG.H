#ifndef __LOG_H__
#define __LOG_H__

typedef enum {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

void Log_Print(
    const char *file,
    int line,
    LogLevel level,
    const char *string_text,
    ...
);

#define LOG_ERROR    Log_Error
#define LOG_WARNING  Log_Warning
#define LOG_INFO     Log_Info

#ifdef __DEBUG__
    #define LOG_DEBUG Log_Debug
#else
    #define LOG_DEBUG Log_Null
#endif

void Log_Error(const char *string_text, ...);
void Log_Warning(const char *string_text, ...);
void Log_Info(const char *string_text, ...);
void Log_Debug(const char *string_text, ...);
void Log_Null(const char *string_text, ...);

#endif