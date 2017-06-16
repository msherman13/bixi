#pragma once

#include <stdint.h>

namespace Math
{
    float exp_by_squaring(float x, uint32_t n);
    float fast_pow(float a, float b);
    float theta_from_cartesian(float x, float y);
};
