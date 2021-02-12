#include  "particles/ParticlesVector.hpp"

ParticlesVector::ParticlesVector() : data(std::vector<Particle>(0)) {}

ParticlesVector::ParticlesVector(std::vector<Particle> data) : data(std::move(data)) {}

ParticlesVector::ParticlesVector(int particlesNumber, const Particle& defaultParticle) {
    data = std::vector<Particle> (particlesNumber, defaultParticle);
}

const std::vector<Particle>& ParticlesVector::get_particles() const {
    return data;
}

void ParticlesVector::update_with(const std::function<void(Particle&)>& function) {
    std::for_each(data.begin(), data.end(), function);
}