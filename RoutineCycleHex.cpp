#include "RoutineCycleHex.h"
#include "PixelArray.h"
#include "Logging.h"

CRoutineCycleHex::CRoutineCycleHex(CPixelArray& pixels) :
    CRoutine(pixels)
{
    char logString[256];
    sprintf(logString, "CRoutineCycleHex::CRoutineCycleHex: Constructing routine");
    CLogging::log(logString);

    CDoubleHex::Config config;

    config.m_start_outer[0]  = 14;
    config.m_end_outer[0]    = 0;
    config.m_start_outer[1]  = 89;
    config.m_end_outer[1]    = 75;
    config.m_start_outer[2]  = 74;
    config.m_end_outer[2]    = 60;
    config.m_start_outer[3]  = 59;
    config.m_end_outer[3]    = 45;
    config.m_start_outer[4]  = 44;
    config.m_end_outer[4]    = 30;
    config.m_start_outer[5]  = 29;
    config.m_end_outer[5]    = 15;

    config.m_start_inner[0]  = 97;
    config.m_end_inner[0]    = 90;
    config.m_start_inner[1]  = 137;
    config.m_end_inner[1]    = 130;
    config.m_start_inner[2]  = 129;
    config.m_end_inner[2]    = 122;
    config.m_start_inner[3]  = 121;
    config.m_end_inner[3]    = 114;
    config.m_start_inner[4]  = 113;
    config.m_end_inner[4]    = 106;
    config.m_start_inner[5]  = 105;
    config.m_end_inner[5]    = 98;

    m_hex = new CDoubleHex(pixels, config);

    //m_hex->SetMode(CDoubleHex::ModeCycle);
    //m_hex->SetMode(CDoubleHex::ModeSolid);
    //m_hex->SetMode(CDoubleHex::ModeBlink);
    //m_hex->SetMode(CDoubleHex::ModeRainbow);
    m_hex->SetMode(CDoubleHex::ModeGlare);
    m_hex->SetDirection(true);
}

CRoutineCycleHex::~CRoutineCycleHex()
{
    delete m_hex;
}

void CRoutineCycleHex::Start()
{
    char logString[256];
    sprintf(logString, "CRoutineCycleHex::Start: Entering routine");
    CLogging::log(logString);

    m_pixels.Reset();

    m_hex->SetBaseColorIndex(ColorPallete::Turquoise);
    m_hex->Start();
}

void CRoutineCycleHex::Continue()
{
    m_hex->Continue();
}
