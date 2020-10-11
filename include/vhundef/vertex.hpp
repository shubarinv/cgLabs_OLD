//
// Created by Vladimir Shubarin on 10/9/20.
//

#ifndef CGLABS_INCLUDE_VHUNDEF_VERTEX_HPP_
#define CGLABS_INCLUDE_VHUNDEF_VERTEX_HPP_
#include "lib2D.hpp"
class Vertex {
  vec3<float> position{};
 public:
  [[nodiscard]] const vec3<float> &getPosition() const {
	return position;
  }
  [[nodiscard]] const vec3<float> &getColor() const {
	return color;
  }
  explicit Vertex(vec3<float> _pos = {0, 0, 0}, vec3<float> _color = {0, 0, 0}) {
	setPosition(_pos);
	setColor(_color);
  }
 private:
  vec3<float> color{};
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
  bool operator==(const Vertex &b) const {
	if (position.a == b.position.a &&
		position.b == b.position.b &&
		position.c == b.position.c) {
	  return true;
	} else return false;
  }
};

#endif //CGLABS_INCLUDE_VHUNDEF_VERTEX_HPP_
