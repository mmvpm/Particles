#pragma once

#include <cstring>
#include "GravitySceneLines.hpp"

class GravitySceneNeonLines : public GravitySceneLines {
protected:
    int** field;

protected:
    const int white_bound = 10;

private:
    void clear_field();
    void allocate_field();
    void bresenham_algorithm(const std::vector<Particle>& particles);

public:
    GravitySceneNeonLines(const GravitySceneConfig& config);

    GravitySceneNeonLines(int width, int height, GravityModel model);
protected:

    vertices_with_type get_vertices(const std::vector<Particle> &particles) override;
};