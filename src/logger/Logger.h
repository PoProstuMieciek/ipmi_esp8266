#pragma once

#include <Arduino.h>

enum MessageLevel
{
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG
};

class Logger
{
    public:
        String channel_name;

        void begin(String channel_name = "[System]");

        size_t printf(const char *format, MessageLevel level, ...);
        size_t printf_raw(const char *format, ...);
        size_t println(const String &s, MessageLevel level);

        String getLevelToString(MessageLevel level);
};