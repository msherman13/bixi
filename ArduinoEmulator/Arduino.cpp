#include "Arduino.h"

void pinMode(size_t, size_t)
{
}

void digitalWrite(size_t, bool)
{
}

size_t curr_time_ms = 0;

size_t millis()
{
    return curr_time_ms;
}

void increment_time(size_t millis)
{
    curr_time_ms += millis;
}

void CSerial::begin(int)
{
}

void CSerial::println(const char* buff)
{
    printf("%s\n", buff);
}

CSerial Serial;
