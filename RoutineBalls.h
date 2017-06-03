#pragma once

#include "stdint.h"

class CRoutineBall;
class CPixelArray;

class CRoutineBalls : public CRoutine
{
    public:
        static constexpr size_t c_max_num_balls = 16;
        static constexpr size_t c_min_q         = 20;
        static constexpr size_t c_max_q         = 60;
        static constexpr size_t c_min_period    = 1;
        static constexpr size_t c_max_period    = 10;

    public:
        CRoutineBalls(CPixelArray* pixels, size_t num_balls);
        ~CRoutineBalls();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Balls"; }

    private:
        void InitBalls();

    private:
        size_t        m_num_balls = 0;
        CRoutineBall* m_balls[c_max_num_balls] = {};
        CPixelArray   m_buffer;
};
