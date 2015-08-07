#include <iostream>

#include <GLES3/gl3.h>

#include "macia/render_manager.h"
#include "macia/program_manager.h"
#include "macia/structure.h"
#include "macia/util.h"

using namespace std;

RenderManager render;
int program = 0;
int buffer = 0;
int texture = 0;
GLfloat data[] = {
    -0.3, 0.3, 0.0, 1.0,
    -0.3, -0.3, 0.0, 0.0,
    0.3, 0.3, 1.0, 1.0,
    0.3, -0.3, 1.0, 0.0
};

void renderFunction() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glutSwapBuffers();
}

int main(int argc, char** argv) {
  render.init(argc, argv);
  render.setupProgram(program, "simple_texture.vert", "simple_texture.frag");

  int position = render.program_manager.getLocation(program, 0, "vPosition");
  int texcoord = render.program_manager.getLocation(program, 0, "vTexCoord");
  render.buffer_manager.createBuffer(buffer);
  render.buffer_manager.bindBuffer(buffer, GL_ARRAY_BUFFER);
  render.buffer_manager.setBufferData(buffer, 16 * sizeof(float), data, GL_STATIC_DRAW);
  glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, NULL);
  glEnableVertexAttribArray(position);
  glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const GLvoid*)(sizeof(float) * 2));
  glEnableVertexAttribArray(texcoord);

  int sampler = render.program_manager.getLocation(program, 1, "uSampler");
  render.texture_manager.createTexture(texture);

  ImageData* image = new ImageData;
  if (ReadJPEGFile(image, kImagePath + "/e_05_simple_texture_r_02.jpg")) {
    render.texture_manager.setupTexture(texture, GL_TEXTURE_2D, image);
    glUniform1i(sampler, texture);
  }

  render.setRenerderFunction(renderFunction);
  render.runMainLoop();
  return 0;
}
