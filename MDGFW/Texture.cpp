#include "MDGFW\Texture.h"
#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "other/stb_image.h"

Texture::Texture( const std::string &filePath ) {
	getIDFromData( filePath );
}

Texture::~Texture() {
	glDeleteTextures( 1, &_textureID );
}

void Texture::getIDFromData( const std::string &filePath ) {
	glGenTextures( 1, &_textureID );
	glBindTexture( GL_TEXTURE_2D, _textureID );
	// set the texture wrapping parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	// set texture filtering parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load( true ); // tell stb_image.h to flip loaded texture's on the y-axis.
											  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	std::cout << "Loading: " << filePath.c_str() << std::endl;
	unsigned char *data = stbi_load( filePath.c_str(), &_width, &_height, &_nrChannels, 0 );
	if ( data )
	{
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free( data );
}