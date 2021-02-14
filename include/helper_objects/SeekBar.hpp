#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "particles/Point.hpp"

class SeekBar {
private:
    int radius;
    Point center_position; // центр слайдера
    Point current_position; // позиция ползунка
    double value = 1; // in [0, 1] - величина сдвига

private:
    const int hit_box = 20; // радиус столкновения

private:
    sf::Color bottom_line_color = sf::Color(255, 255, 255, 70);
    sf::Vector2f slider_size = sf::Vector2f(hit_box / 2, hit_box);
    sf::Color slider_color = sf::Color(100, 100, 100);

public:
    SeekBar(int radius, const Point& center_position);

    double get_value() const;
    void set_position(const Point& new_position);

    bool is_on_slider(const Point& position) const;

    std::vector<sf::RectangleShape> get_shapes() const;
};