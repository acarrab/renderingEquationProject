#ifndef __LIGHTHANDLER_H__
#define __LIGHTHANDLER_H__
#include "common.h"

#include "genericsHandler.h"
#include "color.h"

struct Light {
  glm::vec3 pos, dir;
  Color color;
  void operator()(const glm::vec3 &p, const glm::vec3 &d, const Color &c) {
    pos = p; dir = d; color = c;
  }
  Light() {}
  void loadAttributes(GLuint programId);
};
class LightHandler {
  static constexpr float PI = 3.14159265;
  DataHandler &dh;
  Color lightColor;
  int bounces, i, beta;
  float phi(int b, int i);
  void nextOnSphere(Light &l);
  void nextBounce(Light &l, GenericsHandler &gh);
  inline void attenuate(Light &l, Intersects &intersect);
public:
  LightHandler() : dh(DataHandler::getInstance()),
		   lightColor(),
		   bounces(dh.getXmlInt("light/bounces")),
		   i(0),
		   beta(0)
  {
    lightColor.Ka = dh.getXmlVec3("light/La");
    lightColor.Kd = dh.getXmlVec3("light/Ld");
    lightColor.Ks = dh.getXmlVec3("light/Ls");
    lightColor.Ns = 0.0;
  }
  void next(Light &l, GenericsHandler &gh);
};

#endif
