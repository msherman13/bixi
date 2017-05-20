#include "Polygon.h"
#include "Logging.h"

CPolygon::CPolygon(CPixelArray* pixels, Config& config) :
    m_pixels(pixels),
    m_num_legs(config.m_num_legs)
{
    size_t length[config.m_num_legs] = {};
    size_t perimeter                 = 0;

    for(size_t i=0;i<NumLegs();i++)
    {
        length[i]  = abs((int)config.m_end[i] - (int)config.m_start[i]) + 1;
        perimeter += length[i];
    }

    m_locations      = new size_t[perimeter];
    m_virtual_pixels = new CPixelArray(perimeter);


    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = new CPixelArray(m_virtual_pixels->GetRaw(index), length[i]);

        bool forward = config.m_start[i] <= config.m_end[i];
        for(size_t j=0;j<length[i];j++)
        {
            m_locations[index++] = config.m_start[i] + (forward ? j : -j);
        }
    }

    char logstr[256];
    sprintf(logstr, "CPolygon::CPolygon: Initializing polygon with "
            "%u legs and perimeter %u pixels", NumLegs(), Perimeter());
    CLogging::log(logstr);
}

CPolygon::~CPolygon()
{
    delete m_locations;
    delete m_virtual_pixels;
    for(size_t i=0;i<NumLegs();i++)
    {
        delete m_legs[i];
    }
}

void CPolygon::Show()
{
    for(size_t i=0;i<Perimeter();i++)
    {
        m_pixels.SetPixel(m_locations[i], m_virtual_pixels->GetPixel(i));
    }
}

void CPolygon::ClearRoutines()
{
    m_virtual_pixels->ExitRoutine();

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->ExitRoutine();
    }
}

void CPolygon::Solid(CRGB rgb)
{
    ClearRoutines();

    m_virtual_pixels->StartRoutineSolid(rgb);
}

void CPolygon::Glare(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    m_virtual_pixels->StartRoutineGlare(base_color, q, forward, period_sec);
}

void CPolygon::GlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->StartRoutineGlare(base_color, q, forward, period_sec);
    }
}

void CPolygon::Sticks(size_t num_sticks)
{
    ClearRoutines();

    m_virtual_pixels->StartRoutineSticks(num_sticks);
}

void CPolygon::Continue()
{
    m_virtual_pixels->Continue();

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->Continue();
    }

    Show();
}
