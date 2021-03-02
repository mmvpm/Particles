#include "gravity/GravitySceneLines.hpp"

using namespace sf;

GravitySceneLines::GravitySceneLines(const GravitySceneConfig& config) :
    GravityScene(config) {}

GravitySceneLines::GravitySceneLines(int width, int height, GravityModel model) :
    GravityScene(width, height, model) {}

GravityScene::vertices_with_type GravitySceneLines::get_vertices(const std::vector<Particle>& particles) {
    std::vector<Vertex> lines;
    for (auto& particle : particles) {
        Point pos = point_from_model(particle.position);
        // half of the particle.direction
        Point first = pos - 0.25 * particle.direction;
        Point last = first + 0.5 * particle.direction;
        lines.emplace_back(
            Vector2f(first.x, first.y),
            gradient.get_color(),
            Vector2f(1, 1)
        );
        lines.emplace_back(
            Vector2f(last.x, last.y),
            gradient.get_color(),
            Vector2f(1, 1)
        );
    }
    return {lines, Lines};
}