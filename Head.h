#ifdef GEOM_HEAD

#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "HeadMappings.h"

class CRoutine;

class CHead : public CPixelArrayLegs
{
    public:
        static constexpr size_t c_transition_time_ms  = 20 * 1000;

    public:
        CHead();
        ~CHead();

    public:
        virtual void   Continue()      override;
        virtual size_t PixelsPerStrand() const final { return HeadMappings::c_strand_length; }

    private:
        enum Shape
        {
            MouthLeft,
            MouthRight,
            NoseLeft,
            CheekLeft,
            NoseRight,
            CheekRight,
            NoseTop,
            FlameLeft,
            EyeLeft,
            BrowLeft,
            FlameRight,
            EyeRight,
            BrowRight,

            ShapeQty,
            ShapeNull,
        };
        const char* sShape(Shape shape);

    private:
        CPixelArrayLegs* m_shapes[ShapeQty] = {};

    public:
        CPixelArrayLegs* GetNoseLeft()  { return m_shapes[NoseLeft];  }
        CPixelArrayLegs* GetNoseRight() { return m_shapes[NoseRight]; }
        CPixelArrayLegs* GetNoseTop()   { return m_shapes[NoseTop];   }

    private:
        static CMemoryPool<CHead, 1> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CHead*>(ptr));
        }

    private:
        static HeadMappings::Mappings s_mappings;
};

#endif // GEOM_HEAD
