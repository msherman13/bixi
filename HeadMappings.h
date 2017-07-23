#ifdef GEOM_HEAD

#pragma once

#include "PixelArrayLegs.h"
#include "Logging.h"

namespace HeadMappings
{
    constexpr size_t c_num_strands          = 7;
    constexpr size_t c_strand_length        = 520;
    constexpr size_t c_num_physical_pixels  = c_num_strands * c_strand_length;
    constexpr size_t c_num_logical_pixels   = 2656;

    struct Mappings : public CPixelArrayLegs::Config
    {
        Mappings();

        virtual CPixelArray::Coordinate GetCoordinate(size_t index) final;
        virtual size_t                  GetLocation(size_t index)   final;
        virtual bool                    ApplyGamma(size_t index)    final;
    };

    size_t ShapeStartIndex(size_t index);
    size_t ShapeSize(size_t index);
    size_t ShapeNumLegs(size_t index);
};

#endif // GEOM_HEAD
