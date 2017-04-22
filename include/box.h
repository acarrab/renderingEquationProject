#ifndef __BOX_H__
#define __BOX_H__
#include "common.h"

#include "data.h"
#include "lightHandler.h"
#include "perspectiveHandler.h"
#include "objectHandler.h"
#include "genericObject.h"

/*
Teapot Dimensions:
  x: (-0.817742, 0.817739)
  y: (0.025154, 1.37592)
  z: (-1.46662, 1.28999)

*/
//4x4 box

class Box : public GenericObject {
  static glm::vec3 corners[8];//using a bit vector 7 = 111
  static BufferData buffer;
  GLuint rtnMtxId, diffuseId, specularId, shineId;
  glm::mat4 rtn;
  //should be 3
  std::vector<glm::vec4> diffuseColor, specularColor;
  std::vector<GLfloat> shininess;
public:
  Box(const std::string &programName);
  void display();
};

#endif
