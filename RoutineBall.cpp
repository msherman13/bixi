#include <algorithm>
#include <math.h>

#include "RoutineBall.h"
#include "PixelArray.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "Arduino.h"

CRoutineBall::CRoutineBall(CPixelArray* arrays,
                                 size_t       q,
                                 uint32_t     period_sec) :
    CRoutine(arrays),
    m_q(q),
    m_period_sec(period_sec)
{
    m_last_run = millis();
}

CRoutineBall::CRoutineBall(size_t        num_arrays,
                                 CPixelArray** arrays,
                                 size_t        q,
                                 uint32_t      period_sec) :
    CRoutine(num_arrays, arrays),
    m_q(q),
    m_period_sec(period_sec)
{
    m_last_run = millis();
}

CRoutineBall::~CRoutineBall()
{
}

void CRoutineBall::Continue()
{
    uint32_t now = millis();

    if(m_ball_finish == 0 || now - m_ball_finish >= m_period_sec * 1000)
    {
        m_ball_finish = now;

        size_t side = m_last_side;
        while(side == m_last_side)
        {
            side = rand() % 4;
        }

        m_midpoint.x = ((double)(rand() % 200) / 200) - 1.00;
        m_midpoint.y = ((double)(rand() % 200) / 200) - 1.00;

        m_x_step     = ((double)(rand() % 100) / 100) * 2 / (m_period_sec * 1000);
        m_y_step     = ((double)(rand() % 100) / 100) * 2 / (m_period_sec * 1000);

        switch(side)
        {
            case 0:
                m_midpoint.x = c_frame_size / 2;
                m_x_step     = (2 * -m_midpoint.x) / (m_period_sec * 1000);
                break;
            case 1:
                m_midpoint.x = -c_frame_size / 2;
                m_x_step     = (2 * -m_midpoint.x) / (m_period_sec * 1000);
                break;
            case 2:
                m_midpoint.y = c_frame_size / 2;
                m_y_step     = (2 * -m_midpoint.y) / (m_period_sec * 1000);
                break;
            case 3:
                m_midpoint.y = -c_frame_size / 2;
                m_y_step     = (2 * -m_midpoint.y) / (m_period_sec * 1000);
                break;
        }

        size_t color_index = m_color_index;
        while(color_index == m_color_index)
        {
            color_index = rand() % ColorPallete::Qty;
        }
        m_color_index = color_index;
        m_color = rgb2hsv_approximate(ColorPallete::s_colors[m_color_index]);

        m_last_side = side;
    }

    m_midpoint.x += (double)(now - m_last_run) * m_x_step;
    m_midpoint.y += (double)(now - m_last_run) * m_y_step;

    m_last_run = now;

    CHSV hsv = m_color;

    const double longest_distance = 3.46;

    for(size_t array=0;array<m_num_arrays;array++)
    {
        for(size_t i=0;i<m_arrays[array]->GetSize();i++)
        {
            CPixelArray::Coordinate coord = m_arrays[array]->GetCoordinate(i);
            double x_dist                 = fabs(m_midpoint.x - coord.x);
            double y_dist                 = fabs(m_midpoint.y - coord.y);
            double distance               = sqrt(pow(x_dist, 2) + pow(y_dist, 2)) / longest_distance;
            double brightness             = pow(1 - distance, m_q);
            hsv.val = brightness * 255;
            if(hsv.val < 15)
                hsv.val = 0;

            m_arrays[array]->SetPixel(i, hsv);
        }
    }
}
