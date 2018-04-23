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
	${CMAKE_SOURCE_DIR}/ExtLibs/freetype2/include/
	${CMAKE_SOURCE_DIR}/ExtLibs
	
	${CMAKE_SOURCE_DIR}/MDGFW
	${CMAKE_SOURCE_DIR}/.
)

link_directories(
	${CMAKE_SOURCE_DIR}/ExtLibs/glfw-3.2.1/src
	${CMAKE_SOURCE_DIR}/MDGFW
	${CMAKE_SOURCE_DIR}/ExtLibs/freetype2/win32
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	MDGFW
	glfw
	GLEW_190
	${CMAKE_SOURCE_DIR}/ExtLibs/freetype2/win32/freetype.lib
)

add_custom_target(CustomDlls
  # todo: check if debug and release folder exist
  # debug version
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/ExtLibs/freetype2/win32/freetype.dll          ${CMAKE_BINARY_DIR}/Debug
  
  # release version
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/ExtLibs/freetype2/win32/freetype.dll           ${CMAKE_BINARY_DIR}/Release

  # Output Message
  COMMENT "Copying Custom .dll binaries from '${CMAKE_SOURCE_DIR}/ExtLibs/freetype2/win32/freetype.dll' to '${CMAKE_BINARY_DIR}'" VERBATIM
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
	MDGFW/Shader.cpp
	MDGFW/Shader.h
	MDGFW/Scene.cpp
	MDGFW/Scene.h
	MDGFW/SceneManager.cpp
	MDGFW/SceneManager.h
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
	MDGFW/Canvas.cpp
	MDGFW/Canvas.h
	MDGFW/UIElement.cpp
	MDGFW/UIElement.h
	MDGFW/Mesh.cpp
	MDGFW/Mesh.h
	MDGFW/Skybox.cpp
	MDGFW/Skybox.h
	MDGFW/Animation.cpp
	MDGFW/Animation.h
	MDGFW/Animator.cpp
	MDGFW/Animator.h
)
file(
	COPY MDGFW/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

file(
	COPY MDGFW/fonts
	DESTINATION ${CMAKE_BINARY_DIR}
)

file(
	COPY MDGFW/skyboxes
	DESTINATION ${CMAKE_BINARY_DIR}
)

IF(MAKE_WORKSPACE)
	add_executable(Workspace
		Workspace/main.cpp
	)
	
	file(
		COPY Workspace/assets
		DESTINATION ${CMAKE_BINARY_DIR}
	)
	
	file(
		COPY Workspace/fonts
		DESTINATION ${CMAKE_BINARY_DIR}
	)
	
	target_link_libraries(Workspace
		${ALL_GRAPHICS_LIBS}
	)
	
	add_dependencies(Workspace CustomDlls)
ENDIF()

