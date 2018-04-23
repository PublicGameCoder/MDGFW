#include "MDGFW\Texture.h"
#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture() {
	glGenTextures( 1, &_textureID );
}

Texture::~Texture() {
	glDeleteTextures( 1, &_textureID );
}

void Texture::load2DTexture( const std::string &filePath ) {
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
	unsigned char *data = stbi_load( filePath.c_str(), &_width, &_height, &_nrChannels, 0 );
	if ( data )
	{
		GLuint format1 = GL_RGB;
		GLuint format2 = GL_RGB;

		switch ( _nrChannels ) {
		case 1:
			format1 = GL_LUMINANCE;
			format2 = GL_LUMINANCE;
			break;
		case 2:
			format1 = GL_RED;
			format2 = GL_RGBA;
			break;
		case 3:
			format1 = GL_RGB;
			format2 = GL_RGB;
			break;
		case 4:
			format1 = GL_RGBA;
			format2 = GL_RGBA;
			break;
		default:
			format1 = GL_RGB;
			format2 = GL_RGB;
			break;
		}

		glTexImage2D( GL_TEXTURE_2D, 0, format1, _width, _height, 0, format2, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free( data );
}

void Texture::loadSkybox(  std::vector<std::string> &faces ) {
	glBindTexture( GL_TEXTURE_CUBE_MAP, _textureID );
	for ( unsigned int i = 0; i < faces.size(); i++ )
	{
		unsigned char *data = stbi_load( faces[i].c_str(), &_width, &_height, &_nrChannels, 0 );
		if ( data )
		{
			GLuint format1 = GL_RGB;
			GLuint format2 = GL_RGB;

			switch ( _nrChannels ) {
			case 1:
				format1 = GL_LUMINANCE;
				format2 = GL_LUMINANCE;
				break;
			case 2:
				format1 = GL_RED;
				format2 = GL_RGBA;
				break;
			case 3:
				format1 = GL_RGB;
				format2 = GL_RGB;
				break;
			case 4:
				format1 = GL_RGBA;
				format2 = GL_RGBA;
				break;
			default:
				format1 = GL_RGB;
				format2 = GL_RGB;
				break;
			}
			glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format1, _width, _height, 0, format2, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free( data );
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free( data );
		}
	}
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
}