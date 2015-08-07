#include "ut.h"


const ContextVersion kContextVersionDefault = ContextVersion(3, 1);
const Dimension2D kWindowSizeDefault = Dimension2D(640, 480);
const string kDebugTag = "[GLUT] ";

UT::UT()
  : m_context_version(kContextVersionDefault),
    m_window_size(kWindowSizeDefault),
    m_window_title("") {
}

UT::UT(string title)
  : m_context_version(kContextVersionDefault),
    m_window_size(kWindowSizeDefault),
    m_window_title(title) {
}

UT::~UT() {
  tearDown();
}

void UT::setRenderFunction(VoidFunction renderFunction) {
  glutDisplayFunc(renderFunction);
}

void UT::setIdleFunction(VoidFunction idleFunction) {
  glutIdleFunc(idleFunction);
}

void UT::init(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitContextVersion(m_context_version.major, m_context_version.minor);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(m_window_size.width, m_window_size.height);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(m_window_title.c_str());

  GLenum error = glewInit();
  if (error != GLEW_OK)
    cout << kDebugTag << "Failed to initialize glew!" << endl;
}
void UT::runMainLoop() {
  glutMainLoop();
}

void UT::tearDown() {
}
