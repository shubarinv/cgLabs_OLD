//
// Created by Vladimir Shubarin on 9/11/20.
//
#define GL_SILENCE_DEPRECATION

#ifndef CGLABS__LIB2D_HPP_
#define CGLABS__LIB2D_HPP_
#include <vector>
#include <cmath>
#include "OpenGL/gl.h"
#include "../aixlog.hpp"

template<typename T>
struct vec3 {
  T a, b, c;
};
template<typename T>
struct vec2 {
  T a, b;
};

/**
 * @brief Draws a point on the screen
 * @param _x location by x, should be between [-1;1]
 * @param _y location by y, should be between [-1;1]
 * @param
 * @example drawPoint(0.5,0.5,2,{0.5,0.5,0.5});
**/
void drawPoint(vec2<float> location, int pointSize, vec3<float> _color) {
  LOG(DEBUG) << "Drawing dot at: (" << location.a << "," << location.b << ") pointSize: " << pointSize << "\n";
  glColor3f(_color.a, _color.b, _color.c);
  glPointSize(pointSize);
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  glVertex2f(location.a, location.b);
  glEnd();
  glDisable(GL_POINT_SMOOTH);
}
void drawLine(vec2<vec2<float>> lineCoords, vec3<float> _color) {
  LOG(DEBUG) << "Drawing line from: (" << lineCoords.a.a << "," << lineCoords.a.b << ") to: (" << lineCoords.b.a << "," << lineCoords.b.b
			 << ")\n";
  glColor3f(_color.a, _color.b, _color.c);
  glEnable(GL_LINE_SMOOTH);
  glBegin(GL_LINES);
  glVertex2f(lineCoords.a.a, lineCoords.a.b);
  glVertex2f(lineCoords.b.a, lineCoords.b.b);
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}
void drawTriangle(vec3<vec2<float>> triangleSides, vec3<float> _color) {
  glColor3f(_color.a, _color.b, _color.c);
  glEnable(GL_LINE_SMOOTH);
  glBegin(GL_TRIANGLES);
  glVertex2f(triangleSides.a.a, triangleSides.a.b);
  glVertex2f(triangleSides.b.a, triangleSides.b.b);
  glVertex2f(triangleSides.c.a, triangleSides.c.b);
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}
void drawPolygon(const std::vector<vec2<float>> &polygonLines, vec3<float> _color) {
  glColor3f(_color.a, _color.b, _color.c);
  glEnable(GL_LINE_SMOOTH);
  glBegin(GL_POLYGON);
  for (auto &line:polygonLines) {
	glVertex2f(line.a, line.b);
  }
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}
void drawCircle(float cx, float cy, float r, int num_segments, vec3<float> _color) {
  glColor3f(_color.a, _color.b, _color.c);
  glEnable(GL_LINE_SMOOTH);
  glBegin(GL_LINE_LOOP);
  for (int ii = 0; ii < num_segments; ii++) {
	float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
	float x = r * cosf(theta);//calculate the x component
	float y = r * sinf(theta);//calculate the y component
	glVertex2f(x + cx, y + cy);
  }
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}
#endif // CGLABS__LIB2D_HPP_
