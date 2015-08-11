#include "texture.h"

#include "base/structure.h"
#include "base/util.h"


const string kDebugTag = "[Texture] ";
static int sTextureNumber = 0;

Texture::Texture()
  : id(-1),
    type(-1),
    number(sTextureNumber++) {
}

Texture::Texture(GLenum t)
  : type(t) {
  glGenTextures(1, &id);
  number = sTextureNumber++;
  cout << kDebugTag << number<< endl;
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
  glActiveTexture(GL_TEXTURE0 + number);
  glBindTexture(type, id);
}
