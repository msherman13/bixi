#pragma once

#include <stdlib.h>
#include "GridMappings.h"
#include "PixelArrayLegs.h"

class CRoutine;

class CGrid : public CPixelArrayLegs
{
    public:
        CGrid();
        ~CGrid();

    public:
        virtual void Continue();

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

    private:
        static GridMappings::Mappings s_mappings;
};
