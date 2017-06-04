#pragma once

#include "PixelArray.h"

// raster array

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace GridMappings
{
    struct Mappings : public CPixelArray::Config
    {
        static constexpr size_t c_resolution = 128;
        Mappings() :
            CPixelArray::Config()
        {
            m_num_legs  = c_resolution;
            m_num_raw_pixels = c_resolution * c_resolution;

            for(size_t i=0;i<c_resolution;i++)
            {
                m_start_index[i]      = i * c_resolution;
                m_end_index[i]        = m_start_index[i] + c_resolution - 1;
                float raster_y       = 2 * (i / (float)c_resolution) - 0.99;
                m_start_coordinate[i] = CPixelArray::Coordinate(-1.00, raster_y);
                m_end_coordinate[i]   = CPixelArray::Coordinate(1.00, raster_y);
            }
        }
    };
};
