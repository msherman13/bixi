#include "Arduino.h"

void pinMode(size_t, size_t)
{
}

void digitalWrite(size_t, bool)
{
}

size_t millis()
{
	using namespace std::chrono;
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
	);
    return ms.count();
}

void CSerial::begin(int)
{
}

void CSerial::println(const char* buff)
{
    printf("%s\n", buff);
}

CSerial Serial;
