#ifndef _SHADER_UTIL_HPP_
#define _SHADER_UTIL_HPP_

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdexcept>


namespace csX75
{
  GLuint LoadShaderGL(GLenum eShaderType, const std::string &strFilename);
  GLuint CreateShaderGL(GLenum eShaderType, const std::string &strShaderFile);
  GLuint CreateProgramGL(const std::vector<GLuint> &shaderList);
};

#endif


#ifndef _FSTREAM_
#define _FSTREAM_
#include <fstream>
#include <sstream>
#include <string>

#endif