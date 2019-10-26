#include "space.hpp"
#include "shader_util.hpp"




//==================================================================================
namespace
{

void quad(int a, int b, int c, int d, int &tri_idx,glm::vec4 positions[], space * space_instance)
{
	(space_instance->texture_coord) [tri_idx] = glm::vec2(0.0f,0.0f); 
	(space_instance->mesh) [tri_idx] = positions[a];tri_idx++;

	(space_instance->texture_coord) [tri_idx] = glm::vec2(1.0f,0.0f);
	(space_instance->mesh) [tri_idx] = positions[b]; tri_idx++;

	(space_instance->texture_coord) [tri_idx] = glm::vec2(1.0f,1.0f);
	(space_instance->mesh) [tri_idx] = positions[c]; tri_idx++;

	(space_instance->texture_coord) [tri_idx] = glm::vec2(0.0f,0.0f);
	(space_instance->mesh) [tri_idx] = positions[a]; tri_idx++;

	(space_instance->texture_coord) [tri_idx] = glm::vec2(1.0f,1.0f);
	(space_instance->mesh) [tri_idx] = positions[c]; tri_idx++;

	(space_instance->texture_coord) [tri_idx] = glm::vec2(1.0f,0.0f);
	(space_instance->mesh) [tri_idx] = positions[d]; tri_idx++;


}

};//anonymous namespace


void space::create_mesh()
{
	float cube_side = this->side;
	//Eight vertices in homogenous coordinates
	// glm::vec4 positions[8] = {
	// glm::vec4(0.0, 0.0, 0.0, 1.0),
	// glm::vec4(cube_side, 0.0, 0.0, 1.0),
	// glm::vec4(0.0, cube_side , 0.0, 1.0),
	// glm::vec4(cube_side, cube_side, 0.0, 1.0),
	// glm::vec4(0.0, 0.0, cube_side, 1.0),
	// glm::vec4(cube_side, 0.0, cube_side, 1.0),
	// glm::vec4(0.0, cube_side , cube_side, 1.0),
	// glm::vec4(cube_side, cube_side, cube_side, 1.0)
	// };

	glm::vec4 positions[8] = {
	glm::vec4(0.0, 0.0, 0.0, 1.0),
	glm::vec4(cube_side, 0.0, 0.0, 1.0),
	glm::vec4(0.0, cube_side , 0.0, 1.0),
	glm::vec4(cube_side, cube_side, 0.0, 1.0),
	glm::vec4(0.0, 0.0, cube_side, 1.0),
	glm::vec4(cube_side, 0.0, cube_side, 1.0),
	glm::vec4(0.0, cube_side , cube_side, 1.0),
	glm::vec4(cube_side, cube_side, cube_side, 1.0)
	};

	for(int i=0; i<8 ; i++)
		positions[i] = positions[i] - glm::vec4( cube_side/2.0f , cube_side/2.0f , cube_side/2.0f, 0.0f);

	// glm::vec2 tex_coords[8] = {
	// glm::vec2(0.0f,0.0f),
	// glm::vec2(1.0f,0.0f),
	// glm::vec2(0.0f,1.0f),
	// glm::vec2(1.0f,1.0f),
	// glm::vec2(1.0f,1.0f),
	// glm::vec2(0.0f,1.0f),
	// glm::vec2(1.0f,0.0f),
	// glm::vec2(1.0f,1.0f)
	// };



	this->mesh.resize(36);//this is the final number of vertices
	this->texture_coord.resize(36);//this is the final number of vertices

	int tri_idx=0;
	quad( 0,1,3,2 , tri_idx ,  positions , this);
	quad( 2,3,7,6 , tri_idx ,  positions , this);
	quad( 4,5,7,6 , tri_idx ,  positions , this);
	quad( 0,1,5,4 , tri_idx ,  positions , this);
	quad( 1,5,7,3 , tri_idx ,  positions , this);

}

//==================================================================================
void space::get_shaders(std::string vertex_shader, std::string fragment_shader)
{
	std::string vertex_shader_file(vertex_shader);
	std::string fragment_shader_file(fragment_shader);

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	this->shader = csX75::CreateProgramGL(shaderList);


}

