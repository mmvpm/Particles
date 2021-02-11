#pragma once

#include <cstring>
#include <SFML/Graphics.hpp>

#include "interfaces/IScene.hpp"
#include "GravityModel.hpp"

class GravityScene : public IScene {
protected:
    int width, height;
    GravityModel model;

private:
    sf::Color center_color = sf::Color::White;
    sf::Color particle_color = sf::Color::Red;

protected:
    const std::string title = "GravityScene";
    const sf::Time frame_delay = sf::milliseconds(10);

public:
    GravityScene(int width, int height, GravityModel model);

    void run() override;

protected:
    Point point_from_model(const Point &point) const;
    Point point_from_scene(const Point &point) const;

    using vertices_with_type = std::pair<std::vector<sf::Vertex>, sf::PrimitiveType>;

    virtual sf::Vertex get_center(const Particle& center);
    virtual vertices_with_type get_vertices(const std::vector<Particle> &particles);
};
