#ifndef __PERSPECTIVEHANDLER_H__
#define __PERSPECTIVEHANDLER_H__
#include "common.h"

#include "data.h"
#include "uniformHandler.h"

class PerspectiveHandler : public UniformHandler {
  Data &d;
  glm::vec3 cameraLoc, cameraLookAt, up;
  glm::mat4 projection, view, model, MVP;
  PerspectiveHandler();
public:
  static PerspectiveHandler & getInstance() {
    static PerspectiveHandler instance; return instance;
  }
  void loadElements(GLuint programId);
};

#endif
