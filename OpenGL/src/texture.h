#ifndef TEXTURE_H
#define TEXTURE_H

#include "base/import.h"


class Texture {
 public:
  explicit Texture();
  explicit Texture(GLenum);
  virtual ~Texture();
  void setupWithImage(string);
  void active();

  GLuint id;
  GLenum type;
  int number;
};

#endif
