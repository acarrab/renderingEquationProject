#ifndef __LIGHTHANDLER_H__
#define __LIGHTHANDLER_H__
#include "common.h"

#include "uniformObject.h"
#include "genericsHandler.h"
#include "color.h"

class LightHandler : public UniformObject {
  static constexpr float PI = 3.14159265;
  glm::vec3 position, direction;
  int current, iterations, bounces;
  GenericsHandler &gh;
  Color color;

  LightHandler() :
    UniformObject(),
    position(dh->getXmlVec3("light/pos")),
    direction(dh->getXmlVec3("light/dir")),
    current(0),
    iterations(dh->getXmlInt("light/iterations")),
    bounces(2),
    gh(GenericsHandler::getInstance())
  {
    color.Ka = dh->getXmlVec3("light/La");
    color.Kd = dh->getXmlVec3("light/Ld");
    color.Ks = dh->getXmlVec3("light/Ls");
    color.Ns = 0.0;
  }
public:
  static LightHandler & getInstance() {
    static LightHandler instance; return instance;
  }
  void loadAttributes(GLuint programId);
  void next();
};

#endif
