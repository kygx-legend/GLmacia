#ifndef FW_H
#define FW_H

#include "base/import.h"
#include "base/structure.h"

#include <GLFW/glfw3.h>


typedef void (*VoidFunction)();
typedef void (*KeyCallback)(GLFWwindow*, int, int, int, int);
typedef void (*MouseCallback)(GLFWwindow*, double, double);
typedef void (*ScrollCallback)(GLFWwindow*, double, double);

class FW {
 public:
  explicit FW();
  explicit FW(string);
  virtual ~FW();

  void setContextVersion(int, int);
  void setWindowSize(int, int);
  void setWindowResizable(bool);

  void setKeyCallback(KeyCallback);
  void setScrollCallback(ScrollCallback);
  void setMouseCallback(MouseCallback);

  void setup();
  void runMainLoop(VoidFunction);

 protected:
  void tearDown();
  bool isInitialized() const {
    return m_is_initialized;
  }
  bool isSetup() const {
    return m_is_setup;
  }

 private:
  bool m_is_initialized;
  bool m_is_setup;
  bool m_window_resizable;
  ContextVersion m_context_version;
  Dimension2D m_window_size;
  string m_window_title;
  GLFWwindow* m_window;
};

#endif
