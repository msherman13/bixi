#pragma once

#include <stdlib.h>

class CPixelArray;
class CRoutine;

class CDome
{
    public:
        static constexpr size_t c_num_shapes = 4;

    public:
        CDome(CPixelArray* pixels);
        ~CDome();

    public:
        void StartRoutineSwipe();

    public:
        void ExitRoutine();
        void Continue();

    private:
        CPixelArray* m_shapes[c_num_shapes] = {};
        CRoutine*    m_routine              = nullptr;
};
