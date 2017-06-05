#pragma once

#include <stdlib.h>
#include "PixelArray.h"

class CRoutine;

class CGrid : public CPixelArray
{
    public:
        CGrid();
        ~CGrid();

    private:
        static CMemoryPool<CGrid, 1> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CGrid*>(ptr));
        }
};
