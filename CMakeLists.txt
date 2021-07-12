cmake_minimum_required(VERSION 3.17)

project("glfw-lab")

# 查找GLFW3
# 可以通过源码，也可以使用编译好的二进制文件
# 这里选择后面种方法
set(glfw3_DIR "./glfw/lib/cmake/glfw3")
find_package(glfw3)
find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories("./glfw/include")
include_directories("./glad/include")

add_library(glad STATIC "./glad/src/glad.c"
                        "./glad/include/glad/glad.h"
                        "./glad/include/KHR/khrplatform.h")

link_directories("./glfw/lib")
link_libraries(glfw3 ${OPENGL_LIBRARIES} glad)

add_executable(Glfw001 glfw001.cpp)