#include <GLES3/gl3.h>

#include "macia/render_manager.h"

RenderManager render;

void renderFunction() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

int main(int argc, char** argv) {
  render.init(argc, argv);
  render.setRenerderFunction(renderFunction);
  render.runMainLoop();
  return 0;
}
