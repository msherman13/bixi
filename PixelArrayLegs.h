#pragma once

#include "PixelArray.h"

#include <cmath>

class CPixelArrayLegs : public CPixelArray
{
    public:
        static constexpr size_t c_alloc_qty = 32;

    public:
        CPixelArrayLegs(CPixelArray::Config* config); // owner
        CPixelArrayLegs(CPixelArrayLegs* pixels, size_t len, size_t offset = 0, size_t num_legs=0, size_t leg_offset=0); // reference to external pixels
        virtual ~CPixelArrayLegs();

    public:
        size_t       NumLegs()             const { return m_num_legs; }
        CPixelArray* GetLeg(size_t index)        { return m_legs[index]; }

    public:
        virtual void ExitRoutine();
        virtual void Continue();

    private:
        size_t       m_num_legs             = 0;
        CPixelArray* m_legs[c_max_num_legs] = {};

    private:
        static CMemoryPool<CPixelArrayLegs, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CPixelArrayLegs*>(ptr));
        }
};
