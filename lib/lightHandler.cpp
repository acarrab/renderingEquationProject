#include "../include/lightHandler.h"

//for debugging
std::ostream & operator<<(std::ostream& os, const glm::vec3 &test) {
  return os << "<" << test.x << ", " << test.y << ", " << test.z << ">";
}

void LightHandler::loadAttributes(GLuint programId) {
  GLuint id;
  id = glGetUniformLocation(programId, "lightPosition");
  glUniform3f(id, position.x, position.y, position.z);

  id = glGetUniformLocation(programId, "lightDirection");
  glUniform3f(id, direction.x, direction.y, direction.z);

  //light color
  id = glGetUniformLocation(programId, "La");
  glUniform3f(id, color.Ka.r, color.Ka.g, color.Ka.b);

  id = glGetUniformLocation(programId, "Ld");
  glUniform3f(id, color.Kd.r, color.Kd.g, color.Kd.b);

  id = glGetUniformLocation(programId, "Ls");
  glUniform3f(id, color.Ks.r, color.Ks.g, color.Ks.b);
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
  static int i = 0;
  if (!(i % (bounces + 1))) {
    current %= iterations;
    float az = 2 * PI * phi(2, current);
    float el = asin(phi(3, current));
    direction = glm::vec3(-sin(az) * cos(el), sin(el), cos(az) * cos(el));
    current++;
    i = 1;
  } else {
    Intersects intersect;
    for (auto thing : gh) thing->getIntersects(intersect);
    if (intersect.t < 0) {
      std::cerr << "there should be an intersection..." << std::endl;
      i = 0;
    }
  }
  i++;
}
