#include "PixelArray.h"
#include "FastLED.h"
#include "Logging.h"
#include "Routine.h"
#include "RoutineGlare.h"
#include "RoutineCrawl.h"
#include "RoutineSticks.h"
#include "RoutineSwipe.h"
#include "RoutineFire.h"

CPixelArray::CPixelArray(size_t len) :
    CPixelArray(new CRGB[len], len)
{
    m_owner = true;
}

CPixelArray::CPixelArray(CRGB* rgb, size_t len) :
    m_pixels(rgb),
    m_length(len)
{
    m_locations = new size_t[GetSize()];
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i] = i;
    }
}

CPixelArray::CPixelArray(CRGB* rgb, size_t len, Config config) :
    m_pixels(rgb),
    m_length(len),
    m_config(config)
{
    Init();
}

CPixelArray::CPixelArray(CPixelArray* rhs) :
    CPixelArray(rhs->GetRaw(), rhs->GetSize())
{
    m_config = rhs->GetConfig();
    Init();
}

CPixelArray::CPixelArray(CPixelArray* rhs, Config config) :
    CPixelArray(rhs->GetRaw(), rhs->GetSize())
{
    m_config = config;

    Init();
}

CPixelArray::~CPixelArray()
{
    if(m_owner == true)
    {
        delete[] m_pixels;
    }

    delete[] m_locations;

    if(HasCoordinates() == true)
    {
        delete[] m_coordinates;
    }

    for(size_t i=0;i<NumLegs();i++)
    {
        delete m_legs[i];
    }
}

void CPixelArray::Init()
{
    size_t length[m_config.m_num_legs] = {};
    m_perimeter = 0;

    for(size_t i=0;i<NumLegs();i++)
    {
        length[i]  = abs((int)m_config.m_end[i] - (int)m_config.m_start[i]) + 1;
        m_perimeter += length[i];
    }

    m_locations      = new size_t[Perimeter()];
    m_coordinates    = new Coordinate[Perimeter()];

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = new CPixelArray(GetRaw(index), length[i]);

        bool forward = m_config.m_start[i] <= m_config.m_end[i];
        for(size_t j=0;j<length[i];j++)
        {
            m_locations[index++] = m_config.m_start[i] + (forward ? j : -j);
        }
    }

    MapCoordinates();

    char logstr[256];
    sprintf(logstr, "CPolygon::CPolygon: Initializing polygon with "
            "%u legs and perimeter %u pixels", NumLegs(), GetSize());
    CLogging::log(logstr);
}

void CPixelArray::MapCoordinates()
{
    if(m_config.m_auto_coordinates == true)
    {
        AutoMapCorners();
    }

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        const size_t length = m_legs[i]->GetSize();
        Coordinate&  start  = m_config.m_corner_coordinates[i];
        Coordinate&  end    = m_config.m_corner_coordinates[i < NumLegs() - 1 ? i + 1 : 0];
        const double x_step = (end.x - start.x) / length;
        const double y_step = (end.y - start.y) / length;
        const double z_step = (end.z - start.z) / length;

        for(size_t j=0;j<length;j++)
        {
            Coordinate& this_coord = m_coordinates[index++];
            this_coord.x           = start.x + j * x_step;
            this_coord.y           = start.y + j * y_step;
            this_coord.z           = start.z + j * z_step;
        }
    }
}

// assume regular polygon, map corners to coordinates
void CPixelArray::AutoMapCorners()
{
    const bool   side_at_edge    = NumLegs() == 4 || NumLegs() == 8;
    const double center_distance = side_at_edge ?
                                   0.50 / cos(180 / NumLegs()) :
                                   0.50;

    for(size_t i=0;i<NumLegs();i++)
    {
        Coordinate& corner = m_config.m_corner_coordinates[i];
        const double pi    = 3.14159265358979323846;
        corner.x           = cos(2 * pi * i / NumLegs()) * m_config.m_scale + m_config.m_origin.x;
        corner.y           = center_distance * sin(2 * pi * i / NumLegs()) * m_config.m_scale + m_config.m_origin.y;
        // TODO: how to map z-axis?
    }
}

CRGB CPixelArray::GetPixel(size_t index)
{
    return m_pixels[m_locations[index]];
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    m_pixels[m_locations[index]] = rgb;
}

void CPixelArray::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

void CPixelArray::Shift(bool forward, size_t amount)
{
    for(size_t it=0;it<amount;it++)
    {   
        CRGB pixel = forward ? GetPixel(GetSize()-1) : GetPixel(0);

        for(size_t i=0;i<GetSize();i++)
        {   
            size_t index = forward ? i : GetSize() - i - 1;
            CRGB buff    = GetPixel(index);
            SetPixel(index, pixel);
            pixel        = buff;
        }   
    }   
}

void CPixelArray::SmartCopy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        if(GetPixel(index) == CRGB(CRGB::Black))
        {
            SetPixel(index, rgb);
        }
    }   
}

void CPixelArray::ExitRoutine()
{
    if(m_routine == nullptr)
    {
        return;
    }

    delete m_routine;
}

void CPixelArray::ClearRoutines()
{
    ExitRoutine();

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->ExitRoutine();
    }   
}

void CPixelArray::StartRoutineSolid(CRGB rgb)
{
    ClearRoutines();

    SetAllPixels(rgb);
}

void CPixelArray::StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    m_routine = new CRoutineGlare(this, base_color, q, forward, period_sec);
}

void CPixelArray::StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    m_routine = new CRoutineCrawl(this, base_color, width, start_offset, forward, period_sec);
}

void CPixelArray::StartRoutineSticks(size_t num_sticks)
{
    ClearRoutines();

    m_routine = new CRoutineSticks(this, num_sticks);
}

void CPixelArray::StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->StartRoutineGlare(base_color, q, forward, period_sec);
    }
}

void CPixelArray::StartRoutineSwipe(size_t q, uint32_t period_sec)
{
    ExitRoutine();

    m_routine = new CRoutineSwipe(this, q, period_sec);
}

void CPixelArray::StartRoutineFire()
{
    ExitRoutine();

    m_routine = new CRoutineFire(this);
}

void CPixelArray::Continue()
{
    if(m_routine == nullptr)
    {
        return;
    }

    m_routine->Continue();
}

CRGB* CPixelArray::GetRaw(size_t index)
{
    return &m_pixels[index];
}
