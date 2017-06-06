#pragma once

#include "PixelArray.h"

#include <cmath>

class CPixelArrayLegs : public CPixelArray
{
    public:
        static constexpr size_t c_alloc_qty = 32;

    public:
        struct Config
        {
            size_t     m_physical_size               = CPixelArray::Block::c_pixels_per_block;
            size_t     m_num_legs                    = 0;
            size_t     m_start_index[c_max_num_legs] = {};
            size_t     m_end_index[c_max_num_legs]   = {};
            Coordinate m_start_coordinate[c_max_num_legs];
            Coordinate m_end_coordinate[c_max_num_legs];

            // optional: used for automatic coordinate mapping of polygons
            bool       m_auto_coordinates = false;
            Coordinate m_origin;
            float      m_scale            = 1.00;

            size_t GetLogicalSize()
            {
                size_t ret = 0;
                for(size_t i=0;i<m_num_legs;i++)
                {
                    ret += std::abs(m_end_index[i] - m_start_index[i]) + 1;
                }
                return ret;
            }

            virtual bool LoadLocationsExternally() { return false; }
            virtual bool LoadCoordsExternally()    { return false; }

            virtual ~Config()
            {
            }
        };

    public:
        CPixelArrayLegs(Config config); // owner
        CPixelArrayLegs(CPixelArrayLegs* pixels, size_t len, size_t offset = 0, size_t num_legs=0, size_t leg_offset=0); // reference to external pixels
        virtual ~CPixelArrayLegs();

    public:
        void StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec);

    public:
        size_t       NumLegs()             const { return m_num_legs; }
        CPixelArray* GetLeg(size_t index)        { return m_legs[index]; }

    public:
        virtual void ExitRoutine();
        virtual void Continue();

    private:
        void Init(Config* config);
        void MapCoordinates(Config* config);
        void AutoMapCorners(Config* config);

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
