#include "../include/lightHandler.h"

//for debugging
std::ostream & operator<<(std::ostream& os, const glm::vec3 &test) {
  return os << "<" << test.x << ", " << test.y << ", " << test.z << ">";
}

void LightHandler::loadElements(GLuint programId) {
  GLuint tmp;
  tmp = glGetUniformLocation(programId, "lightPosition");
  glUniform3f(tmp, position.x, position.y, position.z);

  tmp = glGetUniformLocation(programId, "lightDirection");
  glUniform3f(tmp, direction.x, direction.y, direction.z);
}

bool LightHandler::updateLights() {

}
