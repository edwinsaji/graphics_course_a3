#include "gl_framework.hpp"

#include "camera.hpp"

extern GLfloat xrot,yrot,zrot;
extern GLfloat cam_radius;

extern FirstPersonCamera camera1;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  


 
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    // else if (key == GLFW_KEY_LEFT )
    //   yrot -= 1.0;
    // else if (key == GLFW_KEY_RIGHT )
    //   yrot += 1.0;
    // else if (key == GLFW_KEY_UP )
    //   xrot -= 1.0;
    // else if (key == GLFW_KEY_DOWN )
    //   xrot += 1.0;
    // else if (key == GLFW_KEY_PAGE_UP )
    //   zrot -= 1.0;
    // else if (key == GLFW_KEY_PAGE_DOWN)
    //   zrot += 1.0;
    // else if ( key == GLFW_KEY_X && action == GLFW_PRESS)
    //   cam_radius += 0.1;
    // else if ( key == GLFW_KEY_Z && action == GLFW_PRESS && cam_radius >= 1.2f )
    //   cam_radius -= 0.1;

    else if(key == GLFW_KEY_SPACE)
      camera1.update_cam_position(1);
    else if(key == GLFW_KEY_LEFT_CONTROL)
      camera1.update_cam_position(-1);
    else if(key == GLFW_KEY_D)
      camera1.update_cam_position(2);
    else if(key == GLFW_KEY_A)
      camera1.update_cam_position(-2);
    else if(key == GLFW_KEY_W)
      camera1.update_cam_position(3);
    else if(key == GLFW_KEY_S)
      camera1.update_cam_position(-3);



  }



  void cursorPositionCallback (GLFWwindow *window , double xPos , double yPos)
  {
      camera1.update_cam_orientation(float(xPos) ,float(yPos) );
  }



};  
  


