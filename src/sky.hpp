#ifndef _ONAS_STATE_
#define _ONAS_STATE_
#include "ONAS_state.hpp"
#endif

#ifndef _MVP_MATRICES_
#define _MVP_MATRICES_
#include "matrices.hpp"
#endif

#include "gl_framework.hpp"

//to draw sky

class sky
{

public:
	
	std::vector< glm::vec4 > mesh;

	std::vector< GLuint > vao, vbo; 

	std::vector< GLuint > texture_ids;//texture_enums are the corresponding indices;

	float radius;

	GLuint shader;


	void create_mesh(int no_of_longs, int no_of_lats);
	
	void get_shaders(std::string vertex_shader, std::string fragment_shader);

	void init_buffers(void);
	
	void set_constant_uniforms(ONAS_state state);

	void set_non_constant_uniforms(MVPmatrices set);

	void draw(void);

	sky(float radius)
	{
		this->radius = radius;
	}



};