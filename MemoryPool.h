#pragma once

#include "stdlib.h"
#include "stdint.h"

#include "Logging.h"

template <typename T, size_t QTY> class CMemoryPool
{
    public:
        CMemoryPool() {}
        ~CMemoryPool() {}

    private:
        using Block = uint8_t[sizeof(T)];
        Block m_blocks[QTY];
        bool  m_in_use[QTY] = {};

    public:
        T* alloc()
        {
            for(size_t i=0;i<QTY;i++)
            {
                if(m_in_use[i] == true)
                {
                    continue;
                }

                m_in_use[i] = true;

                return reinterpret_cast<T*>(m_blocks[i]);
            }

            CLogging::log("CMemoryPool::alloc: ERROR No more free blocks");

            return nullptr;
        }

        void free(T* block)
        {
            auto ptr = reinterpret_cast<uint8_t*>(block);

            for(size_t i=0;i<QTY;i++)
            {
                if(m_blocks[i] != ptr)
                {
                    continue;
                }

                if(m_in_use[i] == false)
                {
                    CLogging::log("CMemoryPool::free: WARN Double-free");
                }

                m_in_use[i] = false;
                return;
            }

            CLogging::log("CMemoryPool::free: ERROR Tried to free unknown block");
        }
};
