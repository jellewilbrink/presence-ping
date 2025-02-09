#include "MovingMeanFilter.hpp"

#include <cmath>

MovingMeanFilter::MovingMeanFilter(size_t window_size) : AbstractMovingFilter(window_size) {}

uint8_t MovingMeanFilter::calculate()
{
    uint8_t mean = 0;

    double sum = 0;
    for (int i = 0; i < num_valid_samples; i++)
    {
        sum += window[i];
    }

    mean = std::round(sum / num_valid_samples);
    return mean;
}