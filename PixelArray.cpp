#include "PixelArray.h"
#include "Logging.h"
#include "RoutineTest.h"
#include "RoutineGlare.h"
#include "RoutineCrawl.h"
#include "RoutineSticks.h"
#include "RoutineBall.h"
#include "RoutineBalls.h"
#include "RoutineFire.h"

CMemoryPool<CPixelArray::Block, CPixelArray::Block::c_num_blocks> CPixelArray::Block::s_pool;
CMemoryPool<CPixelArray, CPixelArray::c_alloc_qty>                CPixelArray::s_pool;

CPixelArray::CPixelArray(const CPixelArray& rhs) :
    CPixelArray(rhs.GetRawSize(), rhs.GetSize())
{
    m_length     = rhs.GetSize();
    m_raw_length = rhs.GetRawSize();
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i]   = rhs.GetLocation(i);
        m_coordinates[i] = rhs.GetCoordinate(i);
    }
}

CPixelArray::CPixelArray(size_t physical_len, size_t logical_len) :
    m_block(new Block),
    m_owner(true),
    m_pixels(m_block->m_pixels),
    m_length(logical_len),
    m_locations(m_block->m_locations),
    m_coordinates(m_block->m_coordinates)
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i] = i;
    }
}

CPixelArray::CPixelArray(CPixelArray* pixels, size_t len, size_t offset) :
    m_pixels(pixels->GetRaw()),
    m_length(len == 0 ? pixels->GetSize() : len),
    m_raw_length(pixels->GetRawSize() - offset),
    m_locations(pixels->m_locations + offset),
    m_coordinates(pixels->m_coordinates + offset)
{
}

CPixelArray::~CPixelArray()
{
    ExitRoutine();

    if(m_owner == true)
    {
        delete m_block;
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

void CPixelArray::Copy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        SetPixel(index, rgb);
    }   
}

void CPixelArray::SmartCopy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        
        if(rgb == CRGB(CRGB::Black))
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

void CPixelArray::StartRoutineTest()
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineTest: Starting routine");

    m_routine = new CRoutineTest(this);
}

void CPixelArray::StartRoutineSolid(CRGB rgb)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineSolid: Starting routine");

    SetAllPixels(rgb);
}

void CPixelArray::StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineGlare: Starting routine glare");

    m_routine = new CRoutineGlare(this, base_color, q, forward, period_sec);
}

void CPixelArray::StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineCrawl: Starting routine Crawl");

    m_routine = new CRoutineCrawl(this, base_color, width, start_offset, forward, period_sec);
}

void CPixelArray::StartRoutineSticks(size_t num_sticks)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineSticks: Starting routine Sticks");

    m_routine = new CRoutineSticks(this, num_sticks);
}

void CPixelArray::StartRoutineBall(size_t q, uint32_t period_sec)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineBall: Starting routine Ball");

    m_routine = new CRoutineBall(this, q, period_sec);
}

void CPixelArray::StartRoutineBalls(size_t num_balls)
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineBalls: Starting routine Balls");

    m_routine = new CRoutineBalls(this, num_balls);
}

void CPixelArray::StartRoutineFire()
{
    ExitRoutine();

    CLogging::log("CPixelArray::StartRoutineFire: Starting routine Fire");

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
