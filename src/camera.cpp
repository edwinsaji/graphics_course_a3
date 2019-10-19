#include "camera.hpp"

#include "gl_framework.hpp"

#ifndef _MAT_TRANSFORM_
#define _MAT_TRANSFORM_
#include "glm/gtc/matrix_transform.hpp"
#endif

extern GLFWwindow* window;

void FirstPersonCamera::update_cam_orientation( float xpos, float ypos )
{
	float deltaTime = 1.0f;

	int width, height;
	glfwGetWindowSize(::window, &width, &height);

	// Compute new orientation
	float horizontalAngle = mouseSpeed * deltaTime * (float(width)/2 - xpos );
	float verticalAngle   = mouseSpeed * deltaTime * (float(height)/2 - ypos );

	//glm::mat4 rot_matrix = glm::rotate(glm::mat4(1.0f), )

	glm::vec3 up ( glm::rotate( glm::mat4(1.0f) , glm::radians(verticalAngle) , glm::vec3(cam_right)  ) * cam_up );
	glm::vec3 right ( glm::rotate( glm::mat4(1.0f) , glm::radians(horizontalAngle) , up  ) *cam_right );

	

	cam_up = glm::vec4(glm::normalize(up),1.0f);

	cam_right = glm::vec4(glm::normalize(right),1.0f);
	cam_front = glm::vec4( glm::normalize( glm::cross( up , right) ) , 1.0f  );

	update_cam_matrix();


	glfwSetCursorPos(::window , width/2, height/2);

 
}

void  FirstPersonCamera::update_cam_position(int direction)
{
	glm::vec3 up(cam_up),right(cam_right),front(cam_front);

	float deltaTime = 1.0f;


	switch(direction)
	{
		case 1://up
			cam_pos = glm::translate(glm::mat4(1.0f),  movDelta*deltaTime*up) * cam_pos ;
			break;
		case -1://down
			cam_pos = glm::translate(glm::mat4(1.0f), -movDelta*deltaTime*up) * cam_pos ;
			break;
		case 2://right
			cam_pos = glm::translate(glm::mat4(1.0f), movDelta*deltaTime*right) * cam_pos ;
			break;
		case -2://left
			cam_pos = glm::translate(glm::mat4(1.0f), -movDelta*deltaTime*right) * cam_pos ;
			break;
		case 3://front
			cam_pos = glm::translate(glm::mat4(1.0f), movDelta*deltaTime*front) * cam_pos ;
			break;
		case -3://back
			cam_pos = glm::translate(glm::mat4(1.0f), -movDelta*deltaTime*front) * cam_pos ;
			break;
		default:
			break;
	}

	update_cam_matrix();


} 

void FirstPersonCamera::update_cam_matrix()
{
	glm::vec3 lookat_point( glm::vec3(cam_pos)+glm::vec3(cam_front) );

	view_matrix = glm::lookAt( glm::vec3 (cam_pos) , lookat_point , glm::vec3(cam_up) );

	projection_matrix = glm::perspective( glm::radians(80.0f) , 1.0f , 0.00001f , 100.0f );

	
}