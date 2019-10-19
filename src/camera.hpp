#ifndef _GLM_VEC4_
#define _GLM_VEC4_
#include "glm/vec4.hpp"
#endif


#ifndef _MAT4X4_
#define _MAT4X4_
#include "glm/mat4x4.hpp"
#endif

class FirstPersonCamera
{

public:

	glm::vec4 cam_up,cam_front,cam_right;

	glm::vec4 cam_pos;

	float mouseSpeed;

	float movDelta;

	float prev_time_orientation ,prev_time_position;

	glm::mat4 projection_matrix , view_matrix;

	void update_cam_orientation(float xpos, float ypos);

	void update_cam_position(int direction); 

	void update_cam_matrix();

	FirstPersonCamera()
	{
		mouseSpeed = 1.0f;
		movDelta = 0.02f;

		cam_up = glm::vec4(0.0f,1.0f,0.0f,1.0f);
		cam_right = glm::vec4(1.0f , 0.0f , 0.0f ,1.0f);
		cam_front = glm::vec4(0.0f,0.0f,-1.0f,1.0f);

		cam_pos = glm::vec4(0.0f,0.0f,3.0f,1.0f);

		update_cam_matrix();

	}
};