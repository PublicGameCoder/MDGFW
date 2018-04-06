#include <MDGFW/sprite.h>

Sprite::Sprite(std::string image_path)
{

	// Load image as texture
	_texture = ResourceManager::getManager()->getTexture(image_path);
	_shader = ResourceManager::getManager()->getShader( DEFAULTSPRITESHADERVERTEX, DEFAULTSPRITESHADERFRAGMENT );

	_width = _texture->getWidth();
	_height = _texture->getHeight();

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

	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

Sprite::~Sprite()
{
	glDeleteBuffers(1, &_vertexbuffer);
	glDeleteBuffers(1, &_uvbuffer);
}
