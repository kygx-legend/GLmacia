#include "src/fw.h"
#include "src/program.h"
#include "src/buffer.h"
#include "src/texture.h"


Program program;
Texture texture;

GLfloat data[] = {
    -0.5, 0.5, 0.0, 1.0,
    -0.5, -0.5, 0.0, 0.0,
    0.5, 0.5, 1.0, 1.0,
    0.5, -0.5, 1.0, 0.0
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
  fw.setKeyCallback(keyCallback);

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

  int uSampler = glGetUniformLocation(program.id, "uSampler");
  texture = Texture(GL_TEXTURE_2D, "e_05_simple_texture_r_01.jpg");
  texture.sampler.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
  texture.sampler.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
  texture.sampler.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  texture.sampler.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  texture.sampler.setParameterf(GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
  texture.active(uSampler);

  fw.runMainLoop(renderFunction);
  return 0;
}
