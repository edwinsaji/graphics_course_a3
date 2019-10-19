#include "main.hpp"

GLuint create_shader(std::string vertex_shader, std::string fragment_shader)
{
  // Load shaders and use the resulting shader program
  // std::string vertex_shader_file("03_vshader.glsl");
  // std::string fragment_shader_file("03_fshader.glsl");

  std::string vertex_shader_file(vertex_shader);
  std::string fragment_shader_file(fragment_shader);

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  return csX75::CreateProgramGL(shaderList);
}


void initBuffersGL()
{
  shaderProgram = create_shader("../src/vshader.glsl","../src/fshader.glsl");
  glUseProgram( shaderProgram );

  earth1.create_vertices(1.0f);
  cam_radius = 1.001f;
  earth1.init_buffers(shaderProgram);

  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

}

void renderGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glm::mat4 rotation_matrix;


  // rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
  // rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
  // rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));

  // glm::vec4 cam_pos(0.0f,0.0f,cam_radius,1.0f) ,cam_up(0.0f,1.0f,0.0f,1.0f) ;

  // glm::mat4 lookat_matrix = glm::lookAt(glm::vec3(cam_pos),glm::vec3(0.0f),glm::vec3(cam_up));

  // //glm::mat4 projection_matrix = glm::frustum(-2.0f,2.0f,-2.0f,2.0f,2.0f,9.0f); 
  // //glm::mat4 projection_matrix = glm::ortho (-3.0f,3.0f,-3.0f,3.0f,-10.0f,10.0f);
  // glm::mat4 projection_matrix = glm::perspective( glm::radians(80.0f) , 1.0f , 0.00001f , cam_radius + earth1.radius );

  // view_matrix = projection_matrix * lookat_matrix * rotation_matrix;

  view_matrix = camera1.view_matrix;


  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  earth1.draw();

  
}



  //! The pointer to the GLFW window
  GLFWwindow* window;

int main(int argc, char** argv)
{


  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;
  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 6: Texturing a cube", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }
  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
  //mouse callback
  glfwSetCursorPosCallback(window , csX75::cursorPositionCallback);

  //glfwSetCursorEnterCallback(window, csX75::cursorEnterCallback);
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();


  double lastTime = glfwGetTime();
  int nbFrames = 0;


  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {

      double currentTime = glfwGetTime();
      nbFrames++;

      if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
        // printf and reset timer
        printf("%f ms/frame\n", 1000.0/double(nbFrames));
        nbFrames = 0;
        lastTime += 1.0;
      }
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}