cmake_minimum_required(VERSION 3.21)
project(FractalRk LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.5)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG master)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(FractalRk 
src/main.cpp
src/julia.cpp
src/fractal.cpp
src/mandel.cpp
src/tricorn.cpp
src/burning.cpp
)
target_link_libraries(FractalRk PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
target_compile_features(FractalRk PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET FractalRk POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:FractalRk> $<TARGET_FILE_DIR:FractalRk> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS FractalRk)
