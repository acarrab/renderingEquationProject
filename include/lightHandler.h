#ifndef __LIGHTHANDLER_H__
#define __LIGHTHANDLER_H__
#include "common.h"

#include "uniformObject.h"

class LightHandler : public UniformObject {
  static constexpr float PI = 3.14159265;
  glm::vec3 position, direction;
  int current, iterations;
  LightHandler() :
    UniformObject(),
    position(dh->getXmlVec3("light/pos")),
    direction(dh->getXmlVec3("light/dir")),
    current(0),
    iterations(dh->getXmlInt("light/iterations"))
  {}
public:
  static LightHandler & getInstance() {
    static LightHandler instance; return instance;
  }
  void loadAttributes(GLuint programId);
  void next();
};

#endif
