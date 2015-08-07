#include "texture_manager.h"

#include <GLES3/gl3.h>
#include <iostream>
using namespace std;

Texture::Texture()
  : id(0),
    type(0) {
}

Texture::Texture(int n)
  : id(n),
    type(0) {
}

Texture::~Texture() {
}

int Texture::getId() const {
  return id;
}

TextureManager::TextureManager() {
  textures.clear();
}

TextureManager::TextureManager(int number) {
  textures.resize(number);
  size = new GLuint[number];
  glGenTextures(number, size);
}

TextureManager::~TextureManager() {
}

int TextureManager::createTexture(int number) {
  textures[number] = Texture(size[number]);
}

void TextureManager::setupTexture(int number, GLenum type, ImageData* image) {
  glActiveTexture(GL_TEXTURE0 + number);
  glBindTexture(type, textures[number].getId());
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(type, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
}
