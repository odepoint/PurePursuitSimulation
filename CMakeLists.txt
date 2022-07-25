cmake_minimum_required(VERSION 3.22)
project(PurePursuitSimulation)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(PurePursuitSimulation
        include/lookAhead.h
        include/mathLib.h
        include/pathUpdate.h
        include/point.h
        include/pointCreation.h
        include/rateLimiter.h
        include/robot.h
        include/simulation.h
        src/main.cpp
        src/mathLib.cpp
        src/pathUpdate.cpp
        src/pointCreation.cpp
        src/simulation.cpp)
