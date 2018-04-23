#ifndef MESH_H
#define MESH_H

#include <MDGFW\ResourceManager.h>

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	GLuint getVertexBuffer() {
		return _vertexbuffer;
	};
	GLuint getUVBuffer() {
		return _uvbuffer;
	};

	GLuint getNormalsBuffer() {
		return _normalbuffer;
	}

	int getVertices() {
		return _vertices;
	}

	void GenQuadMesh( GLuint _width, GLuint _height, GLuint drawMode);
	void GenCubeMesh( GLuint _width, GLuint _height, GLuint drawMode);

private:
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	GLuint _normalbuffer;
	GLuint _vertexArrayObject;
	int _vertices;
	GLuint _drawArraysMode;
};

#endif // !MESH_H
