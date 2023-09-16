#include "Logger.h"

void Logger::begin(String channel_name)
{
    this->channel_name = channel_name;
}

size_t Logger::printf(const char *format, MessageLevel level, ...)
{
    size_t total = 0;

    total +=
        Serial.printf(
            "[%s]%s ",
            getLevelToString(level).c_str(),
            channel_name.c_str()
        );

    va_list args;
    va_start(args, level);

    char buffer[256];
    size_t len;

    len = vsnprintf(buffer, sizeof(buffer), format, args);
    len = Serial.write((const uint8_t *) buffer, len);

    total += len;
    va_end(args);

    return total;
}

size_t Logger::printf_raw(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[256];
    size_t len;

    len = vsnprintf(buffer, sizeof(buffer), format, args);
    len = Serial.write((const uint8_t *) buffer, len);

    va_end(args);
    return len;
}

size_t Logger::println(const String &s, MessageLevel level)
{
    return
        Serial.printf(
            "[%s]%s %s\n",
            getLevelToString(level).c_str(),
            channel_name.c_str(),
            s.c_str()
        );
}

String Logger::getLevelToString(MessageLevel level)
{
    if (level == MessageLevel::FATAL) return "FATAL";
    else if (level == MessageLevel::ERROR) return "ERROR";
    else if (level == MessageLevel::WARN ) return "WARN";
    else if (level == MessageLevel::INFO ) return "INFO";
    else if (level == MessageLevel::DEBUG) return "DEBUG";
    else return "";
}