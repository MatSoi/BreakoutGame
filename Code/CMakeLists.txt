cmake_minimum_required(VERSION 2.6)

project(main)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -std=c++11")


FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
LINK_DIRECTORIES(${GLEW_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

file(
	GLOB
	source_files
	src/*.[ch]pp
        src/*.h
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

QT4_WRAP_UI(pgm_UI_H src/mainwindow.ui)
QT4_WRAP_CPP(source_files_moc src/window.hpp src/render_area.hpp)

add_executable(
	pgm
	${source_files}
	${pgm_UI_H}
	${source_files_moc}
)


TARGET_LINK_LIBRARIES(pgm -lm ${QT_LIBRARIES})


