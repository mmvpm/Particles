#include "extensions/Gradient.hpp"

Gradient::MyColor::MyColor(double r, double g, double b) :
    r(r), g(g), b(b) {}

Gradient::MyColor Gradient::from_sf_color(sf::Color color) {
    return MyColor(color.r, color.g, color.b);
}

sf::Color Gradient::from_my_color(Gradient::MyColor color) {
    return sf::Color(color.r, color.g, color.b);
}

Gradient::MyColor Gradient::MyColor::operator+(const Gradient::MyColor& other) const {
    return {
        std::fmax(-255, std::fmin(255, r + other.r)),
        std::fmax(-255, std::fmin(255, g + other.g)),
        std::fmax(-255, std::fmin(255, b + other.b)),
    };
}

Gradient::MyColor Gradient::MyColor::operator-(const Gradient::MyColor& other) const {
    return (*this) + (-1) * other;
}

Gradient::MyColor operator*(double k, const Gradient::MyColor& color) {
    return {
        std::fmax(-255, std::fmin(255, k * color.r)),
        std::fmax(-255, std::fmin(255, k * color.g)),
        std::fmax(-255, std::fmin(255, k * color.b)),
    };
}

Gradient::Gradient(const std::vector<sf::Color>& sf_colors) {
    std::transform(sf_colors.begin(), sf_colors.end(),
        std::back_inserter(colors), from_sf_color
    );
}

void Gradient::update_color() {
    current_time += 1;
    if (current_time == one_step_time) {
        current_time = 0;
        // moving through the loop
        current_index = (current_index + 1) % colors.size();
    }
}

sf::Color Gradient::get_color() const {
    double k = (double) current_time / one_step_time;
    int next_index = (current_index + 1) % colors.size();
    MyColor delta_color = (colors[next_index] - colors[current_index]);
    return from_my_color(
        colors[current_index] + k * delta_color
    );
}