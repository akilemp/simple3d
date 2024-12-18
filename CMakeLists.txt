cmake_minimum_required(VERSION 3.5.0)

project(threedee VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(Simple3DRendererSDL render_sdl.cpp)

add_executable(Simple3DRenderer render.cpp)
target_link_libraries(Simple3DRenderer ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES} )

target_link_libraries(Simple3DRendererSDL ${SDL2_LIBRARIES} )

