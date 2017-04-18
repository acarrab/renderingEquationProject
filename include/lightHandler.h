#ifndef __LIGHTHANDLER_H__
#define __LIGHTHANDLER_H__
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "data.h"

class LightHandler {
  glm::vec3 position;
  glm::vec3 direction;
  LightHandler() :
    position(glm::vec3(0,10,0)),
    direction(glm::vec3(0, -1, 0))
  {}
public:
  static LightHandler & getInstance() {
    static LightHandler instance; return instance;
  }
  glm::vec3 getPosition() const { return position; }
  glm::vec3 getDirection() const { return direction; }
};

#endif
