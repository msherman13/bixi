#include "BixiNone.h"

CBixiNone& CBixiNone::Instance()
{
    static CBixiNone bixi;
    return bixi;
}

CBixiNone::CBixiNone() :
    CBixi()
{
}

CBixiNone::~CBixiNone()
{
}

void CBixiNone::Show(CPixelArray*)
{
}
