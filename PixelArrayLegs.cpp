#include "PixelArrayLegs.h"
#include "Logging.h"
#include "RoutineGlare.h"

CMemoryPool<CPixelArrayLegs, CPixelArrayLegs::c_alloc_qty> CPixelArrayLegs::s_pool;

CPixelArrayLegs::CPixelArrayLegs(Config config) :
    CPixelArray(config.m_physical_size, config.GetLogicalSize()),
    m_num_legs(config.m_num_legs)
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = new CPixelArray(this);
    }

    Init(&config);

    char logstr[256];
    sprintf(logstr, "CPixelArrayLegs::CPixelArrayLegs: Constructed parent array of length %u", GetSize());
    CLogging::log(logstr);
}

CPixelArrayLegs::CPixelArrayLegs(CPixelArrayLegs* pixels, size_t len, size_t offset, size_t num_legs, size_t leg_offset) :
    CPixelArray(pixels),
    m_num_legs(num_legs)
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = pixels->m_legs[i + leg_offset];
    }

    char logstr[256];
    sprintf(logstr, "CPixelArrayLegs::CPixelArrayLegs: Constructed child array of length %u", GetSize());
    CLogging::log(logstr);
}

CPixelArrayLegs::~CPixelArrayLegs()
{
    if(m_owner == true)
    {
        for(size_t i=0;i<NumLegs();i++)
        {
            delete m_legs[i];
        }
    }
}

void CPixelArrayLegs::Init(Config* config)
{
    if(NumLegs() > c_max_num_legs)
    {
        char logstr[256];
        sprintf(logstr, "CPixelArray::Init: ERROR num_legs = %u exceeds maximum of %u. Exiting",
                NumLegs(), c_max_num_legs);
        CLogging::log(logstr);
        exit(-1);
    }

    if(NumLegs() == 0)
    {
        char logstr[256];
        sprintf(logstr, "CPixelArray::Init: ERROR num_legs = %u, must be > 0. Exiting",
                NumLegs());
        CLogging::log(logstr);
        exit(-1);
    }

    size_t length[config->m_num_legs] = {};

    for(size_t i=0;i<NumLegs();i++)
    {
        length[i]  = abs((int)config->m_end_index[i] - (int)config->m_start_index[i]) + 1;
    }

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        bool forward = config->m_start_index[i] <= config->m_end_index[i];
        m_legs[i]->SetRaw(m_pixels);
        m_legs[i]->SetSize(length[i]);
        m_legs[i]->SetRawSize(length[i]);
        m_legs[i]->ShiftLocations(index);
        m_legs[i]->ShiftCoordinates(index);

        for(size_t j=0;j<length[i];j++)
        {
            m_locations[index++] = config->m_start_index[i] + (forward ? j : -j);
            m_legs[i]->SetLocation(j, config->m_start_index[i] + (forward ? j : -j));
        }
    }

    MapCoordinates(config);

    char logstr[256];
    sprintf(logstr, "CPixelArrayLegs::Init: Initialized array with "
            "%u legs", NumLegs());
    CLogging::log(logstr);
}

void CPixelArrayLegs::MapCoordinates(Config* config)
{
    if(config->m_auto_coordinates == true)
    {
        AutoMapCorners(config);
    }

    size_t index = 0;
    for(size_t i=0;i<NumLegs();i++)
    {
        const size_t length = m_legs[i]->GetSize();
        Coordinate&  start  = config->m_start_coordinate[i];
        Coordinate&  end    = config->m_end_coordinate[i];
        const float x_step = (end.x - start.x) / length;
        const float y_step = (end.y - start.y) / length;

        for(size_t j=0;j<length;j++)
        {
            Coordinate& this_coord = m_coordinates[index++];
            this_coord.x           = start.x + j * x_step;
            this_coord.y           = start.y + j * y_step;
        }
    }
}

// assume regular polygon, map corners to coordinates
void CPixelArrayLegs::AutoMapCorners(Config* config)
{
    const bool  side_at_edge    = NumLegs() == 4 || NumLegs() == 8;
    const float center_distance = side_at_edge ?
                                   0.50 / cos(180 / NumLegs()) :
                                   0.50;

    for(size_t i=0;i<NumLegs();i++)
    {
        Coordinate& start_corner = config->m_start_coordinate[i];
        const float pi           = 3.14159265358979323846;
        start_corner.x           = cos(2 * pi * i / NumLegs()) * config->m_scale + config->m_origin.x;
        start_corner.y           = center_distance * sin(2 * pi * i / NumLegs()) * config->m_scale + config->m_origin.y;

        config->m_end_coordinate[i > 0 ? i - 1 : NumLegs() - 1] = start_corner;
    }
}

void CPixelArrayLegs::ExitRoutine()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->ExitRoutine();
    }

    CPixelArray::ExitRoutine();
}

void CPixelArrayLegs::ShutdownRoutine()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->ShutdownRoutine();
    }

    CPixelArray::ShutdownRoutine();
}

bool CPixelArrayLegs::RoutineDone()
{
    bool ret = true;

    if(RunningRoutine() == true)
    {
        return CPixelArray::RoutineDone();
    }

    for(size_t i=0;i<NumLegs();i++)
    {
        ret &= m_legs[i]->RoutineDone();
    }

    return ret;
}

void CPixelArrayLegs::Continue()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->Continue();
    }

    CPixelArray::Continue();
}

void CPixelArrayLegs::StartRoutineGlareLegs(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ExitRoutine();

    CLogging::log("CPixelArrayLegs::StartRoutineGlareLegs: Starting routine GlareLegs");

    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->StartRoutineGlare(base_color, q, forward, period_sec);
    }

    m_routine_start_ms = millis();
}
