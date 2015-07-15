#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include <vector>

#include <GL/freeglut.h>

using namespace std;

class Buffer {
 public:
  Buffer();
  Buffer(int);
  virtual ~Buffer();
  int getId() const;

  int id;
  GLenum type;
};

class BufferManager {
 public:
  BufferManager();
  BufferManager(int);
  virtual ~BufferManager();
  int createBuffer(int);
  void bindBuffer(int, GLenum);
  void setBufferData(int, GLsizeiptr, GLvoid*, GLenum);
  
  vector<Buffer> buffers;
  GLuint* size;
};

#endif
