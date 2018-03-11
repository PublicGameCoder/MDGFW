#include <MDGFW\Line.h>

Line::Line() {
	_lineWidth = 2.5f;
	_color = RGBAColor(255,255,255,255);
	_pos1 = Vector3( 0, 0, 0 );
	_pos2 = Vector3( 100.0f, 0, 0 );
}

Line::~Line() {

}