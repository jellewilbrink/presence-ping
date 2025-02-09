#include "MovingMinFilter.hpp"

#include <cmath>

MovingMinFilter::MovingMinFilter(size_t window_size) : AbstractMovingFilter(window_size) {}

uint8_t MovingMinFilter::calculate()
{
    if (num_valid_samples == 0)
        return 0; // By convention

    uint8_t min = 0xFF; // Initialize the the maximim possible value
    for (int i = 0; i < num_valid_samples; i++)
    {
        if (window[i] < min)
            min = window[i];
    }

    return min;
}