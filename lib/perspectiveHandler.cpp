#include "../include/perspectiveHandler.h"

PerspectiveHandler::PerspectiveHandler() :
  cameraLoc(dh->getXmlVec3("cam/pos")),
  cameraLookAt(dh->getXmlVec3("cam/towards")),
  up(0, 1, 0),//should always be the same for my purposes
  projection(glm::perspective(dh->getXmlFloat("perspective/fov"),
			      dh->getXmlFloat("window/width")/
			      dh->getXmlFloat("window/height"),
			      dh->getXmlFloat("perspective/nearClip"),
			      dh->getXmlFloat("perspective/farClip"))),
  view(glm::lookAt(cameraLoc, cameraLookAt, up)),
  model(glm::mat4(1.0f)),
  MVP(projection * view * model)
{}

void PerspectiveHandler::loadAttributes(GLuint programId) {
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
