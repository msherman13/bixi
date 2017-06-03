#include "PixelArray.h"
#include "FastLED.h"
#include "Logging.h"
#include "Routine.h"
#include "RoutineGlare.h"
#include "RoutineCrawl.h"
#include "RoutineSticks.h"
#include "RoutineSwipe.h"
#include "RoutineFire.h"

CPixelArray::CPixelArray(CRGB* leds, Config config) :
    m_pixels(leds)
{
    m_owner = true;

    Init(config);

    char logstr[256];
    sprintf(logstr, "CPixelArray::CPixelArray: Constructed parent array of length %u", GetSize());
    CLogging::log(logstr);
}

CPixelArray::CPixelArray(CPixelArray* pixels) :
    CPixelArray(pixels, pixels->GetSize(), 0, pixels->NumLegs(), 0)
{
}

CPixelArray::CPixelArray(CPixelArray* pixels, size_t len, size_t offset, size_t num_legs, size_t leg_offset) :
    m_pixels(pixels->GetRaw()),
    m_num_legs(num_legs),
    m_length(len),
    m_coordinates(pixels->m_coordinates + offset),
    m_locations(pixels->m_locations + offset)
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = pixels->m_legs[i + leg_offset];
    }

    char logstr[256];
    sprintf(logstr, "CPixelArray::CPixelArray: Constructed child array of length %u", GetSize());
    CLogging::log(logstr);
}

CPixelArray::~CPixelArray()
{
    ClearRoutines();

    if(m_owner == true)
    {
        delete[] m_coordinates;
        delete[] m_locations;
        for(size_t i=0;i<NumLegs();i++)
        {
            delete m_legs[i];
        }
    }
}

void CPixelArray::Init(Config config)
{
    m_num_legs = config.m_num_legs;

    if(NumLegs() == 0)
    {
        return;
    }

    size_t length[config.m_num_legs] = {};

    m_length = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        length[i]  = abs((int)config.m_end_index[i] - (int)config.m_start_index[i]) + 1;
        m_length  += length[i];
    }

    m_locations      = new size_t[GetSize()];
    m_coordinates    = new Coordinate[GetSize()];

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        bool forward = config.m_start_index[i] <= config.m_end_index[i];
        m_legs[i]    = new CPixelArray(this, length[i], index);

        for(size_t j=0;j<length[i];j++)
        {
            m_locations[index++] = config.m_start_index[i] + (forward ? j : -j);
            m_legs[i]->SetLocation(j, config.m_start_index[i] + (forward ? j : -j));
        }
    }

    MapCoordinates(config);

    char logstr[256];
    sprintf(logstr, "CPolygon::CPolygon: Initialized shape with "
            "%u legs", NumLegs(), GetSize());
    CLogging::log(logstr);
}

void CPixelArray::MapCoordinates(Config config)
{
    if(config.m_auto_coordinates == true)
    {
        AutoMapCorners(config);
    }

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        const size_t length = m_legs[i]->GetSize();
        Coordinate&  start  = config.m_start_coordinate[i];
        Coordinate&  end    = config.m_end_coordinate[i];
        const double x_step = (end.x - start.x) / length;
        const double y_step = (end.y - start.y) / length;

        for(size_t j=0;j<length;j++)
        {
            Coordinate& this_coord = m_coordinates[index++];
            this_coord.x           = start.x + j * x_step;
            this_coord.y           = start.y + j * y_step;
        }
    }
}

// assume regular polygon, map corners to coordinates
void CPixelArray::AutoMapCorners(Config config)
{
    const bool   side_at_edge    = NumLegs() == 4 || NumLegs() == 8;
    const double center_distance = side_at_edge ?
                                   0.50 / cos(180 / NumLegs()) :
                                   0.50;

    for(size_t i=0;i<NumLegs();i++)
    {
        Coordinate& start_corner = config.m_start_coordinate[i];
        const double pi          = 3.14159265358979323846;
        start_corner.x           = cos(2 * pi * i / NumLegs()) * config.m_scale + config.m_origin.x;
        start_corner.y           = center_distance * sin(2 * pi * i / NumLegs()) * config.m_scale + config.m_origin.y;

        config.m_end_coordinate[i > 0 ? i - 1 : NumLegs() - 1] = start_corner;
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

    char logstr[256];
    sprintf(logstr, "CPixelArray::ExitRoutine: Exiting routine");
    CLogging::log(logstr);

    delete m_routine;

    m_routine = nullptr;
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

    CLogging::log("CPixelArray::StartRoutineSolid: Starting routine");

    SetAllPixels(rgb);
}

void CPixelArray::StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineGlare: Starting routine glare");

    m_routine = new CRoutineGlare(this, base_color, q, forward, period_sec);
}

void CPixelArray::StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineCrawl: Starting routine Crawl");

    m_routine = new CRoutineCrawl(this, base_color, width, start_offset, forward, period_sec);
}

void CPixelArray::StartRoutineSticks(size_t num_sticks)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineSticks: Starting routine Sticks");

    m_routine = new CRoutineSticks(this, num_sticks);
}

void CPixelArray::StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ClearRoutines();

    CLogging::log("CPixelArray::StartRoutineGlareLegs: Starting routine GlareLegs");

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->StartRoutineGlare(base_color, q, forward, period_sec);
    }
}

void CPixelArray::StartRoutineSwipe(size_t q, uint32_t period_sec)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineSwipe: Starting routine Swipe");

    m_routine = new CRoutineSwipe(this, q, period_sec);
}

void CPixelArray::StartRoutineFire()
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineFire: Starting routine Fire");

    m_routine = new CRoutineFire(this);
}

void CPixelArray::Continue()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->Continue();
    }

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
