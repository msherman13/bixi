#pragma once

#include "Arduino.h"

class CLogging
{
    public:
        static const int c_initTimeoutMs = 1000;

    public:
        static void Init();
        static void log(const char* buff);
};
