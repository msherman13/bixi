#ifdef GEOM_DOME

#pragma once

#include "PixelArrayLegs.h"
#include "MapProjection.h"
#include "Logging.h"

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace DomeMappings
{
    constexpr size_t c_num_strands         = 8;
    constexpr size_t c_num_physical_pixels = 5560;
    constexpr size_t c_num_logical_pixels  = 4664;
    constexpr size_t c_num_shapes          = 22;
    constexpr size_t c_num_double_hex      = 4;
    constexpr size_t c_num_non_hex         = c_num_shapes - 2 * c_num_double_hex;
    constexpr size_t c_inner_hex_index[c_num_double_hex] = { 3, 6, 9, 12 };
    constexpr size_t c_outer_hex_index[c_num_double_hex] = { 4, 7, 10, 13 };

    size_t ShapeStartIndex(size_t shape_index);
    size_t ShapeEndIndex(size_t shape_index);
    size_t ShapeStartLeg(size_t shape_index);
    size_t ShapeEndLeg(size_t shape_index);

    struct Mappings : public CPixelArrayLegs::Config
    {
        Mappings();

        virtual size_t                  GetLocation(size_t index) final;
        virtual CPixelArray::Coordinate GetCoordinate(size_t index) final;
    };
};

#endif // GEOM_DOME
