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
#include "perspectiveHandler.h"

class Teapot {
  ObjectHandler &oh;
  ShaderHandler &sh;
  LightHandler &lh;
  PerspectiveHandler &ph;
  std::vector<UniformHandler *> uniformList;

  const Draw_Data &data;
  glm::mat4 rtn;
  GLuint programId;
  GLuint rtnMtxId;
 public:
  Teapot(const std::string &programName) :
    oh(ObjectHandler::getInstance()),
    sh(ShaderHandler::getInstance()),
    lh(LightHandler::getInstance()),
    ph(PerspectiveHandler::getInstance()),
    uniformList({&lh, &ph}),//things that need to load their uniform
			    //data attributes.
    data(oh.getDataFor("teapot")),
    rtn(glm::rotate(45.0f, glm::vec3(0.0, 1.0, 0.0))),
    programId(sh.getProgramId(programName)),
    rtnMtxId(glGetUniformLocation(programId, "rotationMtx"))
  {}
  void draw();
};

#endif
