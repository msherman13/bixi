#pragma once

#include "PixelArrayLegs.h"
#include "MapProjection.h"
#include "Logging.h"

// - mapping of logical index to hardware index
// - mapping of logical index to 2d coordinates

namespace DomeMappings
{
    constexpr size_t c_num_physical_pixels = 7000;
    constexpr size_t c_num_logical_pixels  = 4942;
    constexpr size_t c_num_shapes          = 23;

    // takes logical index as argument, returns raw index
    size_t GetLocation(size_t index);

    // takes logical index as argument
    CPixelArray::Coordinate GetCoordinate(size_t index);

    size_t ShapeStartIndex(size_t shape_index);
    size_t ShapeEndIndex(size_t shape_index);
    size_t ShapeStartLeg(size_t shape_index);
    size_t ShapeEndLeg(size_t shape_index);

    struct Mappings : public CPixelArrayLegs::Config
    {
        Mappings();
    };
};
