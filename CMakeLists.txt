cmake_minimum_required(VERSION 2.6)
project(sdl_shim)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O1")

find_package(OpenGL)
find_package(GLEW)
find_package(Freetype)

set(ALL_OPENGL_INCLUDES ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
set(ALL_OPENGL_LIBRARIES ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_subdirectory(src)

file(COPY fonts DESTINATION .)
install(DIRECTORY fonts DESTINATION libshimmer)
