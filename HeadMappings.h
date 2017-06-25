#ifdef GEOM_HEAD

#pragma once

#include "PixelArrayLegs.h"
#include "Logging.h"

namespace HeadMappings
{
    constexpr size_t c_num_strands          = 8;
    constexpr size_t c_strand_length        = 300;
    constexpr size_t c_num_physical_pixels  = c_num_strands * c_strand_length;
    constexpr size_t c_num_logical_pixels   = c_num_physical_pixels;

    struct Mappings : public CPixelArrayLegs::Config
    {
        Mappings();

        virtual CPixelArray::Coordinate GetCoordinate(size_t index) final;
    };
};

#endif // GEOM_HEAD
