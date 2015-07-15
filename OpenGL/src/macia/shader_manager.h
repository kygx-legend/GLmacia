#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>

#include <GL/freeglut.h>

#include "structure.h"

using namespace std;


class Shader {
 public:
  explicit Shader();
  explicit Shader(string, GLenum);
  virtual ~Shader();
  GLuint getId() const;
  bool load() const;

  string content;
  GLenum type;
  GLuint id;
};

class ShaderManager {
 public:
  explicit ShaderManager();
  virtual ~ShaderManager();
  bool loadShaderDirectly(string, GLenum);
  bool loadShaderWithFile(string, GLenum);

  Shader vertex_shader;
  Shader fragment_shader;
};

#endif
