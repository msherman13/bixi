#include "PixelArray.h"

// raster array

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace GridMappings
{
    struct Mappings : public CPixelArray::Config
    {
        Mappings() :
            CPixelArray::Config()
        {
            m_num_legs  = 100;

            for(size_t i=0;i<m_num_legs;i++)
            {
                m_start_index[i]      = i * 100;
                m_end_index[i]        = m_start_index[i] + 99;
                double raster_y       = 2 * (i / 100.0) - 0.99;
                m_start_coordinate[i] = CPixelArray::Coordinate(-1.00, raster_y);
                m_end_coordinate[i]   = CPixelArray::Coordinate(1.00, raster_y);
            }
        }
    };
};
