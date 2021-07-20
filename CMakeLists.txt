cmake_minimum_required(VERSION 3.17)

project("LearnOpenGL-Lab")

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

# all executables for legacy
# add_executable(Glfw001 "./src/legacy/glfw001.cpp")
# add_executable(Glfw002Shaders "./src/legacy/glfw002-shaders.cpp")
# add_executable(Glfw003Textures "./src/legacy/glfw003-textures.cpp")
# add_executable(Glfw004Matrix "./src/legacy/glfw004-matrix.cpp")
# add_executable(Glfw005Coordinate "./src/legacy/glfw005-coordinate.cpp")
# add_executable(Glfw006Camera "./src/legacy/glfw006-camera.cpp")

# demo by chapters
set(CHAPTERS
    0.legacy
    1.get_started
    2.lighting
)

set(0.legacy
    1.hello_world
    2.shaders
    3.textures
    4.matrix
    5.coordinate
    6.camera
)
set(1.get_started
    10.review
)
set(2.lighting
    1.colors
    2.1.lighting_ambient
    2.2.lighting_diffuse
    2.3.specular_highlight
    2.4.1.exercise1
)

foreach(CHAPTER ${CHAPTERS})
    foreach(ITEM ${${CHAPTER}})
        file(GLOB SOURCE
            "src/${CHAPTER}/${ITEM}/*.cpp"
            "src/${CHAPTER}/${ITEM}/*.hpp"
            "src/${CHAPTER}/${ITEM}/*.c"
            "src/${CHAPTER}/${ITEM}/*.h"
        )
        set(NAME "${CHAPTER}__${ITEM}")
        add_executable(${NAME} ${SOURCE})
        target_link_libraries(${NAME} ${LIBS})

        # output and debug directories
        if(WIN32)
            set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${NAME}")
            set_target_properties(${NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${NAME}/Debug")
        endif(WIN32)

        # copy shader files to build directory
        file(GLOB SHADERS
            "src/${CHAPTER}/${ITEM}/*.fs"
            "src/${CHAPTER}/${ITEM}/*.vs"
        )
        foreach(SHADER ${SHADERS})
            if(WIN32)
                add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
            endif(WIN32)
        endforeach(SHADER)
                
    endforeach(ITEM ${${CHAPTER}})
endforeach(CHAPTER ${CHAPTERS})