#include "BixiQuickCG.h"

CBixiQuickCG& CBixiQuickCG::Instance()
{
    static CBixiQuickCG bixi;
    return bixi;
}

CBixiQuickCG::CBixiQuickCG() :
    CBixi()
{
}

CBixiQuickCG::~CBixiQuickCG()
{
}

void CBixiQuickCG::Show()
{
}
