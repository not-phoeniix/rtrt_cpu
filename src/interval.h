#pragma once

#include <limits>
#define INFINITY_F std::numeric_limits<float>::infinity()

class Interval {
   private:
    float min;
    float max;

   public:
    Interval();
    Interval(float min, float max);

    bool Contains(float x) const;
    bool Surrounds(float x) const;

    float get_size() const { return max - min; }
    float get_max() const { return max; }
    float get_min() const { return min; }

    static const Interval empty;
    static const Interval universe;
};

const inline Interval Interval::empty = Interval(+INFINITY_F, -INFINITY_F);
const inline Interval Interval::universe = Interval(-INFINITY_F, +INFINITY_F);
