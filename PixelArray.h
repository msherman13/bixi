#pragma once

#include "FastLED.h"
#include "MemoryPool.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

class  CRoutine;

class CPixelArray
{
    public:
        static constexpr size_t c_max_num_legs   = 128;
        static constexpr size_t c_alloc_qty      = c_max_num_legs + 16;

    public:
        struct Coordinate
        {
            float x      = -10.0; // just somewhere out of the frame
            float y      = -10.0; // just somewhere out of the frame

            Coordinate() {}

            Coordinate(const Coordinate& rhs) :
                Coordinate(rhs.x, rhs.y)
            {
            }

            Coordinate(float x_in, float y_in) :
                x(x_in),
                y(y_in)
            {
            }
        };

        struct Block
        {
            static constexpr size_t c_pixels_per_block = 6000;
            static constexpr size_t c_num_blocks = 2;

            static CMemoryPool<Block, c_num_blocks> s_pool;

            CRGB                    m_pixels[c_pixels_per_block];

            void* operator new(size_t)
            {
                return s_pool.alloc();
            }

            void operator delete(void* ptr)
            {
                s_pool.free(reinterpret_cast<Block*>(ptr));
            }
        };

        struct Config
        {
            size_t     m_physical_size               = Block::c_pixels_per_block;
            size_t     m_logical_size                = Block::c_pixels_per_block;
            size_t     m_num_legs                    = 0; // TODO: put into legs module
            size_t     m_leg_offset[c_max_num_legs]  = {};
            size_t     m_leg_size[c_max_num_legs]    = {};

            virtual size_t GetLocation(size_t index)
            {
                return index;
            }

            virtual CPixelArray::Coordinate GetCoordinate(size_t index)
            {
                return CPixelArray::Coordinate();
            }

            virtual bool ApplyGamma(size_t index)
            {
                return true;
            }

            virtual ~Config()
            {
            }
        };

    public:
        CPixelArray(const char* name, Config* config); // owner
        CPixelArray(const CPixelArray& rhs); // copy-ctor creates new underlying pixels (owner)
        CPixelArray(const char* name, CPixelArray* pixels, size_t len=0, size_t offset=0); // reference to external pixels
        virtual ~CPixelArray();

    public:
        void         SetName(const char* name) { strcpy(m_name, name); }
        void         SetRoutine(CRoutine* routine);
        virtual void TransitionTo(CRoutine* routine, size_t duration_ms);
        void         FinishTransition();
        virtual void ExitRoutine();
        virtual void Continue();
        size_t       RoutineStartMs();
        bool         InRoutine()      { return m_routine != nullptr; }
        bool         InTransition()   { return m_next_routine != nullptr; }

    public:
        size_t         GetSize() const                               { return m_length; }
        CRGB*          GetRaw(size_t index=0)                        { return &m_pixels[index]; }
        size_t         GetRawSize() const                            { return m_raw_length; }
        virtual size_t GetNumStrands() const                         { return 1; }
        Coordinate     GetCoordinate(size_t index) const             { return m_config->GetCoordinate(IndexOffset(index)); }
        size_t         GetLocation(size_t index) const               { return m_config->GetLocation(IndexOffset(index)); }
        bool           ApplyGamma(size_t index) const                { return m_config->ApplyGamma(IndexOffset(index)); }
        size_t         IndexOffset(size_t index) const               { return index + m_offset; }
        const char*    GetName() const                               { return m_name; }

    public:
        void        SetSize(size_t len)                           { m_length = len; }
        void        SetRaw(CRGB* pixels)                          { m_pixels = pixels; }
        void        SetRawSize(size_t len)                        { m_raw_length = len; }
        void        SetOffset(size_t val)                         { m_offset = val; }

    public:
        CRGB    GetPixel(size_t index);
        void    SetPixel(size_t index, CRGB rgb);
        CRGB    GetPixelRaw(size_t index);
        void    SetPixelRaw(size_t index, CRGB rgb);
        void    BlendPixel(size_t index, CRGB rgb, float weight);
        void    SetAllPixels(CRGB rgb);
        void    Copy(CPixelArray* rhs, size_t size, size_t offset=0);
        void    SmartCopy(CPixelArray* rhs, size_t size, size_t offset=0);
        Config* GetConfig() const { return m_config; }
        size_t  GetOffset() const { return m_offset; }

    public:
        static CRGB Blend(const CRGB& lhs, const CRGB& rhs, float rhs_weight);

    protected:
        Block* m_block      = nullptr;
        bool   m_owner      = false;
        CRGB*  m_pixels     = nullptr;
        size_t m_length     = 0;
        size_t m_raw_length = 0;

    protected:
        Config* m_config = nullptr;
        size_t m_offset = 0;

    private: static CMemoryPool<CPixelArray, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t size)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CPixelArray*>(ptr));
        }

    protected:
        char      m_name[32]          = {};
        CRoutine* m_routine           = nullptr;
        CRoutine* m_next_routine      = nullptr;
};
