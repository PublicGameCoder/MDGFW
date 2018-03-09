# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (MDGFW)

OPTION(MAKE_WORKSPACE "Make MDGFW game application" ON)

find_package(OpenGL REQUIRED)

add_subdirectory (ExtLibs)

include_directories(
	${CMAKE_SOURCE_DIR}/ExtLibs/glfw-3.2.1/include/GLFW
	${CMAKE_SOURCE_DIR}/ExtLibs/glm-0.9.8.4
	${CMAKE_SOURCE_DIR}/ExtLibs
	
	${CMAKE_SOURCE_DIR}/MDGFW
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/ExtLibs/glfw-3.2.1/src
	${CMAKE_SOURCE_DIR}/MDGFW
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	MDGFW
	glfw
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

####################################################################
# libMDGFW.a                                                        #
####################################################################

add_library(MDGFW
)

IF(MAKE_WORKSPACE)
	add_executable(Workspace
		Workspace/main.cpp
	)
	target_link_libraries(Workspace
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

