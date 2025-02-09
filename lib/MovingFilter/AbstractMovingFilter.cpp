#include "AbstractMovingFilter.hpp"

AbstractMovingFilter::AbstractMovingFilter(size_t window_size)
{
    window.resize(window_size, 0);
    num_valid_samples = 0;
}

void AbstractMovingFilter::add_sample(uint8_t x)
{
    static size_t cursor = 0;

    window[cursor] = x;

    cursor = (cursor + 1) % window.size();

    if (num_valid_samples < window.size())
        num_valid_samples++;
}
