#ifndef __OBJECTHANDLER_H__
#define __OBJECTHANDLER_H__
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "data.h"
struct obj_data {
  GLfloat *data; //v is index 0
  int normalIndex;  //vn
  int tangentIndex; //vx,vy
  int textureIndex; //vt
};
struct read_data {
  std::vector< float >  v;
  std::vector< float >  vt;
  std::vector< float >  vn;
  std::vector< float >  vx, vy; //tangents per vertex
  std::vector< std::vector<int> >  f;
};
class ObjHandler {
  //flyweight
  static std::map<std::string, obj_data> objects;
  static read_data getDataFromFile(std::string fileName);
public:
  static obj_data* getObjDataOf(std::string objectName);
  static void cleanMemory() {
    for (auto s_od : objects) delete[] s_od.second.data;
    objects.clear();
  }
};

#endif
