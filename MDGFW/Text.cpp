#include "MDGFW\Text.h"

Text::Text() : UIElement() {
	_message = "No text assigned!";
	_shader = nullptr;
	_color = WHITE;
	this->setPosition( 0, 0 );
	_scale = 1.0f;
	init();
}

Text::Text(std::string txt) : UIElement() {
	_message = txt;
	_shader = nullptr;
	_color = WHITE;
	this->setPosition( 0, 0 );
	_scale = 1.0f;
	init();
}

Text::~Text() {

}

int Text::init() {
	_fontChars = ResourceManager::getManager()->getFontChars( DEFAULTFONT );
	setupShader();

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

	return 0;
}

void Text::setupShader() {
	_shader = ResourceManager::getManager()->getShader( DEFAULTTEXTSHADERVERTEX, DEFAULTTEXTSHADERFRAGMENT );
	glm::mat4 projection = glm::ortho( 0.0f, ( float ) MINSWIDTH, ( float ) MINSHEIGHT, 0.0f, 0.0f, 100.0f );
	_shader->use();
	glUniformMatrix4fv( glGetUniformLocation( _shader->getID(), "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
}

void Text::setFont( std::string path ) {
	_fontChars = ResourceManager::getManager()->getFontChars( path );
}

void Text::setColor( RGBAColor color ) {
	_color = color;
}