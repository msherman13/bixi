#include "BixiQuickCG.h"
#include "Logging.h"

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
