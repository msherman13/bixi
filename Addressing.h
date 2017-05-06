#pragma once

#include <stddef.h>

#include "Utils.h"

namespace Addressing
{
    constexpr size_t c_num_strands                  = 8;
    constexpr size_t c_effective_strand_length      = 582;
    constexpr size_t c_effective_length             = c_num_strands * c_effective_strand_length;
    constexpr size_t c_strand_length[c_num_strands] = { 582, 419, 416, 435, 366, 478, 367, 582 };
    constexpr size_t c_length                       = Utils::ConstAccum<size_t, c_num_strands>(c_strand_length);

    size_t EffectiveStrandOffset(size_t strand);

    size_t StrandOffset(size_t strand);
};
