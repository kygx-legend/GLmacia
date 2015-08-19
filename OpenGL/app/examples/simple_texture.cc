#include "src/fw.h"
#include "src/program.h"
#include "src/buffer.h"
#include "src/texture.h"


Program program;
Texture texture;
Sampler sampler;

GLfloat data[] = {
    -0.5, 0.5, 0.0, 2.0,
    -0.5, -0.5, 0.0, 0.0,
    0.5, 0.5, 2.0, 2.0,
    0.5, -0.5, 2.0, 0.0
};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action != GLFW_PRESS)
    return;

  switch (key) {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_1:
        sampler.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
        sampler.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
        break;
    case GLFW_KEY_2:
        sampler.setParameteri(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        sampler.setParameteri(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        break;
    case GLFW_KEY_3:
        sampler.setParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        sampler.setParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    case GLFW_KEY_4:
        sampler.setParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        sampler.setParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        break;
    default:
        break;
  }
}

void renderFunction() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  int uSampler = glGetUniformLocation(program.id, "uSampler");
  texture.active(uSampler);

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

  texture = Texture(GL_TEXTURE_2D, "e_05_simple_texture_r_01.jpg");

  sampler = Sampler(texture.unit);
  sampler.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  sampler.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  sampler.setParameterf(GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

  texture.setSampler(sampler);

  fw.runMainLoop(renderFunction);
  return 0;
}
