#include "fw.h" 


const ContextVersion kContextVersionDefault = ContextVersion(3, 1);
const Dimension2D kWindowSizeDefault = Dimension2D(640, 480);
const string kDebugTag = "[GLFW] ";

static void sErrorCallback(int error, const char* description) {
  cout << kDebugTag << "Error: " << error << endl;
  cout << kDebugTag << "Description: " << string(description) << endl;
}

FW::FW()
  : m_is_initialized(false),
    m_is_setup(false),
    m_window_resizable(false),
    m_context_version(kContextVersionDefault),
    m_window_size(kWindowSizeDefault),
    m_window_title(""),
    m_window(NULL) {
}

FW::FW(string title)
  : m_is_initialized(false),
    m_is_setup(false),
    m_window_resizable(false),
    m_context_version(kContextVersionDefault),
    m_window_size(kWindowSizeDefault),
    m_window_title(title),
    m_window(NULL) {
}

void FW::setContextVersion(int major, int minor) {
  m_context_version = ContextVersion(major, minor);
}

void FW::setWindowSize(int width, int height) {
  m_window_size = Dimension2D(width, height);
}

void FW::setWindowResizable(bool resizable) {
  m_window_resizable = resizable;
}

void FW::setKeyCallback(KeyCallback callback) {
  if (!isSetup()) {
    cout << kDebugTag << "No valid window!" << endl;
    return;
  }
  glfwSetKeyCallback(m_window, callback);
}

void FW::setMouseCallback(MouseCallback callback) {
  if (!isSetup()) {
    cout << kDebugTag << "No valid window!" << endl;
    return;
  }
  glfwSetCursorPosCallback(m_window, callback);
}

void FW::setScrollCallback(ScrollCallback callback) {
  if (!isSetup()) {
    cout << kDebugTag << "No valid window!" << endl;
    return;
  }
  glfwSetScrollCallback(m_window, callback);
}


void FW::setup() {
  glfwSetErrorCallback(sErrorCallback);

  if (!glfwInit()) {
    cout << kDebugTag << "Failed to be initialized!" << endl;
    m_is_initialized = false;
    return;
  }
  m_is_initialized = true;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_context_version.major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_context_version.minor);
  glfwWindowHint(GLFW_RESIZABLE, m_window_resizable);

  m_window = glfwCreateWindow(m_window_size.width, m_window_size.height,
                              m_window_title.c_str(), NULL, NULL);
  if (!m_window) {
    cout << kDebugTag << "Can not create a window!" << endl;
    m_is_setup = false;
    return;
  }

  glfwMakeContextCurrent(m_window);

  GLenum error = glewInit();
  if (error != GLEW_OK) {
    cout << kDebugTag << "Failed to initialize glew!" << endl;
    m_is_setup = false;
    return;
  }

  m_is_setup = true;
}

void FW::runMainLoop(VoidFunction render) {
  if (!isInitialized() || !isSetup()) {
    cout << kDebugTag << "Can not run main loop!" << endl;
    return;
  }

  while (!glfwWindowShouldClose(m_window)) {
    glfwPollEvents();
    render();
    glfwSwapBuffers(m_window);
  }
}

FW::~FW() {
  tearDown();
}

void FW::tearDown() {
  if (!isInitialized())
    return;

  glfwTerminate();
}
