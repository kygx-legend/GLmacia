#ifndef STRUCTURE_H
#define STRUCTURE_H


struct ContextVersion {
  int major;
  int minor;
  ContextVersion(int a, int b)
    : major(a),
      minor(b) {
  }
};

struct Dimension2D {
  int width;
  int height;
  Dimension2D(int a, int b)
    : width(a),
      height(b) {
  }
};

struct ImageData {
  unsigned char* pixels;
  int width;
  int height;
};

#endif
