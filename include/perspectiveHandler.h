#ifndef __PERSPECTIVEHANDLER_H__
#define __PERSPECTIVEHANDLER_H__
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
#include "uniformHandler.h"

class PerspectiveHandler : public UniformHandler {
  Data &d;
  glm::vec3 cameraLoc, cameraLookAt, up;
  glm::mat4 projection, view, model, MVP;
  LightHandler() :
    d(Data::getInstance()),
    cameraLoc(0, 4, -3),
    cameraLookAt(0, 0, 0),
    up(0, 1, 0),
    projection(glm::perspective(45.0f,
				d.getXmlFloat("window/width")/
				d.getXmlFloat("window/height"),
				.1f,
				100.0f)),
    view(glm::lookAt(cameraLoc, cameraLookAt, up)),
    model(glm::mat4(1.0f)),
    MVP(projection * view * model)
  {}
public:
  static PerspectiveHandler & getInstance() {
    static PerspectiveHandler instance; return instance;
  }
  void loadElements(GLuint programId) {
    GLuint tmp;
    tmp = glGetUniformLocation(programId, "cameraPosition");
    glUniform3f(tmp, cameraLoc.x, cameraLoc.y, cameraLoc.z);

    tmp = glGetUniformLocation(programId, "cameraLookAt");
    glUniform3f(tmp, cameraLookAt.x, cameraLookAt.y, cameraLookAt.z);

    tmp = glGetUniformLocation(programId, "projectionMtx");
    glUniformMatrix4fv(tmp, 1, GL_FALSE, &projection[0][0]);

    tmp = glGetUniformLocation(programId, "viewMtx");
    glUniformMatrix4fv(tmp, 1, GL_FALSE, &view[0][0]);

    tmp = glGetUniformLocation(programId, "modelMtx");
    glUniformMatrix4fv(tmp, 1, GL_FALSE, &model[0][0]);

    tmp = glGetUniformLocation(programId, "mvpMtx");
    glUniformMatrix4fv(tmp, 1, GL_FALSE, &MVP[0][0]);
  }

};

#endif
