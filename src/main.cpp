#include "gravity/GravityScene.hpp"
#include "gravity/GravitySceneLines.hpp"
#include "gravity/GravitySceneNeonLines.hpp"
#include "gravity/GravitySceneConfig.hpp"

int main() {
    auto config = GravitySceneConfig();
    config.particles_number = 30000;

//    auto scene = GravityScene(config);
    auto scene = GravitySceneLines(config);
//    auto scene = GravitySceneNeonLines(config);

    scene.run();

    return 0;
}
