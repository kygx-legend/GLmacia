#include "sampler.h"


const string kDebugTag = "[Sampler] ";

Sampler::Sampler()
  : id(-1) {
}

Sampler::Sampler(GLuint texture_unit)
  : unit(texture_unit) {
  glGenSamplers(1, &id);
}

Sampler::~Sampler() {
}

void Sampler::setParameteri(GLenum pname, GLint param) {
  glSamplerParameteri(id, pname, param);
}

void Sampler::setParameterf(GLenum pname, GLfloat param) {
  glSamplerParameterf(id, pname, param);
}
