#include "shader_manager.h"

#include <GLES3/gl3.h>

#include "util.h"

Shader::Shader()
  : content(""),
    type(0),
    id(0) {
}

Shader::Shader(string s, GLenum t)
  : content(s),
    type(t) {
  id = glCreateShader(type);
}

Shader::~Shader() {
}

GLuint Shader::getId() const {
  return id;
}

bool Shader::load() const {
  const char* source = content.c_str();
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  GLint is_successful;
  glGetShaderiv(id, GL_COMPILE_STATUS, &is_successful);
  if (!is_successful)
    return false;
  return true;
}

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
}

bool ShaderManager::loadShaderDirectly(string content, GLenum type) {
  switch (type) {
    case GL_VERTEX_SHADER:
      vertex_shader = Shader(content, type);
      if (vertex_shader.load())
          return true;
    case GL_FRAGMENT_SHADER:
      fragment_shader = Shader(content, type);
      if (fragment_shader.load())
          return true;
    default:
      return false;
  }
}

bool ShaderManager::loadShaderWithFile(string file_path, GLenum type) {
  string content = "";
  if (!ReadFile(content, SHADER_PATH + "/" + file_path))
    return false;
  return loadShaderDirectly(content, type);
}
