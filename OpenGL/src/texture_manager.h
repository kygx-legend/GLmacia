#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <vector>

#include <GL/freeglut.h>

#include "structure.h"

using namespace std;

class Texture {
 public:
  Texture();
  Texture(int);
  virtual ~Texture();
  int getId() const;

  int id;
  GLenum type;
};

class TextureManager {
 public:
  TextureManager();
  TextureManager(int);
  virtual ~TextureManager();
  int createTexture(int);
  void setupTexture(int, GLenum, ImageData*);
  
  vector<Texture> textures;
  GLuint* size;
};

#endif
