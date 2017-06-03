#pragma once

#include <stddef.h>

#include "Utils.h"

namespace Addressing
{
    constexpr size_t c_num_strands                  = 8;
    constexpr size_t c_effective_strand_length      = 2 * (90 + 52);
    //constexpr size_t c_effective_strand_length      = 1000;
    constexpr size_t c_effective_length             = c_num_strands * c_effective_strand_length;
};