//==================================================================================
void space::init_buffers()
{
	
	glUseProgram(this->shader);

	//creating vao
	this->vao.push_back(0);
	glGenVertexArrays (1, &this->vao[0]);
	glBindVertexArray (this->vao[0]);


	//vertex data
	this->vbo.push_back(0);
	glGenBuffers (1, &this->vbo[0]);
  	glBindBuffer (GL_ARRAY_BUFFER, this->vbo[0]);
  	glBufferData (GL_ARRAY_BUFFER, this->mesh.size()*sizeof (glm::vec4), this->mesh.data(), GL_STATIC_DRAW);

  	GLuint vPosition = 0; //your convention
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	//texture coordinates
	this->vbo.push_back(0);
	glGenBuffers (1, &this->vbo[1]);
  	glBindBuffer (GL_ARRAY_BUFFER, this->vbo[1]);
  	glBufferData (GL_ARRAY_BUFFER, this->texture_coord.size()*sizeof (glm::vec2), this->texture_coord.data(), GL_STATIC_DRAW);

  	GLuint texCoord = 2; //your convention
	glEnableVertexAttribArray( texCoord );
	glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );



}

//==================================================================================

namespace
{

	void setUniform3f(const GLchar* uName , float vector[], GLuint shader)
	{
		GLint location_temp = glGetUniformLocation( shader, uName);

		if(location_temp == -1)
			printf("\n %s not found", uName);

		GLuint location = location_temp;

		glProgramUniform3f( shader ,location , vector[0], vector[1], vector[2]);
	}

	void setUniform1f(const GLchar* uName, float value, GLuint shader)
	{
		GLint location_temp = glGetUniformLocation( shader, uName);

		if(location_temp == -1)
			printf("\n %s not found", uName);

		GLuint location = location_temp;

		glProgramUniform1f(shader, location , value);

		// glUniform1f( location , value );
	}



};//end of anonymous namespace

void space::set_constant_uniforms(ONAS_state state)
{
	//glUseProgram(this->shader);

	float pi = glm::pi<float>(); 

	printf("\n setting space");


	setUniform3f( "u_LightDir", state.lightDir , this->shader);

	float ooWaveLen4[3] =
	{
	1 / pow( state.m_Wavelength[0], 4.0f ),
	1 / pow( state.m_Wavelength[1], 4.0f ),
	1 / pow( state.m_Wavelength[2], 4.0f )
	};

	setUniform3f( "u_InvWavelength", ooWaveLen4 , this->shader);

	setUniform1f( "u_InnerRadius", state.m_InnerRadius , this->shader);
	setUniform1f( "u_OuterRadius", state.m_OuterRadius , this->shader);
	setUniform1f( "u_KrESun", state.m_Kr * state.m_ESun , this->shader);
	setUniform1f( "u_KmESun", state.m_Km * state.m_ESun , this->shader);
	setUniform1f( "u_Kr4PI", state.m_Kr * (float)(4.0 * pi) , this->shader);
	setUniform1f( "u_Km4PI", state.m_Km * (float)(4.0 * pi) , this->shader);
	setUniform1f( "u_Scale", 1.0f / (state.m_OuterRadius - state.m_InnerRadius) , this->shader);
	setUniform1f( "u_ScaleDepth", state.m_RayleighScaleDepth , this->shader);

	setUniform1f( "u_ScaleOverScaleDepth",
	    1.0f / ((state.m_OuterRadius - state.m_InnerRadius) * state.m_RayleighScaleDepth) , this->shader);

	setUniform1f( "u_g", state.m_g , this->shader);
}

//==================================================================================

void space::set_non_constant_uniforms(MVPmatrices set)
{
	GLuint location;

	location = glGetUniformLocation( this->shader , "u_CameraPos");
	glProgramUniform3f(this->shader, location, set.CameraPosition[0] , set.CameraPosition[1] , set.CameraPosition[2]  );

	location = glGetUniformLocation( this->shader, "u_ModelMatrix");
	glProgramUniformMatrix4fv(this->shader ,location, 1, GL_FALSE, glm::value_ptr(set.Model));

	location = glGetUniformLocation( this->shader, "u_ViewMatrix");
	glProgramUniformMatrix4fv(this->shader, location, 1, GL_FALSE, glm::value_ptr(set.View));

	location = glGetUniformLocation( this->shader, "u_ProjectionMatrix");
	glProgramUniformMatrix4fv(this->shader , location, 1, GL_FALSE, glm::value_ptr(set.Projection));

}



//==================================================================================
void space::draw(GLuint texture_enum)
{


	glUseProgram(this->shader);
	glBindVertexArray (this->vao[0]);

	GLuint texLoc = glGetUniformLocation(this->shader, "u_texture");
	glProgramUniform1i(this->shader ,texLoc, texture_enum);

	glDrawArrays( GL_TRIANGLES, 0,  this->mesh.size() ) ;

}
//==================================================================================