cmake_minimum_required(VERSION 3.15)
project(Particles)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

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
        src/particles/Point.cpp
        src/particles/ParticlesVector.cpp
        src/gravity/GravityModel.cpp
        src/gravity/GravityScene.cpp
        src/gravity/GravitySceneLines.cpp
        src/gravity/GravitySceneNeonLines.cpp
        src/main.cpp)

set(SFML_ROOT C:/cpp_sfml_test/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()