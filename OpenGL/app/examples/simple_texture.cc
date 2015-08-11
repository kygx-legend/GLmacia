#include "src/fw.h"
#include "src/program.h"
#include "src/buffer.h"
#include "src/texture.h"


GLfloat data[] = {
    -0.3, 0.3, 0.0, 1.0,
    -0.3, -0.3, 0.0, 0.0,
    0.3, 0.3, 1.0, 1.0,
    0.3, -0.3, 1.0, 0.0
};

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

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int main(int argc, char** argv) {
  FW fw("Texture Sample");
  fw.setup();
  fw.setKeyCallback(keyCallback);

  Program program;
  program.loadShaderFromFile("simple_texture.vert");
  program.loadShaderFromFile("simple_texture.frag");
  program.setup();
  program.use();

  int position = glGetAttribLocation(program.id, "vPosition");
  int texcoord = glGetAttribLocation(program.id, "vTexCoord");
  Buffer buffer = Buffer(GL_ARRAY_BUFFER);
  buffer.setupWithData(data, sizeof(data), GL_STATIC_DRAW);

  glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, NULL);
  glEnableVertexAttribArray(position);
  glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const GLvoid*)(sizeof(float) * 2));
  glEnableVertexAttribArray(texcoord);

  int sampler = glGetUniformLocation(program.id, "uSampler");
  Texture texture(GL_TEXTURE_2D);
  texture.setupWithImage("e_05_simple_texture_r_02.jpg");
  texture.active();
  glUniform1i(sampler, texture.unit);

  fw.runMainLoop(renderFunction);
  return 0;
}
