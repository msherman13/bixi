#include "BixiQuickCG.h"
#include "Logging.h"

int main()
{
    CLogging::Init();
    CBixiQuickCG::Instance();

    while(true)
    {
        CBixiQuickCG::Instance().Continue();
    }

    return 0;
}
