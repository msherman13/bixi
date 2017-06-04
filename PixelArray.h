#pragma once

#include <string>
#include <stdlib.h>
#include <stdint.h>

struct CRGB;
class  CRoutine;
class  CPolygon;

class CPixelArray
{
    public:
        static constexpr size_t c_max_num_legs   = 256;

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

        struct Config
        {
            size_t     m_num_raw_pixels        = 0;
            size_t     m_num_legs              = 0;
            size_t     m_start_index[c_max_num_legs] = {};
            size_t     m_end_index[c_max_num_legs]   = {};
            Coordinate m_start_coordinate[c_max_num_legs];
            Coordinate m_end_coordinate[c_max_num_legs];

            // optional: used for automatic coordinate mapping of polygons
            bool       m_auto_coordinates      = false;
            Coordinate m_origin;
            float      m_scale                 = 1.00;

            virtual bool isComplete() { return false; }

            virtual ~Config()
            {
            }
        };

        // necessary for map projection method
        struct CompleteConfig : public Config
        {
            static constexpr size_t c_max_num_logical_pixels = 10000;

            size_t m_num_logical_pixels = 0;

            size_t* m_location = nullptr;

            // note that the below uses logical indexing (not raw)
            Coordinate* m_coordinate = nullptr;

            CompleteConfig() :
                Config(),
                m_location(new size_t[c_max_num_logical_pixels]),
                m_coordinate(new Coordinate[c_max_num_logical_pixels])
            {
            }

            CompleteConfig(const CompleteConfig& rhs) :
                Config(rhs),
                m_num_logical_pixels(rhs.m_num_logical_pixels),
                m_location(new size_t[c_max_num_logical_pixels]),
                m_coordinate(new Coordinate[c_max_num_logical_pixels])
            {
                for(size_t i=0;i<m_num_logical_pixels;i++)
                {
                    m_location[i]   = rhs.m_location[i];
                    m_coordinate[i] = rhs.m_coordinate[i];
                }
            }

            virtual ~CompleteConfig()
            {
                delete[] m_location;
                delete[] m_coordinate;
            }

            virtual bool isComplete() { return true; }
        };

    public:
        CPixelArray(size_t len); // owner
        CPixelArray(Config config); // owner
        CPixelArray(CompleteConfig config); // owner
        CPixelArray(const CPixelArray& rhs); // copy-ctor creates new underlying pixels (owner)
        CPixelArray(CPixelArray* pixels); // reference to external pixels
        CPixelArray(CPixelArray* pixels, size_t len, size_t offset = 0, size_t num_legs=0, size_t leg_offset=0); // reference to external pixels
        virtual ~CPixelArray();

    public:
        void StartRoutineSolid(CRGB rgb);
        void StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec);
        void StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec);
        void StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec);
        void StartRoutineSticks(size_t num_sticks);
        void StartRoutineBall(size_t q, uint32_t period_sec);
        void StartRoutineBalls(size_t num_balls);
        void StartRoutineFire();

    public:
        void ExitRoutine();
        void ClearRoutines();
        virtual void Continue();

    public:
        size_t      GetSize() const                               { return m_length; }
        size_t      GetSize(size_t index) const                   { return m_legs[index]->GetSize(); }
        CRGB*       GetRaw(size_t index=0);
        size_t      GetRawSize() const                            { return m_raw_size; }
        size_t      NumLegs()                                     { return m_num_legs; }
        Coordinate& GetCoordinate(size_t index) const             { return m_coordinates[index]; }
        size_t      GetLocation(size_t index) const               { return m_locations[index]; }
        void        SetLocation(size_t index, size_t loc)         { m_locations[index] = loc; }
        void        SetCoordinate(size_t index, Coordinate coord) { m_coordinates[index] = coord; }

    public:
        CRGB   GetPixel(size_t index);
        void   SetPixel(size_t index, CRGB rgb);
        void   SetAllPixels(CRGB rgb);
        void   Shift(bool forward, size_t amount);
        void   Copy(CPixelArray* rhs, size_t size, size_t offset=0);
        void   SmartCopy(CPixelArray* rhs, size_t size, size_t offset=0);
        bool   HasCoordinates() { return m_coordinates != nullptr; }

    private:
        void Init(Config* config);
        void HandleCompleteConfig(CompleteConfig* config);
        void MapCoordinates(Config* config);
        void AutoMapCorners(Config* config);

    private:
        bool         m_owner       = false;
        CRGB*        m_pixels      = nullptr;
        size_t       m_length      = 0;
        size_t       m_raw_size    = 0;

    private:
        size_t              m_num_legs             = 0;
        size_t*             m_locations            = nullptr;
        Coordinate*         m_coordinates          = nullptr;
        CPixelArray*        m_legs[c_max_num_legs] = {};

    protected:
        CRoutine*    m_routine = nullptr;
};
