#include "../include/shader.h"

std::string Shader::readFile(const std::string &filePath) {
  std::string content;
  std::ifstream fin(filePath, std::ios::in);
  if(!fin.is_open()) throw "Failed to open file: " + filePath;
  std::string line = "";
  while(std::getline(fin, line))
    content.append(line + "\n");
  fin.close();
  return content;
}
bool Shader::compileShader(GLuint shader, std::string loc) {
  std::cerr << "Compiling: " << loc << std::endl;
  const GLchar *data = (const GLchar *)readFile(loc).c_str();
  glShaderSource(shader, 1, &(data), 0);
  glCompileShader(shader);
  GLint compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_FALSE) {
    GLint messageLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
    std::vector<GLchar> log(std::max(messageLength, 1));
    glGetShaderInfoLog(shader, messageLength, &messageLength, &log[0]);
    std::cerr << "|" << &log[0] << std::endl;
    return false;
  }
  return true;
}

Shader::Shader(const std::string &type) : dh(DataHandler::getInstance()), id(0) {
  std::string vertName, fragName, geomName;
  try { vertName = dh.getXmlStr(type + "/vert"); } catch(...) {}
  try { fragName = dh.getXmlStr(type + "/frag"); } catch(...) {}
  try { geomName = dh.getXmlStr(type + "/geom"); } catch(...) {}

  std::cout << "Compiling together { - ";
  if (vertName.size()) std::cout << "vert - ";
  if (fragName.size()) std::cout << "frag - ";
  if (geomName.size()) std::cout << "vert - ";
  std::cout << "}" << std::endl;

  GLuint vertShader, fragShader, geomShader;
  if (vertName.size()) {
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    if (!compileShader(vertShader, vertName)) {
      std::cerr << "Failed to compile vert... not good" << std::endl;
      throw -1;
    }
  }
  if (fragName.size()) {
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!compileShader(fragShader, fragName)) {
      std::cerr << "Failed to compile frag... not good" << std::endl;
      throw -2;
    }
  }
  if (geomName.size()) {
    geomShader = glCreateShader(GL_GEOMETRY_SHADER);
    if (!compileShader(geomShader, geomName)) {
      std::cerr << "Failed to compile geom... not good" << std::endl;
      throw -3;
    }
  }
  id = glCreateProgram();
  if (vertName.size()) glAttachShader(id, vertShader);
  if (fragName.size()) glAttachShader(id, fragShader);
  if (geomName.size()) glAttachShader(id, geomShader);

  glLinkProgram(id);


  //check the results
  GLint isLinked = 0;
  glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint messageLength = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &messageLength);
    std::vector<GLchar> log(std::max(messageLength, 1));
    glGetProgramInfoLog(id, messageLength, &messageLength, &log[0]);
    std::cerr << &log[0] << std::endl;
    throw -10;
  }

  if (vertName.size()) glDetachShader(id, vertShader);
  if (fragName.size()) glDetachShader(id, fragShader);
  if (geomName.size()) glDetachShader(id, geomShader);
}
