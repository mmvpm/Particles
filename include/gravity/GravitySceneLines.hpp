#pragma once

#include "GravityScene.hpp"

class GravitySceneLines : public GravityScene {
public:
    GravitySceneLines(const GravitySceneConfig& config);
    GravitySceneLines(int width, int height, GravityModel model);

protected:
    vertices_with_type get_vertices(const std::vector<Particle>& particles) override;
};