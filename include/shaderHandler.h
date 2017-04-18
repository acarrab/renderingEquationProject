#ifndef __SHADERHANDLER_H__
#define __SHADERHANDLER_H__
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
#include <fstream>
#include "data.h"

class ShaderHandler {
  std::string readFile(std::string filePath);
  std::map<std::string, GLuint> loadedPrograms;
  ShaderHandler() {};
  GLuint compileProgram(std::string vert, std::string frag);
public:
  void useProgram(const std::string &type);
  GLuint getProgramId(const std::string &type);
  static ShaderHandler& getInstance();
};


#endif
