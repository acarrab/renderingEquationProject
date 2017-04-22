#ifndef __TEAPOT_H__
#define __TEAPOT_H__
#include "common.h"

#include "genericObject.h"
#include "objectHandler.h"

class Teapot : public GenericObject {
  static BufferData buffer;
  glm::mat4 rtn;
  glm::vec4 diffuseColor, specularColor;
  GLfloat shininess;
 public:
  Teapot();
  void loadAttributes(GLuint programId);
  void drawVerts();
};

#endif
