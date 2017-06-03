#pragma once

#define OUTPUT 1
#define HIGH   true
#define LOW    false

#include <chrono>
#include <cstdio>

void pinMode(size_t, size_t);

void digitalWrite(size_t, bool);

uint32_t millis();

void increment_time(size_t millis);

class CSerial
{
    public:
        void begin(int);
        operator bool() { return true; }
        void println(const char* buff);
};

extern CSerial Serial;
