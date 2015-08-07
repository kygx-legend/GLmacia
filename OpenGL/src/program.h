#ifndef PROGRAM_H
#define PROGRAM_H

#include "base/import.h"
#include "shader.h"

class Program {
 public:
  explicit Program();
  virtual ~Program();
  bool loadShader(GLenum, string);
  bool loadShaderFromFile(string);
  bool setup();
  bool use();

  GLuint id;
  vector<Shader> shaders;
 private:
  bool m_is_setup;
};

#endif
