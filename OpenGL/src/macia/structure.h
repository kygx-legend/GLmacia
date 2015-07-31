#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef void (*VoidFunction)();

struct ContextVersion {
  int primary;
  int secondary;
  ContextVersion(int p, int s)
    : primary(p),
      secondary(s) {
  }
};

struct TupleInt2D {
  int x;
  int y;
  TupleInt2D(int a, int b)
    : x(a),
      y(b) {
  }
};

struct ImageData {
  unsigned char* pixels;
  long width;
  long height;
};

#endif
