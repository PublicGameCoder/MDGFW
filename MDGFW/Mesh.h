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
	int getVertices() {
		return _vertices;
	}

	void GenQuadMesh( GLuint _width, GLuint _height, GLuint drawMode);
	void genTextMesh();

private:
	GLuint _vertexbuffer;
	GLuint _uvbuffer;
	int _vertices;
	GLuint _drawArraysMode;
};

#endif // !MESH_H
