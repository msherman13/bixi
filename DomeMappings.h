#include "PixelArray.h"

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace DomeMappings
{
    struct Mappings : public CPixelArray::Config
    {
        static constexpr size_t c_num_shapes = 4;

        size_t m_shape_start[c_num_shapes]    = {};
        size_t m_shape_length[c_num_shapes]   = {};
        size_t m_shape_num_legs[c_num_shapes] = {};

        Mappings() :
            CPixelArray::Config()
        {
            m_num_legs  = 24;

            // top right outer-hex
            m_shape_start[0]    = 0;
            m_shape_length[0]   = 90;
            m_shape_num_legs[0] = 6;
            m_start_index[0]    = 201;
            m_end_index[0]      = 187;
            m_start_index[1]    = 186;
            m_end_index[1]      = 172;
            m_start_index[2]    = 171;
            m_end_index[2]      = 157;
            m_start_index[3]    = 156;
            m_end_index[3]      = 142;
            m_start_index[4]    = 231;
            m_end_index[4]      = 217;
            m_start_index[5]    = 216;
            m_end_index[5]      = 202;
            m_start_coordinate[0] = CPixelArray::Coordinate( 0.3750,  0.1875);
            m_end_coordinate[0]   = CPixelArray::Coordinate( 0.5000,  0.0625);
            m_start_coordinate[1] = CPixelArray::Coordinate( 0.5000,  0.0625);
            m_end_coordinate[1]   = CPixelArray::Coordinate( 0.3750, -0.0625);
            m_start_coordinate[2] = CPixelArray::Coordinate( 0.3750, -0.0625);
            m_end_coordinate[2]   = CPixelArray::Coordinate( 0.1875, -0.0625);
            m_start_coordinate[3] = CPixelArray::Coordinate( 0.1875, -0.0625);
            m_end_coordinate[3]   = CPixelArray::Coordinate( 0.0625,  0.0625);
            m_start_coordinate[4] = CPixelArray::Coordinate( 0.0625,  0.0625);
            m_end_coordinate[4]   = CPixelArray::Coordinate( 0.1875,  0.1875);
            m_start_coordinate[5] = CPixelArray::Coordinate( 0.1875,  0.1875);
            m_end_coordinate[5]   = CPixelArray::Coordinate( 0.3750,  0.1875);

            // top right inner-hex
            m_shape_start[1]    = 90;
            m_shape_length[1]   = 48;
            m_shape_num_legs[1] = 6;
            m_start_index[6]    = 263;
            m_end_index[6]      = 256;
            m_start_index[7]    = 255;
            m_end_index[7]      = 248;
            m_start_index[8]    = 247;
            m_end_index[8]      = 240;
            m_start_index[9]    = 239;
            m_end_index[9]      = 232;
            m_start_index[10]   = 279;
            m_end_index[10]     = 272;
            m_start_index[11]   = 271;
            m_end_index[11]     = 264;
            m_start_coordinate[6]  = CPixelArray::Coordinate( 0.34375, 0.1250);
            m_end_coordinate[6]    = CPixelArray::Coordinate( 0.40625, 0.0625);
            m_start_coordinate[7]  = CPixelArray::Coordinate( 0.40625, 0.0625);
            m_end_coordinate[7]    = CPixelArray::Coordinate( 0.34375, 0.0000);
            m_start_coordinate[8]  = CPixelArray::Coordinate( 0.34375, 0.0000);
            m_end_coordinate[8]    = CPixelArray::Coordinate( 0.21875, 0.0000);
            m_start_coordinate[9]  = CPixelArray::Coordinate( 0.21875, 0.0000);
            m_end_coordinate[9]    = CPixelArray::Coordinate( 0.15625, 0.0625);
            m_start_coordinate[10] = CPixelArray::Coordinate( 0.15625, 0.0625);
            m_end_coordinate[10]   = CPixelArray::Coordinate( 0.21875, 0.1250);
            m_start_coordinate[11] = CPixelArray::Coordinate( 0.21875, 0.1250);
            m_end_coordinate[11]   = CPixelArray::Coordinate( 0.34375, 0.1250);

            // bottom left outer-hex
            m_shape_start[2]    = 138;
            m_shape_length[2]   = 90;
            m_shape_num_legs[2] = 6;
            m_start_index[12]   = 89;
            m_end_index[12]     = 75;
            m_start_index[13]   = 74;
            m_end_index[13]     = 60;
            m_start_index[14]   = 59;
            m_end_index[14]     = 45;
            m_start_index[15]   = 44;
            m_end_index[15]     = 30;
            m_start_index[16]   = 29;
            m_end_index[16]     = 15;
            m_start_index[17]   = 14;
            m_end_index[17]     = 0;
            m_start_coordinate[12] = CPixelArray::Coordinate( -0.1875,  0.0625);
            m_end_coordinate[12]   = CPixelArray::Coordinate( -0.0625, -0.0625);
            m_start_coordinate[13] = CPixelArray::Coordinate( -0.0625, -0.0625);
            m_end_coordinate[13]   = CPixelArray::Coordinate( -0.1875, -0.1875);
            m_start_coordinate[14] = CPixelArray::Coordinate( -0.1875, -0.1875);
            m_end_coordinate[14]   = CPixelArray::Coordinate( -0.3750, -0.1875);
            m_start_coordinate[15] = CPixelArray::Coordinate( -0.3750, -0.1875);
            m_end_coordinate[15]   = CPixelArray::Coordinate( -0.5000, -0.0625);
            m_start_coordinate[16] = CPixelArray::Coordinate( -0.5000, -0.0625);
            m_end_coordinate[16]   = CPixelArray::Coordinate( -0.3750,  0.0625);
            m_start_coordinate[17] = CPixelArray::Coordinate( -0.3750,  0.0625);
            m_end_coordinate[17]   = CPixelArray::Coordinate( -0.1875,  0.0625);

            // bottom left inner-hex
            m_shape_start[3]    = 228;
            m_shape_length[3]   = 48;
            m_shape_num_legs[3] = 6;
            m_start_index[18]   = 137;
            m_end_index[18]     = 130;
            m_start_index[19]   = 129;
            m_end_index[19]     = 122;
            m_start_index[20]   = 121;
            m_end_index[20]     = 114;
            m_start_index[21]   = 113;
            m_end_index[21]     = 106;
            m_start_index[22]   = 105;
            m_end_index[22]     = 98;
            m_start_index[23]   = 97;
            m_end_index[23]     = 90;
            m_start_coordinate[18] = CPixelArray::Coordinate( -0.21875, -0.0000);
            m_end_coordinate[18]   = CPixelArray::Coordinate( -0.15625, -0.0625);
            m_start_coordinate[19] = CPixelArray::Coordinate( -0.15625, -0.0625);
            m_end_coordinate[19]   = CPixelArray::Coordinate( -0.21875, -0.1250);
            m_start_coordinate[20] = CPixelArray::Coordinate( -0.21875, -0.1250);
            m_end_coordinate[20]   = CPixelArray::Coordinate( -0.34375, -0.1250);
            m_start_coordinate[21] = CPixelArray::Coordinate( -0.34375, -0.1250);
            m_end_coordinate[21]   = CPixelArray::Coordinate( -0.40625, -0.0625);
            m_start_coordinate[22] = CPixelArray::Coordinate( -0.40625, -0.0625);
            m_end_coordinate[22]   = CPixelArray::Coordinate( -0.34375, -0.0000);
            m_start_coordinate[23] = CPixelArray::Coordinate( -0.34375, -0.0000);
            m_end_coordinate[23]   = CPixelArray::Coordinate( -0.21875, -0.0000);

            // hack
            for(size_t i=0;i<m_num_legs;i++)
            {
                m_start_coordinate[i].x *= 2;
                m_end_coordinate[i].x   *= 2;
                m_start_coordinate[i].y *= 2;
                m_end_coordinate[i].y   *= 2;
            }
        }
    };
};
