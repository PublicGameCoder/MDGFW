#include "MDGFW\Text.h"

Text::Text() {
	_message = "No text assigned!";
	_shader = nullptr;
	_color = WHITE;
	_position = Vector2();
	_scale = 1.0f;
	init();
}

Text::Text(std::string txt) {
	_message = txt;
	_shader = nullptr;
	_color = WHITE;
	_position = Vector2();
	_scale = 1.0f;
	init();
}

Text::~Text() {

}

int Text::init() {
	_fontChars = ResourceManager::getManager()->getFontChars( DEFAULTFONT );
	setupShader();
	generateQuad();
	return 0;
}

void Text::setupShader() {
	_shader = ResourceManager::getManager()->getShader( DEFAULTTEXTSHADERVERTEX, DEFAULTTEXTSHADERFRAGMENT );
	glm::mat4 projection = glm::ortho( 0.0f, static_cast<GLfloat>(MINSWIDTH), 0.0f, static_cast<GLfloat>(MINSHEIGHT) );
	_shader->use();
	glUniformMatrix4fv( glGetUniformLocation( _shader->getID(), "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
}

void Text::generateQuad() {
	// Configure VAO/VBO for texture quads
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glBindVertexArray( VAO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * 6 * 4, NULL, GL_DYNAMIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );
}

void Text::setFont( std::string path ) {
	_fontChars = ResourceManager::getManager()->getFontChars( path );
}

void Text::setColor( RGBAColor color ) {
	_color = color;
}