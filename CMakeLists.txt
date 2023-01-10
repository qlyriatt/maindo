cmake_minimum_required(VERSION 3.0.0)
project(maindo VERSION 0.1.0)


find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
if(!${SMFL_FOUND})
    message(FATAL_ERROR "SFML not found")
endif()

add_executable(maindo   main.cpp
                        BasicObject.cpp
                        MovingObject.cpp
                        Misc.cpp
                        Player.cpp
                        Utilities.cpp
                        Render.cpp
)

target_include_directories(maindo PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(maindo sfml-graphics)


