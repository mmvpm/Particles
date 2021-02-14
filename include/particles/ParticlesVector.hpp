#pragma once

#include <vector>
#include <algorithm>
#include <functional>

#include "Particle.hpp"

class ParticlesVector {
private:
    std::vector<Particle> data;

public:
    ParticlesVector();
    explicit ParticlesVector(std::vector<Particle> data);
    ParticlesVector(int particlesNumber, const Particle& defaultParticle);

    int particles_number() const;
    const std::vector<Particle>& get_particles() const;

    void update_with(const std::function<void(Particle&)>& function);
};