#pragma once

#include <SFML/Graphics.hpp>

#include "GravityModel.hpp"
#include "interfaces/IScene.hpp"
#include "GravitySceneConfig.hpp"

class GravityScene : public IScene {
protected:
    int width, height;
    GravityModel model;

protected:
    sf::Color center_color = sf::Color::White;
    sf::Color particle_color = sf::Color::Red;

protected:
    std::string title = "GravityScene";
    sf::Time frame_delay = sf::milliseconds(10);

protected:
    Point point_from_model(const Point &point) const;
    Point point_from_scene(const Point &point) const;

    using vertices_with_type = std::pair<std::vector<sf::Vertex>, sf::PrimitiveType>;

    virtual sf::Vertex get_center(const Particle& center);
    virtual vertices_with_type get_vertices(const std::vector<Particle> &particles);

public:
    GravityScene(int width, int height, GravityModel model);
    GravityScene(const GravitySceneConfig& config);

    void run() override;
};
