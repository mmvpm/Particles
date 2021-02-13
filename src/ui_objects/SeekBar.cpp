#include "ui_objects/SeekBar.hpp"

using namespace sf;

SeekBar::SeekBar(int radius, const Point& center_position) :
    radius(radius),
    center_position(center_position),
    current_position(center_position.x + radius, center_position.y) {}

double SeekBar::get_value() const {
    return value;
}

void SeekBar::set_position(const Point& new_position) {
    double signed_distance = new_position.x - center_position.x;
    if (std::abs(signed_distance) <= radius) {
        current_position.x = new_position.x;
    }
    else {
        current_position.x = center_position.x + (signed_distance < 0 ? -1 : +1) * radius;
    }
    value = (double) (current_position.x - center_position.x + radius) / (2 * radius);
}

bool SeekBar::is_on_slider(const Point& position) const {
    return current_position.distance2(position) <= hit_box * hit_box;
}

std::vector<RectangleShape> SeekBar::get_shapes() const {
    RectangleShape bottom_line(Vector2f(2 * radius, 1));
    bottom_line.setFillColor(bottom_line_color);
    bottom_line.move(
        center_position.x - radius,
        center_position.y
    );
    RectangleShape slider(slider_size);
    slider.setFillColor(slider_color);
    slider.move(
        current_position.x - slider.getSize().x / 2,
        current_position.y - slider.getSize().y / 2
    );

    return {bottom_line, slider};
}