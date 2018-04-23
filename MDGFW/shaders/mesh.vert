#version 130

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition_modelspace;
in vec2 vertexUV;
in vec3 vertexNormals;

// Output data ; will be interpolated for each fragment.
out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	vec4 _fragPos;
	vec4 _vertPos = vec4(vertexPosition_modelspace,1);
	_fragPos = MVP * _vertPos;
	gl_Position = _fragPos;

	// UV of the vertex. No special space for this one.
	UV = vertexUV;
	
	Normal = vertexNormals;
	FragPos = vertexPosition_modelspace;
}
