#include "Math.h"
#include <cmath>

// see https://en.wikipedia.org/wiki/Exponentiation_by_squaring
float Math::exp_by_squaring(float x, uint32_t n)
{
    if(n < 0)
    {
        return exp_by_squaring(1 / x, -n);
    }
    else if(n == 0)
    {
        return 1;
    }
    else if(n == 1)
    {
        return x;
    }
    else if(n % 2 == 0)
    {
        return exp_by_squaring(x * x, n / 2);
    }
    else
    {
        return x * exp_by_squaring(x * x, (n - 1) / 2);
    }
}

float Math::fast_pow(float a, float b)
{
    float in = fabs(a);
    union
    {
        double d;
        int x[2];
    } u = { in };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}

float Math::fast_sqrt(float x)
{
    unsigned int i = *(unsigned int*) &x;

    // adjust bias
    i  += 127 << 23;
    // approximation of square root
    i >>= 1;

    return *(float*) &i;
}


float Math::theta_from_cartesian(float x, float y)
{
    return 0;
}
