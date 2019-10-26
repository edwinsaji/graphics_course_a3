#ifndef _MAT4X4_
#define _MAT4X4_
#include "glm/mat4x4.hpp"
#endif

#ifndef _VEC3_
#define _VEC3_
#include "glm/vec3.hpp"
#endif

class MVPmatrices
{

public:
	
	glm::mat4 Model, View, Projection;

	glm::vec3 CameraPosition;
};