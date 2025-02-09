#ifndef MOVING_MIN_FILTER_H
#define MOVING_MIN_FILTER_H

#include "AbstractMovingFilter.hpp"

class MovingMinFilter : public AbstractMovingFilter
{
public:
    MovingMinFilter(size_t window_size);

    /**
     * Returns minimum value of all valid samples in the moving window.
     *
     * \note Returns 0 if empty.
     */
    uint8_t calculate();
};

#endif // MOVING_MIN_FILTER_H