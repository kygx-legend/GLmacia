#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "shader_manager.h"

using namespace std;

class Program {
 public:
  explicit Program();
  virtual ~Program();
  GLuint getId() const;
  bool loadShaders(string, string);
  bool attachAndLink();

  GLuint id;
  ShaderManager shader_manager;
};

class ProgramManager {
 public:
  explicit ProgramManager();
  explicit ProgramManager(int);
  virtual ~ProgramManager();
  bool initProgram(int, string, string);
  void useProgram(int);
  GLint getLocation(int, int, string);

  vector<Program> programs;
};
#endif
