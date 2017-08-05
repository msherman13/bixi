#ifdef GEOM_DOME

#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "DomeMappings.h"

class CRoutine;

class CDome : public CPixelArrayLegs
{
    public:
        static constexpr size_t c_transition_time_ms  = 20 * 1000;
        static constexpr size_t c_min_routine_time_ms = 2 * 60 * 1000;
        static constexpr size_t c_max_routine_time_ms = 4 * 60 * 1000;

    public:
        CDome();
        ~CDome();

    public:
        virtual void   Continue()      override;
        virtual size_t GetNumStrands() const final { return DomeMappings::c_num_strands; }

    public:
        enum Routine
        {
            // solid
            RoutineCyclePallete,
            RoutineCyclePalleteDimensional,
            RoutineCyclePalleteShapes,

            // complex
            RoutineSpin,
            RoutineBalls,
            RoutineRain,
            RoutineRings,
            RoutineRubics,
            RoutineGlareShapes,
            RoutineCrawlHex,
            RoutineStars,
            RoutineAttack,
            RoutineTurn,
            RoutineSparkle,
            RoutineSparkleColors,

            RoutineQty,
            RoutineNone,
            RoutineSolid,
            RoutineTest,
        };
        static constexpr size_t c_solid_routine_qty = 3;
        static constexpr size_t c_complex_routine_qty = RoutineQty - c_solid_routine_qty;
        static constexpr Routine c_initial_routine = RoutineStars;
        bool IsShapeRoutine(Routine routine);
        CPixelArrayLegs* GetShape(size_t index) { return m_shapes[index]; }

    private:
        Routine m_dome_routine   = RoutineNone;
        size_t  m_routine_end_ms = 0;
        Routine GetNextRoutine();
        void    AdvanceRoutine();
        void    TransitionOut();

    private:
        CPixelArrayLegs* m_shapes[DomeMappings::c_num_shapes] = {};

    private:
        static CMemoryPool<CDome, 1> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CDome*>(ptr));
        }

    private:
        static DomeMappings::Mappings s_mappings;
};

#endif // GEOM_DOME
