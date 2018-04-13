#include <MDGFW\Mesh.h>

Mesh::Mesh() {
	_vertices = 0;
	_drawArraysMode = GL_TRIANGLES;
}

Mesh::~Mesh() {
	glDeleteBuffers( 1, &_vertexbuffer );
	glDeleteBuffers( 1, &_uvbuffer );
}

void Mesh::GenQuadMesh(GLuint _width, GLuint _height, GLuint drawMode ) {
	glGenBuffers( 1, &_vertexbuffer );
	glGenBuffers( 1, &_uvbuffer );
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
	GLfloat g_vertex_buffer_data[18] = {
		0.5f * _width, -0.5f * _height, 0.0f,
		-0.5f * _width, -0.5f * _height, 0.0f,
		-0.5f * _width,  0.5f * _height, 0.0f,

		-0.5f * _width,  0.5f * _height, 0.0f,
		0.5f * _width,  0.5f * _height, 0.0f,
		0.5f * _width, -0.5f * _height, 0.0f
	};

	// Two UV coordinates for each vertex.
	GLfloat g_uv_buffer_data[12] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	if ( (sizeof( g_vertex_buffer_data ) / 3) != (sizeof( g_uv_buffer_data ) / 2) ) {
		std::cout << ":ERROR: The amount of UV's does not match with the amount of vertexes!" << std::endl;
		_vertices = 0;
		return;
	}

	glBindBuffer( GL_ARRAY_BUFFER, _vertexbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, drawMode );

	glBindBuffer( GL_ARRAY_BUFFER, _uvbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_uv_buffer_data ), g_uv_buffer_data, drawMode );

	_vertices = sizeof( g_vertex_buffer_data ) / 3;// 3 => x+y+z = 3 values
	std::cout << "Vertices: " << _vertices << std::endl;

	_drawArraysMode = GL_TRIANGLES;
}

void Mesh::genTextMesh() {
	glGenVertexArrays( 1, &_vertexbuffer );
	glGenBuffers( 1, &_uvbuffer );
	glBindVertexArray( _vertexbuffer );
	glBindBuffer( GL_ARRAY_BUFFER, _uvbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * 6 * 4, NULL, GL_DYNAMIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );
}