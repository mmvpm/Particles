#include "gravity/GravityScene.hpp"

using namespace sf;

GravityScene::GravityScene(const GravitySceneConfig& config) :
    width(config.screen_width),
    height(config.screen_height),
    model(
        std::move(GravityModel(
            config.center,
            config.particles_number,
            config.default_particle
        ))
    ),
    center_color(config.center_color),
    title(config.scene_name),
    frame_delay(config.frame_delay),
    gradient(config.particle_colors) {}

GravityScene::GravityScene(int width, int height, GravityModel model) :
    width(width), height(height), model(std::move(model)) {}

void GravityScene::run() {
    RenderWindow window(VideoMode(width, height), title);

    auto get_mouse_position = [&]() -> Point {
        Vector2i pos = Mouse::getPosition(window);
        return Point(pos.x, pos.y);
    };

    bool pressed_on_slider = false;
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
                    if (seek_bar.is_on_slider(get_mouse_position())) {
                        pressed_on_slider = true;
                    }
                }
                if (event.type == Event::MouseButtonReleased) {
                    pressed_on_slider = false;
                    left_mouse_button_pressed = false;
                }
            }
        }
        // center of mass follows the user's mouse
        if (left_mouse_button_pressed && !pressed_on_slider) {
            model.get_center().position = point_from_scene(get_mouse_position());
        }
        // updating state of the slider
        if (pressed_on_slider) {
            seek_bar.set_position(get_mouse_position());
            model.set_delta_time(seek_bar.get_value());
        }
        // seek_bar rendering
        for (const auto& shape : seek_bar.get_shapes()) {
            window.draw(shape);
        }

        const std::vector<Particle>& particles = model.get_particles();

        // center of mass rendering
        Vertex center[] = {get_center(model.get_center())};
        window.draw(center, 1, Points);

        // particles rendering
        std::vector<Vertex> points;
        PrimitiveType points_type;
        std::tie(points, points_type) = get_vertices(particles);
        window.draw(points.data(), points.size(), points_type);

        window.display();
        sleep(frame_delay);
        window.clear();

        model.update();
        gradient.update_color();
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
        return {Vector2f(pos.x, pos.y), gradient.get_color(), Vector2f(1, 1)};
    };
    std::vector<Vertex> vertices;
    std::transform(particles.begin(), particles.end(), std::back_inserter(vertices), particle_to_vertex);
    return {vertices, Points};
}