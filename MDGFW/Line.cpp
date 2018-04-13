#include <MDGFW\Line.h>

Line::Line() {

	_shader = ResourceManager::getManager()->getShader( DEFAULTMESHSHADERVERTEX, DEFAULTMESHSHADERFRAGMENT );

	_lineWidth = 2.5f;
	_color = RGBAColor(255,255,255,255);
	_pos1 = Vector3( 0, 0, 0 );
	_pos2 = Vector3( 100.0f, 0, 0 );

	_isFromLocal = true;
	_isToLocal = true;

	// Create a VBO
	glGenBuffers( 1, &_vbo );

	// Create a UVBO
	glGenBuffers( 1, &_uvbo );

	//Initialize VBO
	recalculate( Vector3() );
}

void Line::recalculate(Vector3 worldPos) {
	std::vector<Vector3> aps = getAnchors();

	const int dimensions = 3;

	const int s = dimensions * sizeof( aps );

	float line_vertex[s];
	//Construct list with all positions
	line_vertex[0] = _pos1.x + (_isFromLocal)? worldPos.x : 0;
	line_vertex[1] = _pos1.y + (_isFromLocal)? worldPos.y : 0;
	line_vertex[2] = _pos1.z + (_isFromLocal)? worldPos.z : 0;
	int c = dimensions;
	for ( std::vector<Vector3>::iterator it = aps.begin(); it != aps.end(); ++it ) {
		Vector3 anchor = *it;
		line_vertex[c] = anchor.x + worldPos.x;
		line_vertex[c + 1] = anchor.y + worldPos.y;
		line_vertex[c + 2] = anchor.z + worldPos.z;
		c += 3;
	}
	line_vertex[c] = _pos2.x + (_isToLocal)? worldPos.x : 0;
	line_vertex[c + 1] = _pos2.y + (_isToLocal)? worldPos.y : 0;
	line_vertex[c + 2] = _pos2.z + (_isToLocal)? worldPos.z : 0;
	
	float uvs[s];
	for ( unsigned int i = 0; i < s; i+= 2) {
		uvs[i] = 0.5f;
		uvs[i+1] = 0.5f;
	}

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer( GL_ARRAY_BUFFER, _vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( line_vertex ), line_vertex, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, _uvbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( uvs ), uvs, GL_STATIC_DRAW );
}

Line::~Line() {

}