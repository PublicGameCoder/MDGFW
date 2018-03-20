# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (MDGFW)

OPTION(MAKE_WORKSPACE "Make MDGFW game application" ON)

find_package(OpenGL REQUIRED)

add_subdirectory (ExtLibs)

include_directories(
	${CMAKE_SOURCE_DIR}/ExtLibs/glfw-3.2.1/include/GLFW
	${CMAKE_SOURCE_DIR}/ExtLibs/glm-0.9.8.4
	${CMAKE_SOURCE_DIR}/ExtLibs/glew-1.9.0/include/
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
	GLEW_190
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
	MDGFW/camera.h
	MDGFW/camera.cpp
	MDGFW/renderer.h
	MDGFW/renderer.cpp
	MDGFW/sprite.h
	MDGFW/sprite.cpp
	MDGFW/Engine.cpp
	MDGFW/Engine.h
	MDGFW/MDGFWConfig.h
	MDGFW/World.cpp
	MDGFW/World.h
	MDGFW/InputManager.cpp
	MDGFW/InputManager.h
	MDGFW/MDGTime.cpp
	MDGFW/MDGTime.h
	MDGFW/Entity.cpp
	MDGFW/Entity.h
	MDGFW/VectorX.h
	MDGFW/PointX.h
	MDGFW/Line.cpp
	MDGFW/Line.h
	MDGFW/color.h
	MDGFW/Mathmatics.h
	MDGFW/ResourceManager.cpp
	MDGFW/ResourceManager.h
	MDGFW/Texture.cpp
	MDGFW/Texture.h
	MDGFW/Text.cpp
	MDGFW/Text.h
	
)
file(
	COPY MDGFW/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

IF(MAKE_WORKSPACE)
	add_executable(Workspace
		Workspace/main.cpp
		Workspace/RGBAObj.h
		Workspace/StickFigure.cpp
		Workspace/StickFigure.h
	)
	
	file(
		COPY Workspace/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
	
	target_link_libraries(Workspace
		${ALL_GRAPHICS_LIBS}
	)
ENDIF()

