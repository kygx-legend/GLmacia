#include "render_manager.h" 


RenderManager::RenderManager()
  : m_context_version(3, 0),
    m_display_mode(GLUT_SINGLE),
    m_window_size(500, 500),
    m_window_position(100, 100),
    m_window_title("") {
  program_manager = ProgramManager(5);
  buffer_manager = BufferManager(5);
}

RenderManager::RenderManager(string title)
  : m_context_version(3, 0),
    m_display_mode(GLUT_SINGLE),
    m_window_size(500, 500),
    m_window_position(100, 100),
    m_window_title(title) {
  program_manager = ProgramManager(5);
  buffer_manager = BufferManager(5);
}

RenderManager::~RenderManager() {
  tearDown();
}

void RenderManager::init(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitContextVersion(m_context_version.primary, m_context_version.secondary);
  glutInitDisplayMode(m_display_mode);
  glutInitWindowSize(m_window_size.x, m_window_size.y);
  glutInitWindowPosition(m_window_position.x, m_window_position.y);
  glutCreateWindow(m_window_title.c_str());
}

void RenderManager::setupProgram(int program, string vertex_path, string fragment_path) {
  program_manager.initProgram(program, vertex_path, fragment_path);
  program_manager.useProgram(program);
}

void RenderManager::setRenerderFunction(VoidFunction renderFunction) {
  glutDisplayFunc(renderFunction);
}

void RenderManager::setIdleFunction(VoidFunction idleFunction) {
  glutIdleFunc(idleFunction);
}

void RenderManager::runMainLoop() {
  glutMainLoop();
}

void RenderManager::tearDown() {
}
