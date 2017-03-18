#pragma once

#include <stdlib.h>

class CPixel;
class CPixelArray;
struct CRGB;

class CRoutine
{
    public:
        enum RoutineType
        {
            HoldRainbow,
            CycleRainbow,
            Sparkle,
            RainbowSparkle,
            Grow,

            RoutineQty,
            RoutineUndef,
        };
        static const char* sRoutineType(RoutineType type);

    public:
        CRoutine(size_t size);
        virtual ~CRoutine();

    public:
        virtual void Start() = 0;
        virtual void Continue() = 0;
        virtual void Exit();
        virtual RoutineType GetType() = 0;

    public:
        size_t GetSize();
        bool GetRGB(size_t index, CRGB& dest);

    protected:
        CPixelArray* m_pPixelArray;
};
