#include "PixelArrayLegs.h"
#include "Logging.h"
#include "RoutineGlare.h"

CMemoryPool<CPixelArrayLegs, CPixelArrayLegs::c_alloc_qty> CPixelArrayLegs::s_pool;

CPixelArrayLegs::CPixelArrayLegs(const char* name, Config* config) :
    CPixelArray(name, config),
    m_num_legs(config->m_num_legs)
{
    for(size_t i=0;i<NumLegs();i++)
    {
        char leg_name[32];
        sprintf(leg_name, "%sLeg%u", name, i);
        m_legs[i] = new CPixelArray(leg_name, this, config->m_leg_size[i], config->m_leg_offset[i]);
    }

    char logstr[256];
    sprintf(logstr, "CPixelArrayLegs(%s)::CPixelArrayLegs: Constructed parent array of "
            "logical length %u, physical lenth %u", m_name, GetSize(), GetRawSize());
    CLogging::log(logstr);
}

CPixelArrayLegs::CPixelArrayLegs(const char* name,
                                 CPixelArrayLegs* pixels,
                                 size_t len,
                                 size_t offset,
                                 size_t num_legs,
                                 size_t leg_offset) :
    CPixelArray(name, pixels, len, offset),
    m_num_legs(num_legs)
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i] = pixels->m_legs[i + leg_offset];
    }

    char logstr[256];
    sprintf(logstr, "CPixelArrayLegs(%s)::CPixelArrayLegs: Constructed child array of "
            "logical length %u, physical length %u", m_name, GetSize(), GetRawSize());
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

void CPixelArrayLegs::ExitRoutine()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->ExitRoutine();
    }

    CPixelArray::ExitRoutine();
}

void CPixelArrayLegs::Continue()
{
    for(size_t i=0;i<NumLegs();i++)
    {
        m_legs[i]->Continue();
    }

    CPixelArray::Continue();
}
