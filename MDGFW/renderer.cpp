#include <MDGFW/renderer.h>

Renderer::Renderer()
{
	_window_width = MINSWIDTH;
	_window_height = MINSHEIGHT;

	this->init();
}

Renderer::~Renderer()
{
	// Cleanup VBO and shader
	glDeleteProgram(_programID);
}

int Renderer::init()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, false);//Can the user resize the window or not?

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( _window_width, _window_height, TITLE, NULL, NULL);
	if( _window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	useVSYNC( VSYNC );

	GLFWmonitor* primary = glfwGetPrimaryMonitor();

	//Use when user is able to resize (this restricts the user's window size between 2 values on the x and y (WINDOW,MINX,MINY,MAXX,MAXY))
	//glfwSetWindowSizeLimits( _window, MINSWIDTH, MINSHEIGHT, MINSWIDTH, MINSHEIGHT );

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	_programID = this->loadShaders("shaders/sprite.vert", "shaders/sprite.frag");

	_projectionMatrix = glm::ortho(0.0f, (float)_window_width, (float)_window_height, 0.0f, 0.1f, 100.0f);

	// Use our shader
	glUseProgram(_programID);

	_camera = new Camera();

	return 0;
}

void Renderer::updateWorld( World* world ) {
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Compute the ViewMatrix from keyboard and mouse input (see: camera.h/cpp)
	_camera->updateCamera(_window);
	//glm::vec3 cursor = getCursor(); // from Camera
	//printf("(%f,%f)\n",cursor.x, cursor.y);

	updateEntity( world );

	// Swap buffers
	glfwSwapBuffers( _window );
}

void Renderer::updateEntity( Entity* entity ) {

	entity->update();

	Sprite* sprite = entity->getSprite();
	if ( sprite != nullptr ) {
		renderSprite( sprite, entity->position, entity->scale, entity->rotation );
	}
	
	renderLines( entity );

	for each (Entity* child in entity->getChilds()) {
		updateEntity( child );
	}
}

void Renderer::renderLines( Entity* entity ) {

	float lineWidth;
	RGBAColor color;
	Vector3 from;
	Vector3 to;
	Vector3 fromGlobal;
	Vector3 toGlobal;

	for each (Line* line in entity->getLines()) {

		lineWidth = line->getWidth();
		color = line->getColor();

		glLineWidth( lineWidth );

		glColor3f( color.r, color.g, color.b );

		//Model position
		from = line->getFrom();
		to = line->getTo();

		if ( line->hasAnchors() ) {
			std::vector<Vector3> aps = line->getAnchors();
			std::vector<Vector3> anchors;
			anchors.push_back( toWorldSpace(entity, from, line->isFromLocal()) );
			for ( std::vector<Vector3>::iterator it = aps.begin(); it != aps.end(); ++it ) {
				anchors.push_back( toWorldSpace(entity, *it, true) );
			}
			anchors.push_back( toWorldSpace( entity, to, line->isToLocal() ) );
			int s = anchors.size();
			glBegin( GL_LINE_STRIP );
			Vector3 pos1 = anchors[0];
			glVertex3f( pos1.x, pos1.y, pos1.z );
			float stepSize = 1.0f / line->getPrecision();
			for ( float p = stepSize; p < 1.0f; p += stepSize ) {
				Vector3 pos2;
				if ( s == 3 ) {
					pos2 = Math::quadraticCurve( anchors[0], anchors[1], anchors[2], p );
				}
				else if ( s == 4 ) {
					pos2 = Math::cubeCurve( anchors[0], anchors[1], anchors[2], anchors[3], p );
				}
				else if ( s == 5 ) {
					pos2 = Math::quarticCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], p );
				}
				else if ( s == 6 ) {
					pos2 = Math::quinticCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], p );
				}
				else if ( s == 7 ) {
					pos2 = Math::sexticCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], anchors[6], p );
				}
				else if ( s == 8 ) {
					pos2 = Math::septicCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], anchors[6], anchors[7], p );
				}
				else if ( s == 9 ) {
					pos2 = Math::octic( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], anchors[6], anchors[7], anchors[8], p );
				}
				else if ( s == 10 ) {
					pos2 = Math::nonicCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], anchors[6], anchors[7], anchors[8], anchors[9], p );
				}
				else if ( s == 11 ) {
					pos2 = Math::decicCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], anchors[6], anchors[7], anchors[8], anchors[9], anchors[10], p );
				}
				else {
					pos2 = Math::decicCurve( anchors[0], anchors[1], anchors[2], anchors[3], anchors[4], anchors[5], anchors[6], anchors[7], anchors[8], anchors[9], anchors[10], p );
				}
				glVertex3f( pos2.x , pos2.y, pos2.z );
			}

			glEnd();
		}
		else {
			//World position
			fromGlobal = from;//toWorldSpace( entity, from, line->isFromLocal() );
			toGlobal = to;//toWorldSpace( entity, to, line->isToLocal() );

			glBegin( GL_LINES );

			glVertex3f( fromGlobal.x, fromGlobal.y, fromGlobal.z );
			glVertex3f( toGlobal.x, toGlobal.y, toGlobal.z );

			glEnd();
		}
	}
}

Vector3& Renderer::toWorldSpace(Entity* owner,Vector3 pos, bool isLocal ) {
	if ( isLocal ) {
		pos += owner->getWorldPosition();
	}
	return pos;
}

void Renderer::renderSprite( Sprite* sprite, Vector3 pos, Vector3 scl, Vector3 rot ) {
	renderSprite( sprite, pos.x, pos.y, scl.x, scl.y, rot.z );
}

void Renderer::renderSprite(Sprite* sprite, float px, float py, float sx, float sy, float rot)
{
	glm::mat4 viewMatrix  = _camera->getViewMatrix(); // get from Camera (Camera position and direction)
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// Build the Model matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(px, py, 0.0f));
	glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(0.0f, 0.0f, rot);
	glm::mat4 scalingMatrix	 = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, 1.0f));

	modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	glm::mat4 MVP = _projectionMatrix * viewMatrix * modelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	GLuint matrixID = glGetUniformLocation(_programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture()->getID());
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	GLuint textureID  = glGetUniformLocation(_programID, "myTextureSampler");
	glUniform1i(textureID, 0);

	// 1st attribute buffer : vertices
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(_programID, "vertexPosition_modelspace");
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexbuffer());
	glVertexAttribPointer(
		vertexPosition_modelspaceID,  // The attribute we want to configure
		3,							// size : x+y+z => 3
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
	);

	// 2nd attribute buffer : UVs
	GLuint vertexUVID = glGetAttribLocation(_programID, "vertexUV");
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,				   // The attribute we want to configure
		2,							// size : U+V => 2
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
}

GLuint Renderer::loadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
	if (vertexShaderStream.is_open()){
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	} else {
		printf("Can't to open %s.\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		std::vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
