#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_
namespace csX75
{
GLuint LoadTexture( const char * filename, int width, int height , GLuint texture_enum);
void FreeTexture( GLuint texture );
};
#endif 
