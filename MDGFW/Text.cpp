#include "MDGFW\Text.h"

Text::Text() {
	_message = "";
	_size = 24.0f;
	_fontPath = DEFAULTFONT;
	_shader = nullptr;
	_font = nullptr;
	_color = WHITE;
	_position = Vector2();
	_scale = Vector2(1.0f,1.0f);
	init();
}

Text::Text(std::string txt) {
	_message = txt;
	_size = 24.0f;
	_fontPath = DEFAULTFONT;
	_font = nullptr;
	_color = WHITE;
	_position = Vector2();
	_scale = Vector2(1.0f,1.0f);
	init();
}

Text::~Text() {

}

int Text::init() {
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
	_font = ResourceManager::getManager()->getFont( _fontPath );
	_shader = ResourceManager::getManager()->getShader( DEFAULTTEXTSHADERVERTEX, DEFAULTTEXTSHADERFRAGMENT );
	FT_Set_Pixel_Sizes( *_font, 0, _size );

	return 0;
}

void Text::setFontSize( float size ) {
	_size = size;
	FT_Set_Pixel_Sizes( *_font, 0, _size );
}
void Text::setFont( std::string path ) {
	_fontPath = path;
	_font = ResourceManager::getManager()->getFont( _fontPath );
}

void Text::setColor( RGBAColor color ) {
	_color = color;
}