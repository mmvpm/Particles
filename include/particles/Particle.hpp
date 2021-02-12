#pragma once

#include "Point.hpp"

struct Particle {
    Point position = {0, 0};
    Point start_position = {0, 0};
    Point direction = {0, 0};
    double mass = 1;
    int current_time = 1;

    Particle(const Point& pos = {0, 0}, const Point& dir = {0, 0}, double mass = 1) :
        position(pos), direction(dir), mass(mass), start_position(pos), current_time(1) {}
};