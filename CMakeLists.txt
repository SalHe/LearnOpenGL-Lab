cmake_minimum_required(VERSION 3.17)

project("glfw-lab")

set(glfw3_DIR "./deps/glfw/lib/cmake/glfw3")
find_package(glfw3)
find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories("./deps/")
include_directories("./deps/glfw/include")
include_directories("./deps/glad/include")

add_library(glad STATIC "./deps/glad/src/glad.c"
                        "./deps/glad/include/glad/glad.h"
                        "./deps/glad/include/KHR/khrplatform.h")

link_directories("./deps/glfw/lib")
link_libraries(glfw3 ${OPENGL_LIBRARIES} glad)

add_executable(Glfw001 "./src/glfw001.cpp")
add_executable(Glfw002Shaders "./src/glfw002-shaders.cpp")
add_executable(Glfw003Textures "./src/glfw003-textures.cpp")