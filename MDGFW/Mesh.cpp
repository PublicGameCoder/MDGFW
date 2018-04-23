#include <MDGFW\Mesh.h>

Mesh::Mesh() {
	_vertices = 0;
	_drawArraysMode = GL_TRIANGLES;

	glGenVertexArrays( 1, &_vertexArrayObject );
	glGenBuffers( 1, &_vertexbuffer );
	glGenBuffers( 1, &_uvbuffer );
	glGenBuffers( 1, &_normalbuffer );
}

Mesh::~Mesh() {
	glDeleteBuffers( 1, &_normalbuffer );
	glDeleteBuffers( 1, &_uvbuffer );
	glDeleteBuffers( 1, &_vertexbuffer );
	glDeleteBuffers( 1, &_vertexArrayObject );
}

void Mesh::GenQuadMesh( GLuint _width, GLuint _height, GLuint drawMode ) {
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

	// Two UV coordinates for each vertex.
	GLfloat g_normal_buffer_data[18] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	if ( ((sizeof( g_vertex_buffer_data ) / sizeof( GLfloat )) / 3) != ((sizeof( g_uv_buffer_data ) / sizeof( GLfloat )) / 2) ) {
		std::cout << ":ERROR: The amount of UV's does not match with the amount of vertexes!" << std::endl;
		_vertices = 0;
		return;
	}

	//Defining all vertices
	glBindBuffer( GL_ARRAY_BUFFER, _vertexbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, drawMode );

	//Defining all texture coordinates
	glBindBuffer( GL_ARRAY_BUFFER, _uvbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_uv_buffer_data ), g_uv_buffer_data, drawMode );

	//Defining all normal directions
	glBindBuffer( GL_ARRAY_BUFFER, _normalbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_normal_buffer_data ), g_normal_buffer_data, drawMode );

	_vertices = (sizeof( g_vertex_buffer_data ) / sizeof( GLfloat )) / 3;// 3 => x+y+z = 3 values
	std::cout << "Vertices: " << _vertices << std::endl;

	_drawArraysMode = GL_TRIANGLES;
}

void Mesh::GenCubeMesh( GLuint _width, GLuint _height, GLuint drawMode ) {
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
	GLfloat g_vertex_buffer_data[108] = {
		//Front Quad
		0.5f * _width, -0.5f * _height, 0.5f * _width,// 1
		-0.5f * _width, -0.5f * _height, 0.5f * _width,// 2
		-0.5f * _width,  0.5f * _height, 0.5f * _width,// 3

		-0.5f * _width,  0.5f * _height, 0.5f * _width,// 4
		0.5f * _width,  0.5f * _height, 0.5f * _width,// 5
		0.5f * _width, -0.5f * _height, 0.5f * _width,// 6
		//Right Quad
		0.5f * _width, -0.5f * _height, -0.5f * _width,// 7
		0.5f * _width, -0.5f * _height, 0.5f * _width,// 8
		0.5f * _width,  0.5f * _height, 0.5f * _width,// 9

		0.5f * _width,  0.5f * _height, 0.5f * _width,// 10
		0.5f * _width,  0.5f * _height, -0.5f * _width,// 11
		0.5f * _width, -0.5f * _height, -0.5f * _width,// 12
		//Back Quad
		-0.5f * _width, -0.5f * _height, -0.5f * _width,// 13
		0.5f * _width, -0.5f * _height, -0.5f * _width,// 14
		0.5f * _width,  0.5f * _height, -0.5f * _width,// 15

		0.5f * _width,  0.5f * _height, -0.5f * _width,// 16
		-0.5f * _width,  0.5f * _height, -0.5f * _width,// 17
		-0.5f * _width, -0.5f * _height, -0.5f * _width,// 18
		//Left Quad
		-0.5f * _width, -0.5f * _height, 0.5f * _width,// 19
		-0.5f * _width, -0.5f * _height, -0.5f * _width,// 20
		-0.5f * _width,  0.5f * _height, -0.5f * _width,// 21

		-0.5f * _width,  0.5f * _height, -0.5f * _width,// 22
		-0.5f * _width,  0.5f * _height, 0.5f * _width,// 23
		-0.5f * _width, -0.5f * _height, 0.5f * _width,// 24
		//Top Quad
		0.5f * _width,  0.5f * _height, 0.5f * _width,// 25
		-0.5f * _width,  0.5f * _height, 0.5f * _width,// 26
		-0.5f * _width,  0.5f * _height, -0.5f * _width,// 27

		-0.5f * _width,  0.5f * _height, -0.5f * _width,// 28
		0.5f * _width,  0.5f * _height, -0.5f * _width,// 29
		0.5f * _width,  0.5f * _height, 0.5f * _width,// 30
		//Bottom Quad
		-0.5f * _width, -0.5f * _height, -0.5f * _width,// 31
		0.5f * _width, -0.5f * _height, -0.5f * _width,// 32
		0.5f * _width, -0.5f * _height, 0.5f * _width,// 33

		0.5f * _width, -0.5f * _height, 0.5f * _width,// 34
		-0.5f * _width, -0.5f * _height, 0.5f * _width,// 35
		-0.5f * _width, -0.5f * _height, -0.5f * _width// 36
	};

	// Two UV coordinates for each vertex.
	GLfloat g_uv_buffer_data[72] = {
		//Front Quad
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		//Right Quad
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		//Back Quad
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		//Left Quad
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		//Top Quad
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		//Bottom Quad
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	// Two UV coordinates for each vertex.
	GLfloat g_normal_buffer_data[108] = {
		//Front Quad
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		//Right Quad
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		//Back Quad
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		//Left Quad
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		//Top Quad
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		//Bottom Quad
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};

	if ( ((sizeof( g_vertex_buffer_data ) / sizeof( GLfloat )) / 3) != ((sizeof( g_uv_buffer_data ) / sizeof( GLfloat )) / 2) ) {
		std::cout << ":ERROR: The amount of UV's does not match with the amount of vertexes!" << std::endl;
		_vertices = 0;
		return;
	}

	//Defining all vertices
	glBindBuffer( GL_ARRAY_BUFFER, _vertexbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, drawMode );

	//Defining all texture coordinates
	glBindBuffer( GL_ARRAY_BUFFER, _uvbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_uv_buffer_data ), g_uv_buffer_data, drawMode );

	//Defining all normal directions
	glBindBuffer( GL_ARRAY_BUFFER, _normalbuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( g_normal_buffer_data ), g_normal_buffer_data, drawMode );

	_vertices = (sizeof( g_vertex_buffer_data ) / sizeof( GLfloat )) / 3;// 3 => x+y+z = 3 values
	std::cout << "Vertices: " << _vertices << std::endl;

	_drawArraysMode = GL_TRIANGLES;
}