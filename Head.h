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

    public:
        CPixelArrayLegs* GetNoseLeft()  { return m_nose_left; }
        CPixelArrayLegs* GetNoseRight() { return m_nose_right; }
        CPixelArrayLegs* GetNoseTop()   { return m_nose_top; }

    private:
        CPixelArrayLegs* m_nose = nullptr;
        CPixelArrayLegs* m_mouth_left = nullptr;
        CPixelArrayLegs* m_mouth_right = nullptr;
        CPixelArrayLegs* m_nose_left = nullptr;
        CPixelArrayLegs* m_nose_right = nullptr;
        CPixelArrayLegs* m_nose_top = nullptr;
        CPixelArrayLegs* m_side_left = nullptr;
        CPixelArrayLegs* m_side_right = nullptr;
        CPixelArrayLegs* m_flame_left = nullptr;
        CPixelArrayLegs* m_flame_right = nullptr;

    private:
        enum Shape
        {
            MouthLeft,
            MouthRight,
            NoseLeft,
            NoseRight,
            NoseTop,
            SideLeft,
            FlameLeft,
            SideRight,
            FlameRight,

            ShapeQty,
            ShapeNull,
        };

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
