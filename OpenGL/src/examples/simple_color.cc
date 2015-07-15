#include <iostream>

#include <GLES3/gl3.h>

#include "macia/render_manager.h"
#include "macia/program_manager.h"

using namespace std;

RenderManager render;
int program = 0;
int buffer = 0;
GLfloat points[] = {0.0, 0.5, -0.3, -0.3, 0.3, -0.3};

void renderFunction() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glutSwapBuffers();
}

int main(int argc, char** argv) {
  render.init(argc, argv);
  render.setupProgram(program, "simple_color.vert", "simple_color.frag");

  int attrib = render.program_manager.getLocation(program, 0, "vPosition");
  int uniform = render.program_manager.getLocation(program, 1, "u_color");
  render.buffer_manager.createBuffer(buffer);
  render.buffer_manager.bindBuffer(buffer, GL_ARRAY_BUFFER);
  glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(attrib);
  render.buffer_manager.setBufferData(buffer, 6 * sizeof(float), points, GL_DYNAMIC_DRAW);
  glUniform4f(uniform, 1, 0, 0, 1);

  render.setRenerderFunction(renderFunction);
  render.runMainLoop();
  return 0;
}
