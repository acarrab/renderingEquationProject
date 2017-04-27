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
//this has to be the same math as that in the shader
inline void LightHandler::attenuate(Light &l, Intersects &intersect) {
  //first attenuate basic diffuse
  //  l.color.Kd /= pow(intersect.units, 2);
  l.color  *= (intersect.color / intersect.units);
  //some things are shinier than others, like the floor
  //  if (intersect.typeId != 3 && intersect.typeId >= 2)
  //    l.color.Ks /= intersect.units;



}
void LightHandler::nextOnSphere(Light &l) {
  float az = phi(2, i) * 360;
  //lets make this thing shift downwards - later
  float el = asin(phi(3, i))*360;
  l(glm::vec3(0, 7.0, 2.0),//position should make this negative only
    glm::normalize(glm::vec3(-sin(az) * cos(el), -sin(el), cos(az) * cos(el))),
    lightColor);
  //incrementing i
  i++;
}

void LightHandler::nextBounce(Light &l, GenericsHandler &gh) {
  Intersects intersect(l.pos, l.dir);
  for (auto thing : gh) thing->getIntersects(intersect);
  if (intersect.units <  200) {
    //std::cout << intersect.color.Kd << " -> " << intersect.units << " -> ";
    attenuate(l, intersect);
    //std::cout << intersect.color.Kd << std::endl;

    l.pos = intersect.units  * .99f * l.dir + l.pos;
    intersect.normal = glm::normalize(intersect.normal);
    l.dir = glm::normalize(l.dir - 2 * (glm::dot(l.dir, intersect.normal))*intersect.normal);
  } else {
    std::cout << "what just happened?" << std::endl;
  }

}

void LightHandler::next(Light &l, GenericsHandler &gh) {
  if (!(beta % (bounces + 1))) nextOnSphere(l);
  else nextBounce(l, gh);
  beta  = (++beta) % (bounces + 1);
}
