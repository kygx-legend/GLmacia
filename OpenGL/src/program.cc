#include "program.h"

#include "base/util.h"


const int kLogCharSize = 512;
const string kDebugTag = "[Program] ";

Program::Program()
  : m_is_setup(false),
    id(-1) {
}

Program::~Program() {
}

bool Program::loadShader(GLenum type, string content) {
  Shader shader(type, content);
  if (!shader.load())
    return false;
  shaders.push_back(shader);
  return true;
}

bool Program::loadShaderFromFile(string file) {
  GLenum type;
  if (file.find(kVertexSuffix) != string::npos) {
    type = GL_VERTEX_SHADER;
  } else if (file.find(kFragmentSuffix) != string::npos) {
    type = GL_FRAGMENT_SHADER;
  } else {
    cout << kDebugTag << "Invalid suffix of shader file: " << file << endl;
  }

  string content;
  if (!ReadShaderFile(content, kShaderPath + "/" + file))
    return false;
  return loadShader(type, content);
}

bool Program::setup() {
  if (shaders.empty()) {
    cout << kDebugTag << "No shaders in program!" << endl;
    return false;
  }

  id = glCreateProgram();

  for (int i = 0; i < shaders.size(); ++i)
    glAttachShader(id, shaders[i].id);
  glLinkProgram(id);

  GLint is_successful;
  glGetProgramiv(id, GL_LINK_STATUS, &is_successful);
  if (!is_successful) {
    GLchar error[kLogCharSize];
    glGetProgramInfoLog(id, kLogCharSize, NULL, error);
    cout << kDebugTag << "Link error:" << endl;
    cout << kDebugTag << string(error) << endl;
    return false;
  }

  m_is_setup = true;
  return true;
}

bool Program::use() {
  if (!m_is_setup) {
    cout << kDebugTag << "Program is not set up!" << endl;
    return false;
  }
  glUseProgram(id);
  return true;
}
