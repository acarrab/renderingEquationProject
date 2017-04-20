#ifndef __TEAPOT_H__
#define __TEAPOT_H__
#include "common.h"

#include "data.h"
#include "lightHandler.h"
#include "perspectiveHandler.h"
#include "objectHandler.h"
#include "genericObject.h"
class Teapot : public GenericObject {
  static BufferData buffer;
  GLuint rtnMtxId, diffuseId, specularId, shineId;
  glm::mat4 rtn;
  glm::vec4 diffuseColor, specularColor;
  GLfloat shininess;
 public:
  Teapot(const std::string &programName);
  void display();
};

#endif
