#ifndef __WALL_H__
#define __WALL_H__
#include "common.h"

#include "objectHandler.h"
#include "genericObject.h"

/*
Teapot Dimensions:
  x: (-0.817742, 0.817739)
  y: (0.025154, 1.37592)
  z: (-1.46662, 1.28999)

*/
//4x4 wall

class Wall : public GenericObject {
  static int instance;
  static std::vector< std::string > types;
  int myInstance;
  std::string myType;
  BufferData buffer;
  glm::mat4 rtn;
  //should be 3
  glm::vec4 diffuseColor, specularColor;
  GLfloat shininess;
  std::vector<glm::vec3> wallCoords;
public:
  Wall();
  void loadAttributes(GLuint programId);
  void drawVerts();
};

#endif
