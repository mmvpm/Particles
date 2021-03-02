#include "gravity/GravityScene.hpp"
#include "gravity/GravitySceneLines.hpp"
#include "gravity/GravitySceneNeonLines.hpp"
#include "gravity/GravitySceneConfig.hpp"

int main() {
    auto config = GravitySceneConfig();
    config.particles_number = 50000;
    config.particle_colors = {
        sf::Color(255,  49,  50), // red
        sf::Color( 27,  46, 254), // blue
        sf::Color( 65, 250,  52), // green
        sf::Color(249, 254,  46), // yellow
        sf::Color(219, 253, 255), // white
    };

    GravitySceneLines scene(config);
    scene.run();

    return 0;
}
