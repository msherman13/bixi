#pragma once

#include "FastLED.h"
#include "MemoryPool.h"

#include <stdlib.h>
#include <stdint.h>

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

            Coordinate(float x_in, float y_in) :
                x(x_in),
                y(y_in)
            {
            }
        };

        struct Block
        {
            static constexpr size_t c_pixels_per_block = 8000;
            static constexpr size_t c_num_blocks = 1;

            static CMemoryPool<Block, c_num_blocks> s_pool;

            CRGB                    m_pixels[c_pixels_per_block];
            size_t                  m_locations[c_pixels_per_block] = {};
            CPixelArray::Coordinate m_coordinates[c_pixels_per_block];

            void* operator new(size_t)
            {
                return s_pool.alloc();
            }

            void operator delete(void* ptr)
            {
                s_pool.free(reinterpret_cast<Block*>(ptr));
            }
        };

    public:
        CPixelArray(size_t physical_len, size_t logical_len); // owner
        CPixelArray(const CPixelArray& rhs); // copy-ctor creates new underlying pixels (owner)
        CPixelArray(CPixelArray* pixels, size_t len=0, size_t offset=0); // reference to external pixels
        virtual ~CPixelArray();

    public:
        void StartRoutineTest();
        void StartRoutineSolid(CRGB rgb);
        void StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec);
        void StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec);
        void StartRoutineSticks(size_t num_sticks);
        void StartRoutineBall(size_t q, uint32_t period_sec);
        void StartRoutineBalls(size_t num_balls);
        void StartRoutineFire();

    public:
        virtual void ShutdownRoutine();
        virtual bool RoutineDone();
        virtual void ExitRoutine();
        virtual void Continue();

    public:
        size_t      GetSize() const                               { return m_length; }
        CRGB*       GetRaw(size_t index=0)                        { return &m_pixels[index]; }
        size_t      GetRawSize() const                            { return m_raw_length; }
        Coordinate& GetCoordinate(size_t index) const             { return m_coordinates[index]; }
        size_t      GetLocation(size_t index) const               { return m_locations[index]; }

    public:
        void        SetSize(size_t len)                           { m_length = len; }
        void        SetRaw(CRGB* pixels)                          { m_pixels = pixels; }
        void        SetRawSize(size_t len)                        { m_raw_length = len; }
        void        SetLocation(size_t index, size_t loc)         { m_locations[index] = loc; }
        void        SetCoordinate(size_t index, Coordinate coord) { m_coordinates[index] = coord; }
        void        ShiftLocations(size_t amount)                 { m_locations += amount; }
        void        ShiftCoordinates(size_t amount)               { m_coordinates += amount; }

    public:
        CRGB   GetPixel(size_t index);
        void   SetPixel(size_t index, CRGB rgb);
        void   SetAllPixels(CRGB rgb);
        void   Shift(bool forward, size_t amount);
        void   Copy(CPixelArray* rhs, size_t size, size_t offset=0);
        void   SmartCopy(CPixelArray* rhs, size_t size, size_t offset=0);
        bool   HasCoordinates() { return m_coordinates != nullptr; }

    protected:
        Block* m_block      = nullptr;
        bool   m_owner      = false;
        CRGB*  m_pixels     = nullptr;
        size_t m_length     = 0;
        size_t m_raw_length = 0;

    protected:
        size_t*     m_locations   = nullptr;
        Coordinate* m_coordinates = nullptr;

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
        CRoutine* m_routine          = nullptr;
        uint32_t  m_routine_start_ms = 0;
};
