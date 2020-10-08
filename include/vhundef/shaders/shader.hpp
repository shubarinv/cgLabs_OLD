
#ifndef CGLABS_INCLUDE_VHUNDEF_SHADERS_SHADER_HPP_
#define CGLABS_INCLUDE_VHUNDEF_SHADERS_SHADER_HPP_
#define GL_SILENCE_DEPRECATION
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glfw3.h>
#include "../aixlog.hpp"
class Shader {

 public:
  Shader(const char *vertexPath, const char *fragmentPath) {
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
	  // Open files
	  vShaderFile.open(vertexPath);
	  fShaderFile.open(fragmentPath);
	  std::stringstream vShaderStream, fShaderStream;
	  // Read file's buffer contents into streams
	  vShaderStream << vShaderFile.rdbuf();
	  fShaderStream << fShaderFile.rdbuf();
	  // close file handlers
	  vShaderFile.close();
	  fShaderFile.close();
	  // Convert stream into string
	  vertexCode = vShaderStream.str();
	  fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
	  LOG(ERROR) << "Unable to load shader file!\n";
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
	  glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
	  LOG(ERROR) << "Shader vertex compilation failed\n" << infoLog << "\n";
	}
	LOG(INFO) << "Vertex shader compiled successfully\n";
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
	  glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
	  LOG(ERROR) << "Shader fragment compilation failed\n" << infoLog << "\n";
	}
	LOG(INFO) << "Fragment shader compiled successfully\n";
	// Shader Program
	uid = glCreateProgram();
	glAttachShader(uid, vertex);
	glAttachShader(uid, fragment);
	glLinkProgram(uid);
	// Print linking errors if any
	glGetProgramiv(uid, GL_LINK_STATUS, &success);
	if (!success) {
	  glGetProgramInfoLog(uid, 512, nullptr, infoLog);
	  LOG(INFO) << "Shader linking failed\n" << infoLog << "\n";
	}
	LOG(INFO) << "Shaders were linked successfully\n";
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
  }
  unsigned int uid{};
};

#endif //CGLABS_INCLUDE_VHUNDEF_SHADERS_SHADER_HPP_
