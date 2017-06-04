#pragma once

#include "PixelArray.h"
#include "MapProjection.h"

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace DomeMappings
{
    struct Mappings : public CPixelArray::CompleteConfig
    {
        static constexpr size_t c_num_shapes = 0;

        size_t m_shape_start[c_num_shapes]    = {};
        size_t m_shape_length[c_num_shapes]   = {};
        size_t m_shape_num_legs[c_num_shapes] = {};

        Mappings() :
            CPixelArray::CompleteConfig()
        {
            m_num_raw_pixels = 9000;

            // we provide latitude and longitude for now, map to 2d via lambert projection
            m_num_logical_pixels = 0;
            for(int latitude=0;latitude<91;latitude+=10)
            {
                for(int longitude=0;longitude<361;longitude+=10)
                {
                    MapProjection::GeographicCoord geog;
                    geog.latitude  = MapProjection::DegreesToRadians(latitude);
                    geog.longitude = MapProjection::DegreesToRadians(longitude);

                    m_coordinate[m_num_logical_pixels] = MapProjection::LambertProjection(geog);
                    m_location[m_num_logical_pixels]   = m_num_logical_pixels;
                    m_num_logical_pixels++;
                }
            }
        }
    };
};
