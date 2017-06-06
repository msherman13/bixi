#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "DomeMappings.h"

class CRoutine;

class CDome : public CPixelArray
{
    public:
        CDome();
        ~CDome();

    public:
        virtual void Continue()        override;
        virtual void ExitRoutine()     override;
        virtual bool RoutineDone()     override;
        virtual void ShutdownRoutine() override;

    private:
        CPixelArray* m_shapes[DomeMappings::c_num_shapes] = {};

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

};
