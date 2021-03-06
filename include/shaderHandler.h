#ifndef __SHADERHANDLER_H__
#define __SHADERHANDLER_H__
#include "common.h"

#include <map>
#include "dataHandler.h"
class ShaderHandler {
  DataHandler &dh;
  //reads the file
  std::string readFile(const std::string &filePath);
  //singleton
  std::map<std::string, GLuint> loadedPrograms;
  ShaderHandler() : dh(DataHandler::getInstance()), loadedPrograms() {};
  bool compileMyShader(GLuint shader, std::string loc);
  GLuint compileProgram(std::string vert, std::string frag);
public:
  static ShaderHandler& getInstance() {
    static ShaderHandler instance; return instance;
  }
  //probably dont use
  GLuint getProgramId(const std::string &type);
};


#endif
