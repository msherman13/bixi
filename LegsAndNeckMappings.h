#ifdef GEOM_LEGS_NECK

#pragma once

#include "PixelArrayLegs.h"
#include "Logging.h"

namespace LegsAndNeckMappings
{
    constexpr size_t c_num_strands          = 6;
    constexpr size_t c_num_legs             = 4;
    constexpr size_t c_num_necks            = 1;
    constexpr size_t c_shapes_per_leg       = 4;
    constexpr size_t c_shapes_per_neck      = 8;
    constexpr size_t c_num_leg_shapes       = c_num_legs * c_shapes_per_leg;
    constexpr size_t c_num_neck_shapes      = c_num_necks * c_shapes_per_neck;
    constexpr size_t c_num_physical_pixels  = 750 * c_num_strands;
    constexpr size_t c_num_logical_pixels   = 3840;
    constexpr size_t c_num_shapes           = c_shapes_per_leg * c_num_legs +
                                              c_shapes_per_neck * c_num_necks;

    struct Mappings : public CPixelArrayLegs::Config
    {
        Mappings();

        virtual size_t                  GetLocation(size_t index)   final;
        virtual CPixelArray::Coordinate GetCoordinate(size_t index) final;
    };
};

#endif // GEOM_LEGS_NECK
