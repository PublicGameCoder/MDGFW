#include "MDGFW\Text.h"

Text::Text() {
	_message = "";
	_shader = nullptr;
	_color = WHITE;
	_position = Vector2();
	_scale = 1.0f;
	init();
}

Text::Text(std::string txt) {
	_message = txt;
	_color = WHITE;
	_position = Vector2();
	_scale = 1.0f;
	init();
}

Text::~Text() {

}

int Text::init() {
	_shader = ResourceManager::getManager()->getShader( DEFAULTTEXTSHADERVERTEX, DEFAULTTEXTSHADERFRAGMENT );
	return 0;
}

void Text::setColor( RGBAColor color ) {
	_color = color;
}