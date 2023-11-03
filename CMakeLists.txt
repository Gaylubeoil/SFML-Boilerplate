cmake_minimum_required(VERSION 3.5.0)
project(AnimationsTester VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Find SFML shared libraries
find_package(SFML 2.5
  COMPONENTS
  system window graphics network audio REQUIRED
)

set (SOURCE_DIR
    src/main.cpp
    src/Application.cpp
    src/Entity.cpp
    src/Player.cpp
    src/SceneNode.cpp
    src/Utility.cpp
    src/CommandQueue.cpp
    src/StateStack.cpp
    src/State.cpp
    src/GameState.cpp
    src/World.cpp
)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} ${SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE Include/)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)