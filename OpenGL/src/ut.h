#ifndef UT_H
#define UT_H

#include "base/import.h"
#include "base/structure.h"

#include <GL/freeglut.h>


typedef void (*VoidFunction)();

class UT {
 public:
  explicit UT();
  explicit UT(string);
  virtual ~UT();

  void setRenderFunction(VoidFunction);
  void setIdleFunction(VoidFunction);

  void init(int, char**);
  void runMainLoop();

 protected:
  void tearDown();

 private:
  ContextVersion m_context_version;
  Dimension2D m_window_size;
  string m_window_title;
};

#endif
