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

Texture::Texture(GLenum t)
  : type(t),
    unit(sTextureUnit++) {
  glGenTextures(1, &id);
}

Texture::~Texture() {
}

void Texture::setupWithImage(string file) {
  ImageData image;
  if (!ReadImageFile(image, kImagePath + "/" + file)) {
    cout << kDebugTag << "Failed to load image " << file << endl;
    return;
  }

  glBindTexture(type, id);
  glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(type, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
}

void Texture::active() {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(type, id);
}
