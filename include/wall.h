#ifndef __WALL_H__
#define __WALL_H__
#include "common.h"

#include "objectHandler.h"
class GenericObject;
#include "genericObject.h"


class Wall : public GenericObject {
  static int instance;
  static std::vector< std::string > types;
  std::string myType;
  std::vector<glm::vec3> wallCoords;
public:
  Wall();
  void drawVerts();
};

#endif
