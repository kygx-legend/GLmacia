#ifndef TEXTURE_H
#define TEXTURE_H

#include "base/import.h"
#include "sampler.h"


class Texture {
 public:
  explicit Texture();
  explicit Texture(GLenum, string);
  virtual ~Texture();
  void active();

  GLuint id;
  GLenum type;
  GLuint unit;
  Sampler sampler;
};

#endif
