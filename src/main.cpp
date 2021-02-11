#include "gravity/GravityModel.hpp"
#include "gravity/GravitySceneNeonLines.hpp"

using namespace std;

int main() {
    Particle center = {
        {0, 0},
        {0, 0},
        100};
    Particle defaultParticle = {
        {0, -100},
        {27, 0},
        1
    };

    GravityModel model(center, 20000, defaultParticle);
//    GravityScene scene(1600, 900, model);
    GravitySceneLines scene(1600, 900, model);
//    GravitySceneNeonLines scene(1600, 900, model);
    scene.run();
}