#include "../include/perspectiveHandler.h"

PerspectiveHandler::PerspectiveHandler() :
  d(Data::getInstance()),
  cameraLoc(d.getXmlVec3("cam/pos")),
  cameraLookAt(d.getXmlVec3("cam/towards")),
  up(0, 1, 0),//should always be the same for my purposes
  projection(glm::perspective(d.getXmlFloat("perspective/fov"),
			      d.getXmlFloat("window/width")/
			      d.getXmlFloat("window/height"),
			      d.getXmlFloat("perspective/nearClip"),
			      d.getXmlFloat("perspective/farClip"))),
  view(glm::lookAt(cameraLoc, cameraLookAt, up)),
  model(glm::mat4(1.0f)),
  MVP(projection * view * model)
{}

void PerspectiveHandler::loadElements(GLuint programId) {
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
