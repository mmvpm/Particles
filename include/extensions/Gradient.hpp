#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Gradient {
public:
    struct MyColor;

private:
    int one_step_time = 255;
    int current_time = 0;
    int current_index = 0;
    std::vector<MyColor> colors;

public:
    Gradient(const std::vector<sf::Color>& sf_colors);

    void update_color();
    sf::Color get_color() const;

private:
    static MyColor from_sf_color(sf::Color color);
    static sf::Color from_my_color(MyColor color);

public:
    struct MyColor {
        double r, g, b;

        MyColor(double r, double g, double b);

        MyColor operator+(const MyColor& other) const;
        MyColor operator-(const MyColor& other) const;
        friend MyColor operator*(double k, const MyColor& color);
    };
};