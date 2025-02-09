#ifndef ABSTRACT_MOVING_FILTER_H
#define ABSTRACT_MOVING_FILTER_H

#include <stdint.h>
#include <vector>

class AbstractMovingFilter
{
public:
    AbstractMovingFilter(size_t window_size);
    void add_sample(uint8_t x);
    virtual uint8_t calculate() = 0;

protected:
    std::vector<uint8_t> window;
    size_t num_valid_samples;
};

#endif // ABSTRACT_MOVING_FILTER_H
