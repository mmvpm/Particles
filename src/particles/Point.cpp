#include "particles/Point.hpp"

Point::Point(double x, double y) : x(x), y(y) {}

Point Point::operator-() const {
    return {-x, -y};
}

Point Point::operator+(const Point& other) const {
    return {x + other.x, y + other.y};
}

Point Point::operator-(const Point& other) const {
    return *this + (-other);
}

void Point::operator+=(const Point& other) {
    x += other.x;
    y += other.y;
}

void Point::operator*=(double k) {
    x *= k;
    y *= k;
}

Point operator*(double k, const Point& point) {
    return {k * point.x, k * point.y};
}

double Point::norm2() const {
    return x * x + y * y;
}

bool Point::equal(const Point& other) const {
    return std::abs(x - other.x) < precision
        && std::abs(y - other.y) < precision;
}

double Point::distance2(const Point& other) const {
    return (*this - other).norm2();
}

Point Point::normalize() {
    return (1 / std::sqrt(norm2())) * (*this);
}

std::pair<double, double> Point::to_pair() const {
    return {x, y};
}