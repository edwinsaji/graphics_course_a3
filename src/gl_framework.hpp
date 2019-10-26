

#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))





namespace csX75
{
  //! Initialize GL State
  void initGL(void);
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

   void cursorPositionCallback (GLFWwindow *window , double xPos , double yPos);

};

#ifndef _GLM_CONSTANTS_
#define _GLM_CONSTANTS_
#include<glm/gtc/constants.hpp>
#include<glm/trigonometric.hpp>
#endif

#ifndef _GLM_VEC4_
#define _GLM_VEC4_
#include "glm/vec4.hpp"
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


#endif