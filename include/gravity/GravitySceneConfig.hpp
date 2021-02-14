#pragma once

#include <SFML/Graphics.hpp>

#include "particles/Particle.hpp"

struct GravitySceneConfig {
    // general
    int screen_width = 1600;
    int screen_height = 900;
    int particles_number = 10000;
    std::string scene_name = "GravityScene";
    sf::Time frame_delay = sf::milliseconds(10);

    // gravity
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
    sf::Color center_color = sf::Color::White;
    std::vector<sf::Color> particle_colors = {
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color::Green,
        sf::Color::Yellow
    };
};