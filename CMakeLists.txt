cmake_minimum_required(VERSION 3.17)

project("glfw-lab")

# packages
find_package(OpenGL REQUIRED)

# header files
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories("./include")

# libraries
link_directories("./lib")
add_library(stb_image "./deps/stb/src/stb_image.c")
add_library(glad STATIC "./deps/glad/src/glad.c")

set(LIBS
    ${OPENGLE_LIBRARIES}
    glfw3
    glad
    stb_image
)
link_libraries(${LIBS})

add_executable(Glfw001 "./src/glfw001.cpp")
add_executable(Glfw002Shaders "./src/glfw002-shaders.cpp")
add_executable(Glfw003Textures "./src/glfw003-textures.cpp")
add_executable(Glfw004Matrix "./src/glfw004-matrix.cpp")
add_executable(Glfw005Coordinate "./src/glfw005-coordinate.cpp")