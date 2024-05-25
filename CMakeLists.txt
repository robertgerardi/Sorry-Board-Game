cmake_minimum_required(VERSION 3.23)
project(309_Final_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(309_Final_Project
        GameObjects.h
        GameObjects.cpp

        Shuffle.cpp
        Shuffle.h

        setupGame.cpp
        setupGame.h

        main.cpp

        )
