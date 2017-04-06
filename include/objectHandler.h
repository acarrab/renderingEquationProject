#ifndef __OBJECTHANDLER_H__
#define __OBJECTHANDLER_H__
#include "data.h"
struct obj_data {
  std::vector< glm::vec3 >  v;
  std::vector< glm::vec2 >  vt;
  std::vector< glm::vec3 >  vn;
  std::vector< glm::vec3 >  f;
};

class ObjHandler {
  //flyweight
  static std::map<std::string, obj_data> objects;
  static *obj_data getObjDataOf(std::string s) {
    if (objects.find(s)) return objects.find(s)->second;
    try std::string fileName = Data::g().getXmlStr(s + "/fileName");
    catch (...) {
      std::cerr << "Failed to find" << s << "/fileName" << std::endl;
      return nullptr;
    }
    obj_data d;
  }
};

#endif
