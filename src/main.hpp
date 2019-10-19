#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"

// // Translation Parameters
// GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// // Rotation Parameters


GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
GLfloat cam_radius;




// // Camera position and rotation Parameters
// GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 2.0;
// GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
// GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;
// //Running variable to toggle culling on/off
// bool enable_culling=true;
// //Running variable to toggle wireframe/solid modelling
// bool solid=true;
// //Enable/Disable perspective view
// bool enable_perspective=false;

//-------------------------------------------------------------------------

#endif




#ifndef _VEC2_
#define _VEC2_
#include "glm/vec2.hpp"
#endif

#ifndef _VEC3_
#define _VEC3_
#include "glm/vec3.hpp"
#endif

#ifndef _MAT4X4_
#define _MAT4X4_
#include "glm/mat4x4.hpp"
#endif


#ifndef _MAT_TRANSFORM_
#define _MAT_TRANSFORM_
#include "glm/gtc/matrix_transform.hpp"
#endif

#ifndef _TYPE_PTR_
#define _TYPE_PTR_
#include "glm/gtc/type_ptr.hpp"
#endif 



#include "earth.hpp"
#include "camera.hpp"



GLuint shaderProgram;
GLuint viewMatrix;

earth earth1;
FirstPersonCamera camera1;

glm::mat4 view_matrix(1.0f);


