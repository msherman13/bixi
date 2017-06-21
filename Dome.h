#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "DomeMappings.h"

class CRoutine;

class CDome : public CPixelArrayLegs
{
    public:
        CDome();
        ~CDome();

    public:
        virtual void Continue()        override;
        virtual void ExitRoutine()     override;

    private:
        CPixelArrayLegs* m_shapes[DomeMappings::c_num_shapes]        = {};
        CPixelArrayLegs* m_inner_hex[DomeMappings::c_num_double_hex] = {};
        CPixelArrayLegs* m_outer_hex[DomeMappings::c_num_double_hex] = {};
        CPixelArrayLegs* m_non_hex[DomeMappings::c_num_non_hex]      = {};

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
