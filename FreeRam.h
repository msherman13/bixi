#ifdef __arm__

#include "WProgram.h"
#include <stdlib.h>

// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);

// function from the sdFat library (SdFatUtil.cpp)
// licensed under GPL v3
// Full credit goes to William Greiman.
int FreeRam() {
    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
}

#else

int FreeRam()
{
    return 0;
}

#endif  // __arm__
