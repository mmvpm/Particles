#pragma once

#include "interfaces/IModel.hpp"
#include "particles/ParticlesVector.hpp"

class GravityModel : public IModel {
private:
    Particle center;
    ParticlesVector particles;

    double delta_time   = 1; // delta_time < 1 - замедление
    double current_time = 0; // накапливает прошедшее время

private:
    // << магические константы >>
    const double G = 5e4;
    const double max_F = 10;
    const double friction = 0.96;
    const double radius_shrink = 500;
    const double max_random_shift = 0.5;

public:
    GravityModel(const Particle& center, int particles_number, const Particle& defaultParticle);

    double get_delta_time() const;
    void set_delta_time(double new_value);

    Particle& get_center(); // not const
    const std::vector<Particle>& get_particles() const;

    void update() override;

private:
    void apply_shift(Point& direction) const;
};