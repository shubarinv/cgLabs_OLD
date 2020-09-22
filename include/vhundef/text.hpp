//
// Created by Vladimir Shubarin on 9/22/20.
//

#ifndef CGLABS_LIBS_VHUNDEF_TEXT_HPP_
#define CGLABS_LIBS_VHUNDEF_TEXT_HPP_

#define GLT_IMPLEMENTATION
#include <cstdio>
#include <glfw3.h>
#include <stdexcept>
#include "lib2D.hpp"
#include "../aixlog.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

class Text {
  struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	vec2<unsigned int> Size;       // Size of glyph
	vec2<int> Bearing;    // Offset from baseline to left/top of glyph
	long Advance;    // Offset to advance to next glyph
  };

  std::map<char, Character> Characters;
 public:
  explicit Text(const std::string &fontName = "FiraCode-Regular.ttf") {
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
	  std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	  throw;
	}

	FT_Face face;
	if (FT_New_Face(ft, "FiraCode-Regular.ttf", 0, &face)) {
	  std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	  throw;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++) {
	  // load character glyph
	  if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		continue;
	  }
	  // generate texture
	  unsigned int texture;
	  glGenTextures(1, &texture);
	  glBindTexture(GL_TEXTURE_2D, texture);
	  glTexImage2D(
		  GL_TEXTURE_2D,
		  0,
		  GL_RED,
		  face->glyph->bitmap.width,
		  face->glyph->bitmap.rows,
		  0,
		  GL_RED,
		  GL_UNSIGNED_BYTE,
		  face->glyph->bitmap.buffer
	  );
	  // set texture options
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  // now store character for later use
	  Character character = {
		  texture,
		  {face->glyph->bitmap.width, face->glyph->bitmap.rows},
		  {face->glyph->bitmap_left, face->glyph->bitmap_top},
		  face->glyph->advance.x
	  };
	  Characters.insert(std::pair<char, Character>(c, character));
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
  }
  /*static  *createText(vec2<float> location={0,0},const std::string& text="",vec3<unsigned short int> color={0,0,0}){
	GLTtext *newText = gltCreateText();
	gltSetText(newText, text.c_str());
	return newText;
  }*/

};

#endif // CGLABS_LIBS_VHUNDEF_TEXT_HPP_
