#include "texture.h"

#include "base/structure.h"
#include "base/util.h"


const string kDebugTag = "[Texture] ";
static GLuint sTextureUnit = 0;

Texture::Texture()
  : id(-1),
    type(-1),
    unit(sTextureUnit++) {
}

Texture::Texture(GLenum t, string file)
  : type(t),
    unit(sTextureUnit++) {
  ImageData image;
  if (!ReadImageFile(image, kImagePath + "/" + file)) {
    cout << kDebugTag << "Failed to load image " << file << endl;
    return;
  }

  glGenTextures(1, &id);
  glBindTexture(type, id);
  glTexImage2D(type, 0, GL_RGB, image.width, image.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image.pixels);
  sampler = Sampler(unit);
}

Texture::~Texture() {
}

void Texture::active(GLint uniform_sampler) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(type, id);
  glUniform1i(uniform_sampler, unit);
}
