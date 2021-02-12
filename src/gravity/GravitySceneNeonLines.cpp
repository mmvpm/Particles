#include "gravity/GravitySceneNeonLines.hpp"

using namespace sf;

void GravitySceneNeonLines::allocate_field() {
    // быстрое выделение двумерного массива
    field = new int* [width];
    field[0] = new int[width * height];
    for (int i = 1; i < width; i++) {
        field[i] = field[i - 1] + height;
    }
}

void GravitySceneNeonLines::clear_field() {
    // очищаем массив от результатов предыдущих запусков функции
    memset(field[0], 0, width * height * sizeof(int));
}

GravitySceneNeonLines::GravitySceneNeonLines(const GravitySceneConfig& config) :
    GravitySceneLines(config) {
    allocate_field();
}

GravitySceneNeonLines::GravitySceneNeonLines(int width, int height, GravityModel model) :
    GravitySceneLines(width, height, model) {
    allocate_field();
}

void GravitySceneNeonLines::bresenham_algorithm(const std::vector<Particle>& particles) {
    for (auto& particle : particles) {
        Point pos = point_from_model(particle.position);
        // рисуем половину от particle.direction
        Point first = pos - 0.25 * particle.direction;
        Point last = first + 0.5 * particle.direction;

        // написано без ОО-подхода ради производительности
        int delta_x = last.x - first.x;
        int delta_y = last.y - first.y;
        int distance = std::max(std::abs(delta_x), std::abs(delta_y));

        auto sign = [](int x) -> int {
            return x < 0 ? -1 : +1;
        };

        double step_x = sign(delta_x) * std::fmin(1.0, (double) abs(delta_x) / abs(delta_y));
        double step_y = sign(delta_y) * std::fmin(1.0, (double) abs(delta_y) / abs(delta_x));

        double error_x = 0;
        double error_y = 0;

        int current_x = first.x;
        int current_y = first.y;

        for (int i = 0; i < distance; ++i) {
            if (0 <= current_x && current_x < width &&
                0 <= current_y && current_y < height) {
                field[current_x][current_y]++;
            }
            error_x += step_x;
            error_y += step_y;
            current_x += (int) error_x;
            current_y += (int) error_y;
            error_x -= (int) error_x;
            error_y -= (int) error_y;
        }
    }
}

GravityScene::vertices_with_type GravitySceneNeonLines::get_vertices(const std::vector<Particle> &particles) {
    auto sigmoid = [](double x) -> double {
        return 1 / (1 + std::pow(M_E, -x)); // in [-1, 1]
    };

    clear_field();
    bresenham_algorithm(particles);

    std::vector<Vertex> vertices;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (field[x][y] > 0) {
                // color_estimation in [-white_bound / 2, white_bound / 2]
                int color_estimation = std::min(white_bound,  field[x][y]) - white_bound / 2;
                double saturation = 1 - sigmoid(color_estimation); // HSV-saturation

                // уменьшение насыщенности в формате HSV (цвет становится более белым)
                Color color = particle_color;
                int max_component = std::max(std::max(color.r, color.g), color.b);
                color.r += (1 - saturation) * (max_component - color.r);
                color.g += (1 - saturation) * (max_component - color.g);
                color.b += (1 - saturation) * (max_component - color.b);

                vertices.emplace_back(Vector2f(x, y), color, Vector2f(1, 1));
            }
        }
    }
    return {vertices, Points};
}