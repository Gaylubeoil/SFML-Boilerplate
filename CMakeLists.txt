cmake_minimum_required(VERSION 3.22.1)
project(AnimationsTester VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.5.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

# FindSFML shared libraries

# find_package(SFML 2.5
# COMPONENTS
# system window graphics network audio REQUIRED
# )
set(SOURCE_DIR
  src/main.cpp
  src/Application.cpp
  src/Entity.cpp
  src/Player.cpp
  src/SceneNode.cpp
  src/SpriteNode.cpp
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

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)

# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
  OUTPUT_NAME RPG
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

if(WIN32)
  add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
