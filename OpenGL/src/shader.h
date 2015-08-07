#ifndef SHADER_H
#define SHADER_H

#include "base/import.h"


class Shader {
 public:
  explicit Shader();
  explicit Shader(GLenum, string);
  virtual ~Shader();
  bool load();

  string content;
  GLenum type;
  GLuint id;
};

#endif
