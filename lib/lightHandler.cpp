#include "../include/lightHandler.h"
std::ostream & operator<<(std::ostream &os, const glm::vec3 &v) {
  return os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}

void Light::loadAttributes(GLuint programId) {
  GLuint id;
  id = glGetUniformLocation(programId, "lightPosition");
  glUniform3f(id, pos.x, pos.y, pos.z);

  id = glGetUniformLocation(programId, "lightDirection");
  glUniform3f(id, dir.x, dir.y, dir.z);

  //light color
  id = glGetUniformLocation(programId, "La");
  glUniform4f(id, color.Ka.r, color.Ka.g, color.Ka.b, 1.0);

  id = glGetUniformLocation(programId, "Ld");
  glUniform4f(id, color.Kd.r, color.Kd.g, color.Kd.b, 1.0);

  id = glGetUniformLocation(programId, "Ls");
  glUniform4f(id, color.Ks.r, color.Ks.g, color.Ks.b, 1.0);
}


float LightHandler::phi(int b, int i) {
  float x = 0.0, f = 1.0/static_cast<float>(b);
  while (i) {
    x += f * static_cast<float>(i % b);
    i /= b;
    f *= 1.0/static_cast<float>(b);
  }
  return x;
}
void LightHandler::nextOnSphere(Light &l, GLuint &programId) {
  GLuint lid = glGetUniformLocation(programId, "lightId");
  glUniform1i(lid, -1);
  float az = phi(2, i) * 2 * 3.14159265;//360;
  //lets make this thing shift downwards - later
  float el = asin(phi(3, i)) * 4.5;//3.14159265;

  l(glm::vec3(0, 7.0, 0.3) + .9f * glm::normalize(glm::vec3(-sin(az) * cos(el), -sin(el), cos(az) * cos(el))),//position should make this negative only
    glm::normalize(glm::vec3(-sin(az) * cos(el), -sin(el), cos(az) * cos(el))),
    lightColor);
  //incrementing i
  i++;
}

void LightHandler::nextBounce(Light &l, GenericsHandler &gh, GLuint &programId) {
  GLuint lid = glGetUniformLocation(programId, "lightId");
  Intersects intersect(l.pos, l.dir);

  for (auto thing : gh) thing->getIntersects(intersect);

  if (intersect.typeId != -1) {

    intersect.color *= 1.0/(pow(intersect.units, 1.4));
    l.color  *= intersect.color;

    glUniform1i(lid, intersect.typeId);

    l.pos = intersect.units  * .99f * l.dir + l.pos;

    intersect.normal = glm::normalize(intersect.normal);
    l.dir = glm::normalize(glm::reflect(l.dir, intersect.normal));
  } else {
    std::cout << "what just happened?" << std::endl;
  }
}

void LightHandler::next(Light &l, GenericsHandler &gh, GLuint &programId) {
  if (!(beta % (bounces + 1))) nextOnSphere(l, programId);
  else nextBounce(l, gh, programId);
  beta  = (++beta) % (bounces + 1);
}
