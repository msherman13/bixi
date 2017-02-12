#pragma once

class CPixel;
class CPixelArray;
struct CRGB;

class CRoutine
{
    public:
        enum RoutineType
        {
            ROUTINE_HOLD_RAINBOW,
            ROUTINE_CYCLE_RAINBOW,
            ROUTINE_SPARKLE,
            ROUTINE_RAINBOW_SPARKLE,

            ROUTINE_QTY,
            ROUTINE_UNDEF,
        };
        static const char* sRoutineType(RoutineType type);

    public:
        CRoutine(int size);
        virtual ~CRoutine();

    public:
        virtual void Start() = 0;
        virtual void Continue() = 0;
        virtual void Exit();
        virtual RoutineType GetType() = 0;

    public:
        int GetSize();
        bool GetRGB(int index, CRGB& dest);

    protected:
        CPixelArray* m_pPixelArray;
};
