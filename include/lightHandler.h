#ifndef __LIGHTHANDLER_H__
#define __LIGHTHANDLER_H__
#include "common.h"

#include "data.h"
#include "uniformHandler.h"

class LightHandler : public UniformHandler {
  glm::vec3 position, direction;
  LightHandler() :
    position(glm::vec3(0,10,0)),
    direction(glm::vec3(0, -1, 0))
  {}
public:
  static LightHandler & getInstance() {
    static LightHandler instance; return instance;
  }
  void loadElements(GLuint programId);
  bool updateLights();
};

#endif
