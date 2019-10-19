#ifndef _VEC2_
#define _VEC2_
#include "glm/vec2.hpp"
#endif

#ifndef _VEC3_
#define _VEC3_
#include "glm/vec3.hpp"
#endif

#include "gl_framework.hpp"



class earth
{

public:
	//we shall make it with 
	std::vector< glm::vec4 > vertices;
	std::vector< glm::vec3 > normal;
	std::vector< glm::vec2 > texture;
	std::vector< unsigned int > indices;

	float radius;

	unsigned int no_of_longs ,  no_of_lats;

	GLuint vbo , vao , index , texture_id;

	GLuint shaderProgram;


	void create_vertices (float radius);
	void init_buffers (GLuint _shaderProgram);
	void draw (void);

	earth()
	{
		no_of_lats = no_of_longs = 2000 ;
	}

};