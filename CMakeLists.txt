cmake_minimum_required(VERSION 3.0.0)
project(maindo VERSION 0.1.0)

# ???
include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
if(!${SMFL_FOUND})
    message(FATAL_ERROR "SFML not found")
endif()

add_executable(maindo   main.cpp 
                        Entity.cpp
                        gameObject.cpp 
                        gameObjectStationary.cpp
                        Map.cpp
                        Misc.cpp
                        Player.cpp
                        Weapon.cpp
)

target_include_directories(maindo PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(maindo sfml-graphics)


