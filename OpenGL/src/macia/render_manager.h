#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <string>

#include <GL/freeglut.h>

#include "structure.h"
#include "program_manager.h"
#include "buffer_manager.h"
#include "texture_manager.h"

using namespace std;

class RenderManager {
 public:
  explicit RenderManager();
  explicit RenderManager(string);
  virtual ~RenderManager();

  void init(int, char**);
  void setupProgram(int, string, string);
  void setRenerderFunction(VoidFunction);
  void setIdleFunction(VoidFunction); 
  void runMainLoop();
  void tearDown();

  ProgramManager program_manager;
  BufferManager buffer_manager;
  TextureManager texture_manager;

 private:
  ContextVersion m_context_version;
  GLenum m_display_mode;
  TupleInt2D m_window_size;
  TupleInt2D m_window_position;
  string m_window_title;
};

#endif
