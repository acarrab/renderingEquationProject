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
#include "shaderHandler.h"
struct VBO_Data {
  GLuint id; //should be freed+++++++++++++
  GLuint attribNum;
  GLuint vecSize;
  GLuint dataType; //i.e. GL_FLOAT
  GLuint normalized; //i.e. GL_FALSE
  GLuint stride; //0 means tightly packed
  void * address; //probably 0
  VBO_Data(GLuint id, GLuint atrNum, GLuint vecSize):
    id(id),
    attribNum(atrNum),
    vecSize(vecSize),
    dataType(GL_FLOAT),  //  <-|
    normalized(GL_FALSE),//  <-+- things that are in common
    stride(0),           //  <-|
    address((void *)0)   //  <-|
  {}
};

class Draw_Data {
  std::string shaderType;
  std::vector< VBO_Data > attributes;
  GLuint vertexType;
  GLuint vertexCount;
public:
  //getters
  const std::string & getShader() const { return shaderType; }
  const VBO_Data & operator[](unsigned int i) const { return attributes[i]; }
  const std::vector<VBO_Data> & getAttribs() const { return attributes; }
  GLuint getVertexType() const { return vertexType; }
  GLuint getVertexCount() const { return vertexCount; }
  unsigned int size() const { return attributes.size(); }
  //setters
  void push_back(VBO_Data data) { attributes.push_back(data); }
  void setVertexType(GLuint type) { vertexType = type; }
  void setVertexCount(GLuint count) { vertexCount = count; }
  void setShader(std::string shaderName) { shaderType = shaderName; }
};

struct read_data {
  std::vector< std::vector<float> > v, vt, vn, vx, vy;
  std::vector< std::vector< std::vector<int> > > f;
};

class ObjectHandler {
  //flyweight
  std::map<std::string, Draw_Data> objects;
  read_data* getDataFromFile(std::string fileName);
  const Draw_Data& generate(const std::string &objectName);
  Draw_Data const *currentObj;
public:
  //make it a singleton
  static ObjectHandler& getInstance() { static ObjectHandler instance; return instance; }

  void attributeLoad(const std::string &objectName);
  void attributeDraw();
  void attributeClear();
};

#endif
