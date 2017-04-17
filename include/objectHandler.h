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
#include <cstdio>
#include <algorithm>
#include "data.h"
struct obj_data {
  std::vector<GLfloat> data; //v is index 0
  int normalIndex;  //vn
  int textureIndex; //vt
  int tangentIndexX; //vx
  int tangentIndexY; //vy
  int vertices;
  GLuint pointer;
};
struct read_data {
  std::vector< std::vector<float> > v, vt, vn, vx, vy;
  std::vector< std::vector< std::vector<int> > > f;
};
class ObjHandler {
  //flyweight
  std::map<std::string, obj_data> objects;
  read_data getDataFromFile(std::string fileName);
  std::vector<int> parseFace(std::string s);
  void triangularize(obj_data &od,
		     std::vector< std::vector< std::vector<int> > > &f,
		     std::vector< std::vector<GLfloat> > &v,
		     int index);
public:
  static ObjHandler& getInstance();
  obj_data* getObjDataOf(std::string objectName);
};

#endif
