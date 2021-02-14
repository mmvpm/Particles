#include "gravity/GravityScene.hpp"
#include "gravity/GravitySceneLines.hpp"
#include "gravity/GravitySceneNeonLines.hpp"
#include "gravity/GravitySceneConfig.hpp"

int main() {
    auto config = GravitySceneConfig();
    config.screen_width = 1600;
    config.screen_height = 900;
    config.particles_number = 50000;


    GravityScene scene(config);
//    GravitySceneLines scene(config);
//    GravitySceneNeonLines scene(config);

    scene.run();

    return 0;
}
