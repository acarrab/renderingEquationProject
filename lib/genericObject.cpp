#include "../include/genericObject.h"
DataHandler *GenericObject::dh = nullptr;
ObjectHandler *GenericObject::oh = nullptr;

GenericObject::GenericObject() : buffer(), color() {
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}
GenericObject::GenericObject(const std::string &type) : buffer(), color(type) {
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}

void Intersects::withTri(const glm::vec3 *v,
			 const glm::vec3 &N,
			 const Color &color) {
  static float epsilon = .000001;
  glm::vec3 e1 = v[1] - v[0];
  glm::vec3 e2 = v[2] - v[0];

  glm::vec3 h = glm::cross(d, e2);
  float a = glm::dot(e1, h);
  if (-epsilon < a && a < epsilon) return;

  float f = 1.0/a;
  glm::vec3 s = o - v[0];
  float u = f * glm::dot(s, h);
  if (u < 0.0 || 1.0 < u) return;

  glm::vec3 q = glm::cross(s, e1);
  float r = f * glm::dot(d, q);
  if (r < 0.0 || 1.0 < u + r) return;

  float t = f * glm::dot(e2, q);
  if (t > epsilon && t < this->units) {
    this->units = t;
    this->color = color;
  }
}
