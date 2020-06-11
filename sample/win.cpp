/*
 * Creating simpe OpenGL window that show one RGBA texture
 */

#include <iostream>
#include <vector>

#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#define POINTER(i) reinterpret_cast<const GLvoid*>(i)
#define GLSL(src) "#version 330\n" #src

// Vertex shader for OpenGL window
const char* vertex_shader_text = GLSL (

  in vec2 vPos;
  in vec2 texture_2dcoord;

  out vec2 texture_coord;

  void main()
  {
    gl_Position = vec4(vPos, 0.0, 1.0);
    texture_coord = texture_2dcoord;
  }
);


// Fragment shader for OpenGL window
const char* fragment_shader_text = GLSL (

  in vec2 texture_coord;
  uniform sampler2D texture_data;

  void main()
  {
    gl_FragColor = texture(texture_data, texture_coord);
  }
);


///
/// \brief error_callback
/// \param description
///
static void error_callback(int, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}


///
/// \brief key_callback
/// \param window
/// \param key
/// \param action
///
static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}


///
/// \brief opengl_window_show
/// \param texture_data
///
void opengl_window_show(const unsigned char* texture_data, int win_width, int win_height)
{
  static const struct
  {
      float x, y, u, v;
  } vertices[4] = {
      {-1.f,-1.f, 0.f, 1.f },
      { 1.f,-1.f, 1.f, 1.f },
      {-1.f, 1.f, 0.f, 0.f },
      { 1.f, 1.f, 1.f, 0.f }
  };
  static const int attr_count = 4;

  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit()) exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 0);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

  window = glfwCreateWindow(win_width, win_height, "", NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  if(!gladLoadGL()) { exit(-1); }

  char title[16] = {0};
  sprintf(title, "OpenGL ver. %d.%d", GLVersion.major, GLVersion.minor);
  glfwSetWindowTitle(window, title);
  glfwSwapInterval(1);

  glEnable(GL_BLEND);      // поддержка прозрачности
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint hdl_vao;
  GLuint vertex_buffer, vertex_shader, fragment_shader, program;

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glActiveTexture(GL_TEXTURE0);
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, win_width, win_height,
           0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint vpos_location = glGetAttribLocation (program, "vPos");
  GLint t2d_location  = glGetAttribLocation (program, "texture_2dcoord");

  glGenVertexArrays(1, &hdl_vao);
  glBindVertexArray(hdl_vao);

  glEnableVertexAttribArray(static_cast<GLuint>(vpos_location));
  glVertexAttribPointer(static_cast<GLuint>(vpos_location), 2, GL_FLOAT,
    GL_FALSE, sizeof(float) * attr_count, POINTER(0));

  glEnableVertexAttribArray(static_cast<GLuint>(t2d_location));
  glVertexAttribPointer(static_cast<GLuint>(t2d_location), 2, GL_FLOAT,
    GL_FALSE, sizeof(float) * attr_count, POINTER(sizeof(float) * 2));

  glClearColor(1.f, 1.f, 1.f, 1.f);
  while (!glfwWindowShouldClose(window))
  {
      int width, height;

      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(program);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      glfwSwapBuffers(window);
      glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}

