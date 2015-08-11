#include "src/fw.h"
#include "src/program.h"
#include "src/buffer.h"

GLfloat points[] = {0.0, 0.5, -0.3, -0.3, 0.3, -0.3};

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

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char** argv) {
  FW fw("Basic Sample");
  fw.setup();
  fw.setKeyCallback(keyCallback);

  Program program;
  program.loadShaderFromFile("simple.vert");
  program.loadShaderFromFile("simple.frag");
  program.setup();
  program.use();

  int attrib = glGetAttribLocation(program.id, "aPosition");
  int uniform = glGetUniformLocation(program.id, "uColor");

  Buffer buffer = Buffer(GL_ARRAY_BUFFER);
  buffer.setupWithData(points, sizeof(points), GL_STATIC_DRAW);

  glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(attrib);
  glUniform4f(uniform, 0.0, 1.0, 0.0, 1.0);

  fw.runMainLoop(renderFunction);
  return 0;
}
