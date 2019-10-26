#include "earth.hpp"
#include "sky.hpp"
#include "space.hpp"
#include "camera.hpp"


#ifndef _ONAS_STATE_
#define _ONAS_STATE_
#include "ONAS_state.hpp"
#endif

#ifndef _MVP_MATRICES_
#define _MVP_MATRICES_
#include "matrices.hpp"
#endif


class scene
{

public:

	ONAS_state State;

	int tesselation;// no of longitudes is assigned to this while no of latitudes is assigned twice this value

	earth Earth;
	sky Sky;
	space Space;
	FirstPersonCamera Camera;

	std::vector< GLuint > texture_ids;

	glm::vec3 LightDirection;



	scene(): 
	State(),
	Earth(State.m_InnerRadius),
	Sky(State.m_OuterRadius),
	Space(30.0f)

	{
		// Earth.radius = (State.m_InnerRadius );
		// Sky.radius = (State.m_OuterRadius );
		// Space.side = (30.0f);
		//std::cout<<"\n inner Radius "<< State.m_OuterRadius<<"\n";

		tesselation = 500;

		LightDirection = glm::normalize(glm::vec3(1.0f,1.0f,1.0f));

		State.lightDir[0] = LightDirection[0];
		State.lightDir[1] = LightDirection[1];
		State.lightDir[2] = LightDirection[2];


	}

	void initialise(void);
	// void update_matrices(void);
	void draw(void);
};