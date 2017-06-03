#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CPixelArray;

class CRoutineBall : public CRoutine
{
    public:
        static constexpr double c_frame_size = 4.0;

    public:
        CRoutineBall(CPixelArray*    arrays,
                        size_t          q,
                        uint32_t        period_sec);
        CRoutineBall(size_t          num_arrays,
                        CPixelArray**   arrays, // array of ptrs
                        size_t          q,
                        uint32_t        period_sec);
        ~CRoutineBall();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Ball"; }

    private:
        void Init();

    private:
        CHSV                    m_color;
        size_t                  m_color_index  = 0;
        size_t                  m_q            = 0;
        uint32_t                m_period_sec   = 10;
        uint32_t                m_last_run     = 0;
        uint32_t                m_ball_finish = 0;
        size_t                  m_last_side    = 0;
        double                  m_x_step       = 0.0;
        double                  m_y_step       = 0.0;
        double                  m_z_step       = 0.0;
        CPixelArray::Coordinate m_midpoint;
};
