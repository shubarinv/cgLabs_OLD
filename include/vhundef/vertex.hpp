//
// Created by Vladimir Shubarin on 10/9/20.
//

#ifndef CGLABS_INCLUDE_VHUNDEF_VERTEX_HPP_
#define CGLABS_INCLUDE_VHUNDEF_VERTEX_HPP_

#include "lib2D.hpp"
class Vertex {
  vec3<float> position{};
  vec3<float> color{};
  explicit Vertex(vec3<float> _pos = {0, 0, 0}, vec3<float> _color = {0, 0, 0}) {
	setPosition(_pos);
	setColor(_color);
  }
  void setPosition(vec3<float> _newPosition) {
	if (_newPosition.a < -1 || _newPosition.a > 1 ||
		_newPosition.b < -1 || _newPosition.b > 1 ||
		_newPosition.c < -1 || _newPosition.c > 1) {
	  LOG(ERROR) << "Invalid location!";
	  throw std::runtime_error("Invalid location for vertex");
	}
	position = _newPosition;
  }
  void setColor(vec3<float> _color) {
	if (_color.a < -1 || _color.a > 1 ||
		_color.b < -1 || _color.b > 1 ||
		_color.c < -1 || _color.c > 1) {
	  LOG(ERROR) << "Invalid color!";
	}
	color = _color;
  }

  float translateToFloatArray() {
	return (position.a, position.b, position.c, color.a, color.b, color.c);
  }
};

#endif //CGLABS_INCLUDE_VHUNDEF_VERTEX_HPP_
