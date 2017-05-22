#pragma once

#include <stdlib.h>
#include <stdint.h>

struct CRGB;
class  CRoutine;
class  CPolygon;

class CPixelArray
{
    public:
        static constexpr size_t c_min_num_legs = 1;
        static constexpr size_t c_max_num_legs = 8;

    public:
        struct Coordinate
        {
            double x      = 0.0;
            double y      = 0.0;

            Coordinate() {}

            Coordinate(double x_in, double y_in) :
                x(x_in),
                y(y_in)
            {
            }
        };

        struct Config
        {
            size_t m_num_legs              = 0;
            size_t m_start[c_max_num_legs] = {};
            size_t m_end[c_max_num_legs]   = {};
            double m_scale                 = 1.00;
            Coordinate m_origin;
        };

    public:
        CPixelArray(size_t len); // new underlying pixels
        CPixelArray(CRGB* rgb, size_t len); // reference to external pixels
        CPixelArray(CRGB* rgb, size_t len, Config config); // reference to external pixels
        CPixelArray(CPixelArray* rhs); // reference to external pixels (no copy!)
        CPixelArray(CPixelArray* rhs, Config config); // reference to external pixels, diff config
        ~CPixelArray();

    public:
        void StartRoutineSolid(CRGB rgb);
        void StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec);
        void StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec);
        void StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec);
        void StartRoutineSticks(size_t num_sticks);
        void StartRoutineSwipe(size_t q, uint32_t period_sec);

    public:
        void ExitRoutine();
        void ClearRoutines();
        void Continue();

    public:
        size_t      GetSize()                   { return HasCoordinates() ? Perimeter() : m_length; }
        size_t      GetSize(size_t index)       { return m_legs[index]->GetSize(); }
        size_t      Perimeter()                 { return m_perimeter; }
        CRGB*       GetRaw(size_t index=0);
        size_t      NumLegs()                   { return m_config.m_num_legs; }
        Coordinate& GetCoordinate(size_t index) { return m_coordinates[index]; }
        Config&     GetConfig()                 { return m_config; }

    public:
        CRGB   GetPixel(size_t index);
        void   SetPixel(size_t index, CRGB rgb);
        void   SetAllPixels(CRGB rgb);
        void   Shift(bool forward, size_t amount);
        void   SmartCopy(CPixelArray* rhs, size_t size, size_t offset=0);
        bool   HasCoordinates() { return m_coordinates != nullptr; }

    private:
        void InitPolygon();
        void MapCoordinates(double scale);

    private:
        bool         m_owner       = false;
        CRGB*        m_pixels      = nullptr;
        size_t       m_length      = 0;
        size_t       m_perimeter   = 0;
        CRoutine*    m_routine     = nullptr;

    private:
        Config              m_config;
        size_t*             m_locations            = nullptr;
        Coordinate*         m_coordinates          = nullptr;
        CPixelArray*        m_legs[c_max_num_legs] = {};
};
