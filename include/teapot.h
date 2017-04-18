#ifndef __TEAPOT_H__
#define __TEAPOT_H__
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

#include <map>
#include "data.h"
#include "shaderHandler.h"
#include "objectHandler.h"
#include "lightHandler.h"

class Teapot {
  ObjectHandler &oh;
  ShaderHandler &sh;
  LightHandler &lh;
  PerspectiveHandler &ph;
  std::vector<UniformHandler *> uniformList;

  const Draw_Data &data;
  glm::mat4 mvp, rtn;
  GLuint programId;
  GLuint mvpMtxId, rtnMtxId, lightId;
 public:
  Teapot(const std::string &programName, glm::mat4 MVP) :
    oh(ObjectHandler::getInstance()),
    sh(ShaderHandler::getInstance()),
    lh(LightHandler::getInstance()),
    ph(PerspectiveHandler::getInstance()),
    uniformList({&lh, &ph}),//things that need to load their uniform
			    //data attributes.
    data(oh.getDataFor("teapot")),
    mvp(MVP),
    rtn(glm::rotate(45.0f, glm::vec3(0.0, 1.0, 0.0))),
    programId(sh.getProgramId(programName)),
    mvpMtxId(glGetUniformLocation(programId, "MVP")),
    rtnMtxId(glGetUniformLocation(programId, "Rotation")),
    lightId(glGetUniformLocation(programId, "lightPosition"))
  {

  }
  void draw();
};

#endif
