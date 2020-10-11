//
// Created by Vladimir Shubarin on 11.10.2020.
//

#ifndef CGLABS_INCLUDE_VHUNDEF_VERTEX_GROUP_HPP_
#define CGLABS_INCLUDE_VHUNDEF_VERTEX_GROUP_HPP_
#define GL_SILENCE_DEPRECATION
#include <glfw3.h>

#include <utility>
#include "screen.hpp"
class VertexGroup {
 private:
  ///< Hold vertex position data
  GLuint VBO{}; ///< kinda holds attribs for vertices eg Color
  GLuint VAO{};
  std::string name;
  std::vector<float> vertices;
  int type{};

 public:
  [[nodiscard]] GLuint getVao() const {
	return VAO;
  }
  explicit VertexGroup(const std::vector<float> &_vertices, int _type, const std::string &_name = {}) {
	vertices = _vertices;
	name = _name;
	type = _type;
	init();
  }
  explicit VertexGroup(const std::vector<Vertex> &_vertices, int _type, const std::string &_name) {
	for (auto &vertex:_vertices) {
	  auto position = vertex.getPosition();
	  auto color = vertex.getColor();
	  vertices.emplace_back(position.a);
	  vertices.emplace_back(position.b);
	  vertices.emplace_back(position.c);
	  vertices.emplace_back(color.a);
	  vertices.emplace_back(color.b);
	  vertices.emplace_back(color.c);
	}
	if (vertices.size() % 6 != 0) {
	  throw std::runtime_error("Incorrect amount of args!");
	}
	name = _name;
	type = _type;
	init();
  }
  void init() {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); ///< Stating that we will make changes in this buffer from now on

	// Copying vertices from array(vertices) in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)nullptr);
	glEnableVertexAttribArray(0);
// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
  }
  unsigned long getVerticesSize() {
	return vertices.size();
  }
  [[nodiscard]] int getType() const {
	return type;
  }
  void updateVertices(std::vector<float> _updatedVertices) {
	if (_updatedVertices.size() != vertices.size()) {
	  throw std::runtime_error("Can't update vertices, updated array size if different!");
	}
	vertices = std::move(_updatedVertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)nullptr);
	glEnableVertexAttribArray(0);
// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
  }
  std::vector<float> getVertices() {
	return vertices;
  }
};

#endif //CGLABS_INCLUDE_VHUNDEF_VERTEX_GROUP_HPP_
