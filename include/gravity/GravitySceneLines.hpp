#pragma once

#include "GravityScene.hpp"

class GravitySceneLines : public GravityScene {
private:
    sf::Color line_color = sf::Color::Red;

public:
    GravitySceneLines(int width, int height, GravityModel model);

protected:
    vertices_with_type get_vertices(const std::vector<Particle> &particles) override;
};

