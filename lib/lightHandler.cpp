#include "../include/lightHandler.h"

//for debugging
std::ostream & operator<<(std::ostream& os, const glm::vec3 &test) {
  return os << "<" << test.x << ", " << test.y << ", " << test.z << ">";
}

void LightHandler::loadAttributes(GLuint programId) {
  GLuint tmp;
  tmp = glGetUniformLocation(programId, "lightPosition");
  glUniform3f(tmp, position.x, position.y, position.z);

  tmp = glGetUniformLocation(programId, "lightDirection");
  glUniform3f(tmp, direction.x, direction.y, direction.z);

  std::cout << direction << std::endl;
}

float phi(int b, int i) {
  float x = 0, f = 1.0/static_cast<float>(b);
  while (i) {
    x += f * static_cast<float>(i % b);
    i /= b;
    f *= 1.0/static_cast<float>(b);
  }
  return x;
}
void LightHandler::next() {
  current %= iterations;
  float az = 2 * PI * phi(2, current);
  float el = asin(phi(3, current));
  direction = glm::vec3(-sin(az) * cos(el), -abs(sin(el)), cos(az) * cos(el));
  current++;
}
