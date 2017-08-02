#ifdef GEOM_LEGS_NECK

#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "LegsAndNeckMappings.h"

class CRoutine;

class CLegsAndNeck : public CPixelArrayLegs
{
    public:
        static constexpr size_t c_transition_time_ms  = 20 * 1000;
        static constexpr size_t c_min_routine_time_ms = 5 * 60 * 1000;
        static constexpr size_t c_max_routine_time_ms = 10 * 60 * 1000;

    public:
        CLegsAndNeck();
        ~CLegsAndNeck();

    public:
        virtual void   Continue()        override;
        virtual size_t PixelsPerStrand() const final { return LegsAndNeckMappings::c_pixels_per_strand; }

    public:
        enum Routine
        {
            RoutineSolid,
            RoutineCyclePallete,
            RoutineTraverse,

            RoutineQty,
            RoutineNone,
            RoutineTest,
        };

    private:
        Routine m_curr_routine        = RoutineSolid;
        size_t  m_routine_end_ms      = 0;
        Routine GetNextRoutine();
        void    AdvanceRoutine();
        void    SetAllShapesTo(Routine routine);

    private:
        CPixelArray* m_leg_shapes[LegsAndNeckMappings::c_num_legs][LegsAndNeckMappings::c_shapes_per_leg];
        CPixelArray* m_neck_shapes[LegsAndNeckMappings::c_num_legs][LegsAndNeckMappings::c_shapes_per_leg];

    public:
        CPixelArray* GetLegShape(size_t leg, size_t shape);
        CPixelArray* GetNeckShape(size_t neck, size_t shape);

    private:
        static CMemoryPool<CLegsAndNeck, 1> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CLegsAndNeck*>(ptr));
        }

    private:
        static LegsAndNeckMappings::Mappings s_mappings;
};

#endif // GEOM_LEGS_NECK
