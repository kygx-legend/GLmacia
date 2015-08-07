#ifndef BUFFER_H
#define BUFFER_H

#include "base/import.h"

class Buffer {
 public:
  explicit Buffer();
  explicit Buffer(GLenum);
  virtual ~Buffer();
  bool setupWithData(GLvoid*, GLsizeiptr, GLenum);

  GLuint id;
  GLenum type;
};

#endif
