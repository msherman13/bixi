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
        virtual size_t GetNumStrands() const final { return HeadMappings::c_num_strands; }

    private:
        CPixelArray* m_mouth_left = nullptr;
        CPixelArray* m_mouth_right = nullptr;
        CPixelArray* m_nose_left = nullptr;
        CPixelArray* m_nose_right = nullptr;
        CPixelArray* m_side_left = nullptr;
        CPixelArray* m_side_right = nullptr;
        CPixelArray* m_flame_left = nullptr;
        CPixelArray* m_flame_right = nullptr;

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
