#include "gravity/GravityModel.hpp"

GravityModel::GravityModel(const Particle &center, int particles_number, const Particle &defaultParticle)
    : center(center), particles(particles_number, defaultParticle) {}

Particle &GravityModel::get_center() {
    return center;
}

const std::vector<Particle> &GravityModel::get_particles() const {
    return particles.get_particles();
}

void GravityModel::update() {
    particles.update_with([&](Particle &particle) {

        if (!particle.position.equal(center.position)) {
            double radius2 = particle.position.distance2(center.position); // r^2
            double F = std::fmin(max_F, G * center.mass / radius2); // F = G * m / r^2
            Point F_direction = delta_time * F * (center.position - particle.position).normalize();
            particle.direction += F_direction;

            // дополнительная обработка для большей реалистичности
            if (particle.direction.norm2() <= radius_shrink && particle.direction.norm2() > radius2) {
                particle.direction = std::sqrt(radius2) * particle.direction.normalize();
            }
        }

        // смещение происходит не каждый раз (при delta_time < 1)
        if (current_time >= 1) {
            apply_shift(particle.direction);
        }
        particle.position += delta_time * particle.direction;
    });

    if (current_time >= 1) {
        current_time = 0;
    }
    current_time += delta_time;
}

double GravityModel::get_delta_time() const {
    return delta_time;
}

void GravityModel::set_delta_time(double new_value) {
    if (new_value > 1) {
        // для (1.0 <= 1)
        new_value -= precision;
    }
    if (0 <= new_value && new_value <= 1) {
        delta_time = new_value;
    }
}

void GravityModel::apply_shift(Point &direction) const {
    auto random_double = [&]() -> double {
        return max_random_shift * rand() / RAND_MAX;
    };
    direction += Point(random_double(), random_double());
    direction *= friction;
}