#include "gravity/GravityModel.hpp"

GravityModel::GravityModel(const Particle& center, int particlesNumber, const Particle& defaultParticle)
    : center(center), particles(particlesNumber, defaultParticle) {}

Particle& GravityModel::get_center() {
    return center;
}

std::vector<Particle> GravityModel::get_particles() const {
    return particles.get_particles();
}

void GravityModel::update()  {
    particles.update_with([&](Particle& particle) {
        if (!particle.position.equal(center.position)) {
            double radius2 = particle.position.distance2(center.position); // r^2
            double F = std::fmin(max_F, G * center.mass / radius2); // F = G * m / r^2
            Point F_direction = F * (center.position - particle.position).normalize();
            particle.direction += F_direction;

            // допплнительная обработка для большей реалистичности
            if (particle.direction.norm2() <= quantum_radius && particle.direction.norm2() > radius2) {
                particle.direction = std::sqrt(radius2) * particle.direction.normalize();
            }
        }

        apply_shift(particle.direction);
        particle.position += particle.direction;
    });
}

void GravityModel::apply_shift(Point& direction) const {
    // random_double() in [0, max_random_shift]
    auto random_double = [&]() -> double {
        return max_random_shift * rand() / RAND_MAX;
    };
    direction += {random_double(), random_double()};
    direction *= friction;
}
