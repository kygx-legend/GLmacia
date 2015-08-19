#include "src/fw.h"


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
          glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    default:
        break;
  }
}

void renderFunction() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
  FW fw("Basic Sample");
  fw.setKeyCallback(keyCallback);
  fw.runMainLoop(renderFunction);
  return 0;
}
