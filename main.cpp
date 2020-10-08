#include "include/vhundef/screen.hpp"
#include "include/aixlog.hpp"
#include "include/vhundef/shaders/shader.hpp"
void handleKeyboard(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
  LOG(DEBUG) << "Keyboard callback \n";
  if ((key == GLFW_KEY_Q && action == GLFW_PRESS) && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
	LOG(INFO) << "Got quit command, destroying window\n";
	glfwDestroyWindow(window);
	LOG(DEBUG) << "Quiting...\n";
	glfwTerminate();
	exit(0);
  }
}
void drawLab1() {
  // Nothing to do here
}
[[maybe_unused]] void drawLab2() {
  { // Var 3 drawing 1
	drawLine({{-0.9, 0.9}, {-0.9, 0.5}}, {255, 0, 0});
	drawLine({{-0.9, 0.5}, {-0.7, 0.5}}, {255, 0, 0});
	drawLine({{-0.7, 0.5}, {-0.8, 0.6}}, {255, 0, 0});
	drawLine({{-0.8, 0.6}, {-0.7, 0.8}}, {255, 0, 0});
	drawLine({{-0.7, 0.8}, {-0.6, 0.66}}, {255, 0, 0});
	drawLine({{-0.6, 0.66}, {-0.65, 0.5}}, {255, 0, 0});
	drawLine({{-0.65, 0.5}, {-0.45, 0.5}}, {255, 0, 0});

  }
  { // drawing 2
	drawLine({{0.1, 0.8}, {0.2, 0.9}}, {0, 255, 0});
	drawLine({{0.2, 0.9}, {0.3, 0.83}}, {0, 255, 0});
	drawLine({{0.3, 0.83}, {0.5, 0.9}}, {0, 255, 0});
	drawLine({{0.5, 0.9}, {0.5, 0.75}}, {0, 255, 0});
	drawLine({{0.5, 0.75}, {0.23, 0.75}}, {0, 255, 0});
	drawLine({{0.23, 0.75}, {0.3, 0.5}}, {0, 255, 0});
	drawLine({{0.3, 0.5}, {0.13, 0.57}}, {0, 255, 0});
	drawLine({{0.13, 0.57}, {0.1, 0.8}}, {0, 255, 0});
  }
  { // drawing 3
	drawLine({{-0.9, -0.9}, {-0.9, -0.5}}, {0, 0, 255});
	drawLine({{-0.9, -0.5}, {-0.7, -0.55}}, {0, 0, 255});
	drawLine({{-0.7, -0.55}, {-0.4, -0.45}}, {0, 0, 255});
	drawLine({{-0.4, -0.45}, {-0.36, -0.9}}, {0, 0, 255});
	drawLine({{-0.36, -0.9}, {-0.56, -0.9}}, {0, 0, 255});
	drawLine({{-0.56, -0.9}, {-0.56, -0.7}}, {0, 0, 255});
	drawLine({{-0.56, -0.7}, {-0.66, -0.7}}, {0, 0, 255});
	drawLine({{-0.66, -0.7}, {-0.8, -0.83}}, {0, 0, 255});
	drawLine({{-0.8, -0.83}, {-0.66, -0.9}}, {0, 0, 255});
	drawLine({{-0.66, -0.9}, {-0.9, -0.9}}, {0, 0, 255});
  }
}
void gl3test() {
  // This will identify our vertex buffer
  GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  // An array of 3 vectors which represents 3 vertices
  static const GLfloat g_vertex_buffer_data[] = {
	  -1.0f, -1.0f, 0.0f,
	  1.0f, -1.0f, 0.0f,
	  0.0f, 1.0f, 0.0f,
  };
  // Give our vertices to OpenGL.
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  // 1st attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
	  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	  3,                  // size
	  GL_FLOAT,           // type
	  GL_FALSE,           // normalized?
	  0,                  // stride
	  (void *)0            // array buffer offset
  );
// Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
  glDisableVertexAttribArray(0);
}
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
  LOG(INFO) << "Hello, World!\n";
  GLFWwindow *window = Screen::createWindow({100, 100}, {640, 480}, "Test");
  vec2<int> windowSize = Screen::getWindowSize(window);
  glfwGetFramebufferSize(window, &windowSize.a, &windowSize.b);
  glfwSetKeyCallback(window, handleKeyboard);

  Shader shader("../include/vhundef/shaders/VertexShader.glsl", "../include/vhundef/shaders/FragmentShader.glsl");
  glUseProgram(shader.uid);

  {
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
// This will identify our vertex buffer
	GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	while (glfwWindowShouldClose(window) == GL_FALSE) {
	  // 1st attribute buffer : vertices
	  glEnableVertexAttribArray(0);
	  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	  glVertexAttribPointer(
		  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		  3,                  // size
		  GL_FLOAT,           // type
		  GL_FALSE,           // normalized?
		  0,                  // stride
		  (void *)0            // array buffer offset
	  );
// Draw the triangle !
	  glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	  glDisableVertexAttribArray(0);
	  Screen::updateScreen(gl3test, {0, 0, 0}, window, true, false);
	}
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  LOG(INFO) << "Program quit\n";
  return 0;
}

