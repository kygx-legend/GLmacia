#include "shader.h"


const int kLogCharSize = 512;
const string kDebugTag = "[Shader] ";

Shader::Shader()
  : content(""),
    type(-1),
    id(-1) {
}

Shader::Shader(GLenum t, string c)
  : type(t),
    content(c) {
  id = glCreateShader(t);
}

Shader::~Shader() {
}

bool Shader::load() {
  const char* source = content.c_str();
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);
  GLint is_successful;
  glGetShaderiv(id, GL_COMPILE_STATUS, &is_successful);
  if (!is_successful) {
    GLchar error[kLogCharSize];
    glGetShaderInfoLog(id, kLogCharSize, NULL, error);
    cout << kDebugTag << "Compile error:" << endl;
    cout << kDebugTag << string(error) << endl;
    return false;
  }
  return true;
}
