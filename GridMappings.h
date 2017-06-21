#pragma once

#include "PixelArrayLegs.h"

// raster array

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace GridMappings
{
    struct Mappings : public CPixelArrayLegs::Config
    {
        static constexpr size_t c_resolution = 64;
        Mappings() :
            CPixelArrayLegs::Config()
        {
            m_num_legs  = c_resolution;

            for(size_t i=0;i<c_resolution;i++)
            {
                m_leg_offset[i]      = i * c_resolution;
                m_leg_size[i]        = c_resolution;
//                float raster_y       = 2 * (i / (float)c_resolution) - 0.99;
//                m_start_coordinate[i] = CPixelArray::Coordinate(-1.00, raster_y);
//                m_end_coordinate[i]   = CPixelArray::Coordinate(1.00, raster_y);
            }
        }
    };
};
