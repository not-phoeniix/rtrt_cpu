#include "interval.h"

// default to empty interval
Interval::Interval()
  : min(-INFINITY_F),
    max(INFINITY_F) { }

Interval::Interval(float min, float max)
  : min(min),
    max(max) { }

bool Interval::Contains(float x) const {
    return min <= x && x <= max;
}

bool Interval::Surrounds(float x) const {
    return min < x && x < max;
}
