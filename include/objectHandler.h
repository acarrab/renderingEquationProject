#ifndef __OBJECTHANDLER_H__
#define __OBJECTHANDLER_H__
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include "data.h"
struct obj_data {
  std::vector< float >  v;
  std::vector< float >  vt;
  std::vector< float >  vn;
  std::vector< int >  f;
};

class ObjHandler {
  //flyweight
  static std::map<std::string, obj_data> objects;
public:
  static obj_data* getObjDataOf(std::string objectName);
};

#endif
