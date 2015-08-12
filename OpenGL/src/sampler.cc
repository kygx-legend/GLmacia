#include "sampler.h"


const string kDebugTag = "[Sampler] ";

Sampler::Sampler()
  : id(-1) {
}

Sampler::Sampler(GLuint texture_unit) {
  glGenSamplers(1, &id);
  glSamplerParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glSamplerParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glSamplerParameteri(id, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
  glBindSampler(texture_unit, id);
}

Sampler::~Sampler() {
}
