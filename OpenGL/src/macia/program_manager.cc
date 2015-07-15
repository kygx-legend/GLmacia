#include "program_manager.h"

#include <GLES3/gl3.h>


Program::Program() {
  id = glCreateProgram();
}

Program::~Program() {
}

GLuint Program::getId() const {
  return id;
}

bool Program::loadShaders(string vertex_path, string fragment_path) {
  if (!shader_manager.loadShaderWithFile(vertex_path, GL_VERTEX_SHADER))
    return false;
  if (!shader_manager.loadShaderWithFile(fragment_path, GL_FRAGMENT_SHADER))
    return false;
  return true;
}

bool Program::attachAndLink() {
  glAttachShader(id, shader_manager.vertex_shader.getId());
  glAttachShader(id, shader_manager.fragment_shader.getId());
  glLinkProgram(id);
  return true;
}

ProgramManager::ProgramManager() {
  programs.clear();
}

ProgramManager::ProgramManager(int number) {
  programs.resize(number);
}

ProgramManager::~ProgramManager() {
  programs.clear();
}

bool ProgramManager::initProgram(int location, string vertex_path, string fragment_path) {
  programs[location] = Program();
  if (!programs[location].loadShaders(vertex_path, fragment_path))
    return false;
  if (!programs[location].attachAndLink())
    return false;
  return true;
}

void ProgramManager::useProgram(int program) {
  glUseProgram(programs[program].getId());
}

GLint ProgramManager::getLocation(int program, int type, string name) {
  switch (type) {
    case 0:
      return glGetAttribLocation(programs[program].getId(), name.c_str());
    case 1:
      return glGetUniformLocation(programs[program].getId(), name.c_str());
    defalut:
      return -1;
  }
}
