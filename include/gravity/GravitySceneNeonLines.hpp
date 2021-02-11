#pragma once

#include "GravitySceneLines.hpp"

class GravitySceneNeonLines : public GravitySceneLines {
protected:
    int** field;

protected:
    const int white_bound = 10;

private:
    sf::Color line_color = sf::Color::Red;

public:
    GravitySceneNeonLines(int width, int height, GravityModel model);

protected:
    vertices_with_type get_vertices(const std::vector<Particle> &particles) override;
};