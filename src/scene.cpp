#include "scene.hpp"
#include "shader_util.hpp"
#include "texture.hpp"

void scene::initialise()
{
	//first we have to load textures

	
	this->texture_ids.push_back( csX75::LoadTexture("../textures/space.bmp", 2048 , 2048 ,0) );
	this->texture_ids.push_back( csX75::LoadTexture("../textures/earth.bmp",1000 , 500, 1) );

	//first setup Space
	// this->Space.create_mesh();
	// this->Space.get_shaders("../src/space.vert","../src/space.frag");
	// this->Space.init_buffers();
	// this->Space.set_constant_uniforms(this->State);
	

	//now setup Earth
	this->Earth.create_mesh(this->tesselation , 2 * this->tesselation);
	this->Earth.get_shaders("../src/earth.vert","../src/earth.frag");
	this->Earth.init_buffers();
	this->Earth.set_constant_uniforms(this->State);







	//now setup Sky
	this->Sky.create_mesh(this->tesselation , 2 * this->tesselation);
	this->Sky.get_shaders("../src/sky.vert","../src/sky.frag");
	this->Sky.init_buffers();
	this->Sky.set_constant_uniforms(this->State);
}

void scene::draw()
{

	//first we shall modify the uniforms;
	MVPmatrices MVPearth,MVPsky,MVPspace;

	MVPearth.CameraPosition = MVPspace.CameraPosition = MVPsky.CameraPosition = glm::vec3(this->Camera.cam_pos);

	MVPearth.Model = MVPspace.Model = MVPsky.Model = glm::mat4(1.0f);

	MVPearth.View  = MVPsky.View = this->Camera.view_matrix;

	//MVPspace.View = this->Camera.view_matrix_without_cam_pos;
	MVPspace.View = this->Camera.view_matrix;

	MVPearth.Projection = MVPsky.Projection = this->Camera.projection_matrix;

	

	constexpr static float side = 11.0f; 

	MVPspace.Projection = glm::ortho(-side ,side, -side, side, 0.00001f , 30000.0f);

	//MVPspace.Projection = this->Camera.projection_matrix;






	//first we shall draw Space
	// this->Space.set_non_constant_uniforms(MVPspace);
	// this->Space.draw(0);

	//now we shall draw Earth
	this->Earth.set_non_constant_uniforms(MVPearth);
	this->Earth.draw(1);//the enum for earth



	// //now we shall draw the sky
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);
	this->Sky.set_non_constant_uniforms(MVPsky);
	this->Sky.draw();

	glDisable(GL_BLEND);

}