#include "earth.hpp"

#include "shader_util.hpp"

#include "texture.hpp"


#include <cmath>

//==================================================================================
void earth::create_mesh (int no_of_longs, int no_of_lats)
{
	//creates and fills mesh as well as normals and texcoords

	float PI = glm::pi<float>();
	//we will assume radius of 1 for this sphere. 

	float lats,longs;

	// float slices=(180/(float(Lats)*10))/2;
	// float sectors=(180/(float(Longs)*10))/2;

	float slices = 2.0 * PI/float(no_of_lats);
	float sectors = PI / float(no_of_longs);

	float l;

	for (lats = 0.0; lats <= PI; lats+=sectors)  
	{
		for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
		{
			float x = this->radius * sin(lats) * cos(longs);
			float y = this->radius * sin(lats) * sin(longs);
			float z = this->radius * cos(lats);
			glm::vec4 pt(x, y, z, 1.0);

			this->mesh.push_back(pt);
			this->normals.push_back(glm::normalize(glm::vec3(pt)));
			this->texture_coord.push_back( glm::vec2( 1.0-longs/(2*PI) , lats/PI ) );


			if(lats+sectors>PI)
				l=PI;
			else
				l=lats+sectors;


			x = this->radius * sin(l) * cos(longs);
			y = this->radius * sin(l) * sin(longs);
			z = this->radius * cos(l);
			pt =glm::vec4(x, y, z, 1.0);

			this->mesh.push_back(pt);
			this->normals.push_back(glm::normalize(glm::vec3(pt)));
			this->texture_coord.push_back( glm::vec2( 1.0-longs/(2*PI) , l/PI ) );


		}
	}


}

//==================================================================================
void earth::get_shaders(std::string vertex_shader, std::string fragment_shader)
{
	std::string vertex_shader_file(vertex_shader);
	std::string fragment_shader_file(fragment_shader);

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	this->shader = csX75::CreateProgramGL(shaderList);


}

//==================================================================================
void earth::init_buffers()
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

	//normals
	this->vbo.push_back(0);
	glGenBuffers( 1 , &this->vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER , this->vbo[1]);
	glBufferData (GL_ARRAY_BUFFER, this->normals.size()*sizeof(glm::vec3), this->normals.data(), GL_STATIC_DRAW);

	GLuint vNormal = 1; //your convention
	glEnableVertexAttribArray( vNormal);
	glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	//texture coordinates
	this->vbo.push_back(0);
	glGenBuffers (1, &this->vbo[2]);
  	glBindBuffer (GL_ARRAY_BUFFER, this->vbo[2]);
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

		printf("\n%s : (%f,%f,%f)", uName , vector[0] ,vector[1] , vector[2] );

		GLuint location = location_temp;

		glProgramUniform3f( shader ,location , vector[0], vector[1], vector[2]);
	}

	void setUniform1f(const GLchar* uName, float value, GLuint shader)
	{
		GLint location_temp = glGetUniformLocation( shader, uName);

		if(location_temp == -1)
			printf("\n %s not found", uName);

		printf("\n%s : %f", uName ,value );

		GLuint location = location_temp;

		glProgramUniform1f(shader, location , value);

		// glUniform1f( location , value );
	}



};//end of anonymous namespace


void earth::set_constant_uniforms(ONAS_state state)
{
	// glUseProgram(this->shader);

	float pi = glm::pi<float>(); 

	printf("\n setting earth");

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

void earth::set_non_constant_uniforms(MVPmatrices set)
{
	GLuint location;

	location = glGetUniformLocation( this->shader , "u_CameraPos");
	glProgramUniform3f(this->shader, location, set.CameraPosition[0] , set.CameraPosition[1] , set.CameraPosition[2]  );

	location = glGetUniformLocation( this->shader, "u_ModelMatrix");
	glProgramUniformMatrix4fv(this->shader,location, 1, GL_FALSE, glm::value_ptr(set.Model));

	location = glGetUniformLocation( this->shader, "u_ViewMatrix");
	glProgramUniformMatrix4fv(this->shader ,location, 1, GL_FALSE, glm::value_ptr(set.View));

	location = glGetUniformLocation( this->shader, "u_ProjectionMatrix");
	glProgramUniformMatrix4fv(this->shader ,location, 1, GL_FALSE, glm::value_ptr(set.Projection));

}



//==================================================================================
void earth::draw( GLuint texture_enum)
{

	glUseProgram(this->shader);

	glBindVertexArray (this->vao[0]);

	GLuint texLoc = glGetUniformLocation(this->shader, "u_texture");
	glProgramUniform1i(this->shader, texLoc, texture_enum);

	glDrawArrays( GL_TRIANGLE_STRIP, 0,  this->mesh.size() ) ;

}


