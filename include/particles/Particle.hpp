#pragma once

#include "Point.hpp"

struct Particle {
    Point position = {0, 0};
    Point direction = {0, 0};
    double mass = 1;
};