#ifndef SAMPLER_H
#define SAMPLER_H

#include "base/import.h"


class Sampler {
 public:
  explicit Sampler();
  explicit Sampler(GLuint);
  virtual ~Sampler();

  void setParameteri(GLenum, GLint);
  void setParameterf(GLenum, GLfloat);

  GLuint id;
};

#endif
