#ifndef MOVING_MEAN_FILTER_H
#define MOVING_MEAN_FILTER_H

#include "AbstractMovingFilter.hpp"

class MovingMeanFilter : public AbstractMovingFilter
{
public:
    MovingMeanFilter(size_t window_size);
    /**
     * Returns mean value of all valid samples in the moving window rounded.
     */
    uint8_t calculate();
};

#endif // MOVING_MEAN_FILTER_H