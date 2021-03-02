cmake_minimum_required(VERSION 3.15)
project(Particles)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(Particles
    include/interfaces/IModel.hpp
    include/interfaces/IScene.hpp

    include/particles/Point.hpp
    include/particles/Particle.hpp
    include/particles/ParticlesVector.hpp

    include/gravity/GravityModel.hpp
    include/gravity/GravityScene.hpp
    include/gravity/GravitySceneLines.hpp
    include/gravity/GravitySceneNeonLines.hpp
    include/gravity/GravitySceneConfig.hpp

    include/extensions/SeekBar.hpp
    include/extensions/Gradient.hpp

    src/particles/Point.cpp
    src/particles/ParticlesVector.cpp

    src/gravity/GravityModel.cpp
    src/gravity/GravityScene.cpp
    src/gravity/GravitySceneLines.cpp
    src/gravity/GravitySceneNeonLines.cpp

    src/extensions/SeekBar.cpp
    src/extensions/Gradient.cpp

    src/main.cpp
)

target_link_libraries(Particles sfml-graphics)