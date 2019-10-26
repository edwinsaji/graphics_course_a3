#ifndef _ONAS_STATE_
#define _ONAS_STATE_
#include "ONAS_state.hpp"
#endif

#ifndef _MVP_MATRICES_
#define _MVP_MATRICES_
#include "matrices.hpp"
#endif

#include "gl_framework.hpp"

//implementation of space as a skybox

class space
{

public:

	std::vector< glm::vec4 > mesh;
	std::vector< glm::vec2 > texture_coord;

	std::vector< GLuint > vao, vbo; 

	GLuint shader;

	float side;


	void create_mesh(void);
	
	void get_shaders(std::string vertex_shader, std::string fragment_shader);

	void init_buffers(void);

	void set_constant_uniforms(ONAS_state state);

	void set_non_constant_uniforms(MVPmatrices set);

	void draw(GLuint texture_enum);

	space(float side)
	{
		this->side = side;
	}
};