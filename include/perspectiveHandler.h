#ifndef __PERSPECTIVEHANDLER_H__
#define __PERSPECTIVEHANDLER_H__
#include "common.h"

#include "uniformObject.h"

class PerspectiveHandler : public UniformObject {
  glm::vec3 cameraLoc, cameraLookAt, up;
  glm::mat4 projection, view, model, MVP;
  PerspectiveHandler();
public:
  static PerspectiveHandler & getInstance() {
    static PerspectiveHandler instance; return instance;
  }
  void loadAttributes(GLuint programId);
};

#endif
