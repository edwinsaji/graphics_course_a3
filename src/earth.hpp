
#ifndef _ONAS_STATE_
#define _ONAS_STATE_
#include "ONAS_state.hpp"
#endif

#ifndef _MVP_MATRICES_
#define _MVP_MATRICES_
#include "matrices.hpp"
#endif


#include "gl_framework.hpp"

//to draw ground
class earth
{

public:

	std::vector< glm::vec4 > mesh;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec2 > texture_coord;


	float radius;

	std::vector<GLuint> vao, vbo;

	//Gluint surface_texture;

	GLuint shader;

	void create_mesh(int no_of_longs, int no_of_lats);

	void get_shaders(std::string vertex_shader, std::string fragment_shader);
	
	void init_buffers(void);
	
	void set_constant_uniforms(ONAS_state state);

	void set_non_constant_uniforms(MVPmatrices set);

	void draw(GLuint texture_enum);

	earth(float radius)
	{
		this->radius = radius;
	}

};