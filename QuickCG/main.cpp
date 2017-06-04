#include "BixiQuickCG.h"
#include "Logging.h"
#include "MapProjection.h"

int main()
{
    CLogging::Init();
    CBixiQuickCG::Instance();

    while(!CBixiQuickCG::Instance().ShuttingDown())
    {
        CBixiQuickCG::Instance().Continue();
    }

    return 0;
}
