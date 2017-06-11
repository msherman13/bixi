#pragma once

#include "PixelArray.h"
#include "MapProjection.h"
#include "Logging.h"

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace DomeMappings
{
    constexpr size_t c_num_physical_pixels = 7000;
    constexpr size_t c_num_logical_pixels  = 4942;
    constexpr size_t c_num_shapes          = 0; // TODO

    constexpr size_t c_shape_length[c_num_shapes] = {}; // TODO
    constexpr size_t c_shape_start[c_num_shapes] = {}; // TODO
    constexpr size_t c_shape_num_legs[c_num_shapes] = {}; // TODO

    // takes logical index as argument, returns raw index
    size_t GetLocation(size_t index);

    // takes logical index as argument
    CPixelArray::Coordinate GetCoordinate(size_t index);
};
