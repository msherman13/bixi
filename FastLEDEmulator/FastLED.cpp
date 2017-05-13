#include "FastLED.h"
#include "Arduino.h"

#include <cstdio>
#include <unistd.h>

CFastLED::CFastLED()
{
    m_file.open("sim.csv");
    m_start_time_ms = millis();
}

void CFastLED::show()
{
    m_file << millis() - m_start_time_ms << ",";
    for(size_t i=0;i<m_numLeds;i++)
    {
        char logstr[16];
        sprintf(logstr, "0x%02X%02X%02X", m_leds[i].r, m_leds[i].g, m_leds[i].b);
        m_file << "," << logstr;
    }
    m_file << std::endl;

    // fake the refresh rate
    usleep(c_sleep_time_ms * 1000);
}

CFastLED FastLED;
