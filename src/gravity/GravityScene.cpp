#include "gravity/GravityScene.hpp"

#include <iostream>

using namespace sf;

GravityScene::GravityScene(int width, int height, GravityModel model)
    : width(width), height(height), model(std::move(model)) {}

void GravityScene::run() {
    RenderWindow window(VideoMode(width, height), title);

    bool left_mouse_button_pressed = false;
    while (window.isOpen()) {
        Event event {};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if ((int) event.key.code == (int) Mouse::Left) {
                if (event.type == Event::MouseButtonPressed) {
                    left_mouse_button_pressed = true;
                }
                if (event.type == Event::MouseButtonReleased) {
                    left_mouse_button_pressed = false;
                }
            }
        }
        // center follows the mouse
        if (left_mouse_button_pressed) {
            Vector2i mouse_position = Mouse::getPosition(window);
            model.get_center().position = point_from_scene(Point(mouse_position.x, mouse_position.y));
        }

        std::vector<Particle> particles = model.get_particles();

        Vertex center[] = {get_center(model.get_center())};
        window.draw(center, 1, Points);

        std::vector<Vertex> points;
        PrimitiveType points_type;
        std::tie(points, points_type) = get_vertices(particles);
        window.draw(&points[0], points.size(), points_type);

        window.display();
        sleep(frame_delay);

        model.update();
        window.clear();
    }
}

Point GravityScene::point_from_model(const Point& point) const {
    return {point.x + width / 2.0, point.y + height / 2.0};
}

Point GravityScene::point_from_scene(const Point& point) const {
    return {point.x - width / 2.0, point.y - height / 2.0};
}

Vertex GravityScene::get_center(const Particle& center) {
    Point pos = point_from_model(center.position);
    return {Vector2f(pos.x, pos.y), center_color, Vector2f(1, 1)};
}

GravityScene::vertices_with_type GravityScene::get_vertices(const std::vector<Particle>& particles) {
    auto particle_to_vertex = [&](const Particle& particle) -> Vertex {
        Point pos = point_from_model(particle.position);
        return {Vector2f(pos.x, pos.y), particle_color, Vector2f(1, 1)};
    };
    std::vector<Vertex> vertices;
    std::transform(particles.begin(), particles.end(), std::back_inserter(vertices), particle_to_vertex);
    return {vertices, Points};
}