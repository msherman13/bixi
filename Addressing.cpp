#include "Addressing.h"

size_t Addressing::EffectiveStrandOffset(size_t strand)
{
    return c_effective_strand_length * strand;
}

size_t Addressing::StrandOffset(size_t strand)
{
    size_t ret = 0;

    for(size_t i=0;i<strand;i++)
    {
        ret += c_strand_length[i];
    }

    return ret;
}
