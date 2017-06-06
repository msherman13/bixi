#include "BixiNone.h"
#include "Logging.h"

int main()
{
    CLogging::Init();
    CBixiNone::Instance();

    while(!CBixiNone::Instance().ShuttingDown())
    {
        CBixiNone::Instance().Continue();
    }

    return 0;
}
