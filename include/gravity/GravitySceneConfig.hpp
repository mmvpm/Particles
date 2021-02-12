#pragma once

#include <SFML/Graphics.hpp>

#include "particles/Particle.hpp"

struct GravitySceneConfig {
    int screen_width  = 1600;
    int screen_height =  900;

    std::string scene_name = "GravityScene";

    int particles_number = 10000;
    sf::Time frame_delay = sf::milliseconds(10);

    Particle center = {
        {0, 0},
        {0, 0},
        100
    };
    Particle default_particle = {
        {0, -100},
        {27,   0},
        1
    };

    sf::Color center_color   = {255, 255, 255};
    sf::Color particle_color = {255,   0,   0};
};