#include "Math.h"

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
    union
    {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}


float Math::theta_from_cartesian(float x, float y)
{
    return 0;
}
