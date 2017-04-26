#ifndef __SHADER_H__
#define __SHADER_H__
#include "common.h"

#include <map>
#include "dataHandler.h"

class Shader {
  DataHandler &dh;
  std::string readFile(const std::string &filePath);
  bool compileShader(GLuint shader, std::string loc);
public:
  GLuint id;
  Shader(const std::string &type);
};

#endif
