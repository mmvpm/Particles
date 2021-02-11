#pragma once

#include "interfaces/IModel.hpp"
#include "particles/ParticlesVector.hpp"

class GravityModel : public IModel {
private:
    Particle center;
    ParticlesVector particles;

private:
    const double G = 5e4;
    const double max_F = 10;
    const double friction = 0.96;
    const double quantum_radius = 500;
    const double max_random_shift = 0.5;

public:
    GravityModel(const Particle& center, int particlesNumber, const Particle& defaultParticle);

    Particle& get_center();
    std::vector<Particle> get_particles() const;

    void update() override;

private:
    void apply_shift(Point& direction) const;
};