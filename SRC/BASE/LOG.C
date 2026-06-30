#include "BASE/@BASE.H"

void Log_Print(
    const char *file,
    int line,
    LogLevel level,
    const char *string_text,
    ...
)
{
    va_list args;

    printf("[%s:%d] ", file, line);

    switch (level) {
        case LOG_LEVEL_ERROR:
            printf("ERROR: ");
            break;

        case LOG_LEVEL_WARNING:
            printf("WARNING: ");
            break;

        case LOG_LEVEL_INFO:
            printf("INFO: ");
            break;

        case LOG_LEVEL_DEBUG:
            printf("DEBUG: ");
            break;
    }

    va_start(args, string_text);
    vprintf(string_text, args);
    va_end(args);

    printf("\n");
}

void Log_Error(const char *string_text, ...)
{
    va_list args;

    printf("ERROR: ");

    va_start(args, string_text);
    vprintf(string_text, args);
    va_end(args);

    printf("\n");
}

void Log_Warning(const char *string_text, ...)
{
    va_list args;

    printf("WARNING: ");

    va_start(args, string_text);
    vprintf(string_text, args);
    va_end(args);

    printf("\n");
}

void Log_Info(const char *string_text, ...)
{
    va_list args;

    printf("INFO: ");

    va_start(args, string_text);
    vprintf(string_text, args);
    va_end(args);

    printf("\n");
}

void Log_Debug(const char *string_text, ...)
{
    va_list args;

    printf("DEBUG: ");

    va_start(args, string_text);
    vprintf(string_text, args);
    va_end(args);

    printf("\n");
}

void Log_Null(const char *string_text, ...)
{
    /* avoid unused parameter warning if needed */
    string_text = string_text;
}