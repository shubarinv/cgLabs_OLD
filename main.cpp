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
// draw points 0-3 from the currently bound VAO with current in-use shader
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
  LOG(INFO) << "Hello, World!\n";
  GLFWwindow *window = Screen::createWindow({100, 100}, {640, 480}, "Test");
  vec2<int> windowSize = Screen::getWindowSize(window);
  glfwGetFramebufferSize(window, &windowSize.a, &windowSize.b);
  glfwSetKeyCallback(window, handleKeyboard);

//  Shader shader("VertexShader.glsl", "FragmentShader.glsl");
//  glUseProgram(shader.uid);
  float points[] = {
	  0.0f, 0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f
  };
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  const char *vertex_shader =
	  "#version 400\n"
	  "in vec3 vp;"
	  "void main() {"
	  "  gl_Position = vec4(vp, 1.0);"
	  "}";
  const char *fragment_shader =
	  "#version 400\n"
	  "out vec4 frag_colour;"
	  "void main() {"
	  "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
	  "}";
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);
  while (glfwWindowShouldClose(window) == GL_FALSE) {

	// 1st attribute buffer : vertices
	glUseProgram(shader_programme);
	glBindVertexArray(vao);

	Screen::updateFpsCounter(window);
	Screen::updateScreen(gl3test, {0, 0, 0}, window, true, true);

  }
  glfwDestroyWindow(window);
  glfwTerminate();
  LOG(INFO) << "Program quit\n";
  return 0;
}

