#pragma once

#include <SFML/Graphics.hpp>

#include "GravityModel.hpp"
#include "interfaces/IScene.hpp"
#include "GravitySceneConfig.hpp"
#include "helper_objects/SeekBar.hpp"
#include "helper_objects/Gradient.hpp"

class GravityScene : public IScene {
protected:
    int width, height;
    GravityModel model;

protected:
    Gradient gradient = Gradient({ sf::Color::Red });
    sf::Color center_color = sf::Color::White;

protected:
    std::string title = "GravityScene";
    sf::Time frame_delay = sf::milliseconds(10);

protected:
    SeekBar seek_bar = SeekBar(
        100,
        Point(width / 2,height - 100)
    );

protected:
    Point point_from_model(const Point& point) const;
    Point point_from_scene(const Point& point) const;

    using vertices_with_type = std::pair<std::vector<sf::Vertex>, sf::PrimitiveType>;

    virtual sf::Vertex get_center(const Particle& center);
    virtual vertices_with_type get_vertices(const std::vector<Particle>& particles);

public:
    GravityScene(int width, int height, GravityModel model);
    GravityScene(const GravitySceneConfig& config);

    void run() override;
};
