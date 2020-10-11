//
// Created by Vladimir Shubarin on 10/10/20.
//

#ifndef CGLABS_INCLUDE_VHUNDEF_VERTEX_GROUP_HPP_
#define CGLABS_INCLUDE_VHUNDEF_VERTEX_GROUP_HPP_

#include <utility>
#include <vector>
#include "vertex.hpp"
class VertexGroup {
 private:
  std::vector<Vertex> vertices;
  short type;
 public:
  explicit VertexGroup(short _type) {
	type = _type;
  }
  VertexGroup(std::vector<Vertex> _vertices, short _type) {
	vertices = std::move(_vertices);
	type = _type;
  }
  void addVertex(Vertex newVertex) {
	vertices.emplace_back(newVertex);
  }
  void changeVertex(Vertex previousVal, Vertex newVal) {
	for (auto &vertex:vertices) {
	  if (vertex == previousVal) {
		vertex = newVal;
	  }
	}
  }

};

#endif //CGLABS_INCLUDE_VHUNDEF_VERTEX_GROUP_HPP_
