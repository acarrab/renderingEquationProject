#include "../include/lightHandler.h"


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

void LightHandler::nextOnSphere(Light &l) {
  float az = 2.0 * PI * phi(2, i);
  float el = asin(phi(3, i/(bounces + 1)));
  std::cerr << i << ", " << az << ", " << el << std::endl;

  //hardcoding
  l(glm::vec3(0, 7.9, 0),//position
    glm::vec3(-sin(az) * cos(el), sin(el), cos(az) * cos(el)),//should make this negative only
    lightColor);
  //incrementing i
  i++;
}

void LightHandler::nextBounce(Light &l, GenericsHandler &gh) {
  Intersects intersect;
  intersect.rp = l.pos;
  intersect.rd = l.dir;
  for (auto thing : gh) thing->getIntersects(intersect);
  if (intersect.t < 0) {
    i += ((bounces + 1) - i % (bounces + 1) - 1);
    //std::cerr << (i + 1) %(bounces + 1) << std::endl;
  }
}

void LightHandler::next(Light &l, GenericsHandler &gh) {
  static int beta = 0;

  if (!(beta % (bounces + 1))) nextOnSphere(l);
  else nextBounce(l, gh);

  beta  = (++beta) % (bounces + 1);
}
