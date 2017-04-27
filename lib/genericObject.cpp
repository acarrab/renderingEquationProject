#include "../include/genericObject.h"
DataHandler *GenericObject::dh = nullptr;
ObjectHandler *GenericObject::oh = nullptr;


GenericObject::GenericObject() :
  buffer(), color(), myTypeId(10)
{
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}

GenericObject::GenericObject(const std::string &type) :
  buffer(), color(type), myTypeId(10)
{
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}

void GenericObject::loadAttributes(GLuint programId) {
  color.loadAttributes(programId);
  //add my type to the shader
  GLuint id = glGetUniformLocation(programId, "myTypeId");
  glUniform1i(id, myTypeId);
}

void GenericObject::getIntersects(Intersects &intersect) const {
  //skipping teapot
  if (myTypeId == 10) return;
  intersect.with(buffer.verts, buffer.norms, color, myTypeId);
}
