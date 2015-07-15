#include "buffer_manager.h"

#include <GLES3/gl3.h>
#include <iostream>
using namespace std;

Buffer::Buffer()
  : id(0),
    type(0) {
}

Buffer::Buffer(int n)
  : id(n),
    type(0) {
}

Buffer::~Buffer() {
}

int Buffer::getId() const {
  return id;
}

BufferManager::BufferManager() {
  buffers.clear();
}

BufferManager::BufferManager(int number) {
  buffers.resize(number);
  size = new GLuint[number];
  glGenBuffers(number, size);
}

BufferManager::~BufferManager() {
}

int BufferManager::createBuffer(int number) {
  buffers[number] = Buffer(size[number]);
}

void BufferManager::bindBuffer(int number, GLenum type) {
  buffers[number].type = type;
  glBindBuffer(type, buffers[number].getId());
}

void BufferManager::setBufferData(int number, GLsizeiptr length, GLvoid* data, GLenum usage) {
  glBufferData(buffers[number].type, length, data, usage);
}
