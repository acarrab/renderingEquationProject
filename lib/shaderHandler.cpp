#include "../include/shaderHandler.h"

std::string ShaderHandler::readFile(const std::string &filePath) {
  std::string content;
  std::ifstream fin(filePath, std::ios::in);
  if(!fin.is_open()) throw "Failed to open file: " + filePath;
  std::string line = "";
  while(std::getline(fin, line))
    content.append(line + "\n");
  fin.close();
  return content;
}
bool ShaderHandler::compileMyShader(GLuint shader, std::string loc) {
  const GLchar *data = (const GLchar *)readFile(loc).c_str();
  glShaderSource(shader, 1, &(data), 0);
  GLint compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_FALSE) {
    GLint messageLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
    std::vector<GLchar> log(std::max(messageLength, 1));
    glGetShaderInfoLog(shader, messageLength, &messageLength, &log[0]);
    std::cout << &log[0] << std::endl;
    return false;
  }
  return true;
}
GLuint ShaderHandler::compileProgram(std::string vertLoc, std::string fragLoc) {
  std::cout << "Compiling " << vertLoc << " with " << fragLoc << std::endl;
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  if (compileMyShader(vertShader, vertLoc)) {
    glDeleteShader(vertShader);
    std::cerr << "Failed to compile vert... this is not good" << std::endl;
    throw "failed to compile shader";
  }
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (compileMyShader(fragShader, fragLoc)) {
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    std::cerr << "Failed to compile frag... this is not good" << std::endl;
    throw "failed to compile shader";
  }
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint messageLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &messageLength);
    std::vector<GLchar> log(std::max(messageLength, 1));
    glGetProgramInfoLog(program, messageLength, &messageLength, &log[0]);
    glDeleteProgram(program);
    glDeleteShader(fragShader);
    glDeleteShader(vertShader);
    std::cout << &log[0] << std::endl;
    throw "failed to link program";
  }
  glDetachShader(program, vertShader);
  glDetachShader(program, fragShader);
  return program;
}

GLuint ShaderHandler::getProgramId(const std::string &type) {
  if (!loadedPrograms.count(type)) {
    loadedPrograms[type] = compileProgram(dh.getXmlStr(type + "/vert"),
					  dh.getXmlStr(type + "/frag"));
  }
  return loadedPrograms[type];
}
