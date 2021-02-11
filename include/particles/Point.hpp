#pragma once

#include <cmath>
#include <utility>

const double precision = 1e-6;

struct Point {
    double x, y;

    Point(double x, double y);

    Point operator-() const;
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;

    void operator+=(const Point& other);
    void operator*=(double k);

    double norm2() const; // norm squared
    bool equal(const Point& other) const;
    double distance2(const Point& other) const; // distance squared

    Point normalize();

    std::pair<double, double> to_pair() const;

    friend Point operator*(double k, const Point& point);
};