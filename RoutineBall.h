#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"
#include "PixelArray.h"

class CRoutineBall : public CRoutine
{
    public:
        static constexpr float c_frame_size = 4.0;
        static constexpr float c_longest_distance = sqrtf(pow(c_frame_size, 2) + pow(c_frame_size, 2));

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
        void                    Init();

    public:
        CPixelArray::Coordinate RecalculateMidpoint();
        CHSV                    RecalculateColor(size_t array, size_t index);

    private:
        CHSV                    m_color;
        size_t                  m_color_index  = 0;
        size_t                  m_q            = 0;
        float                   m_radius       = 0;
        uint32_t                m_period_sec   = 10;
        uint32_t                m_last_run     = 0;
        uint32_t                m_ball_finish = 0;
        size_t                  m_last_side    = 0;
        float                   m_x_step       = 0.0;
        float                   m_y_step       = 0.0;
        float                   m_z_step       = 0.0;
        CPixelArray::Coordinate m_midpoint;
};
