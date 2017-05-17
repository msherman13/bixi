#pragma once

#include <stddef.h>

namespace Utils
{
    template <typename T, size_t N>
    constexpr T ConstAccum(T const (&a)[N], size_t i = 0U)
    {
        return i < N ? (a[i] + ConstAccum(a, i+1U)) : T{};
    }
};
