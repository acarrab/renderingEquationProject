#include "../include/shaderHandler.h"

GLuint ShaderHandler::program = 0;

std::string ShaderHandler::readFile(std::string filePath) {
  std::string content;
  std::ifstream fileStream(filePath, std::ios::in);
  if(!fileStream.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
    return "";
  }
  std::string line = "";
  while(!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }
  fileStream.close();
  return content;
}

ShaderHandler::ShaderHandler() {
  Data &d = Data::getInstance();

  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders
  std::string vertShaderStr = readFile(d.getXmlStr("shader/vert"));
  std::string fragShaderStr = readFile(d.getXmlStr("shader/frag"));
  const char *vertShaderSrc = vertShaderStr.c_str();
  const char *fragShaderSrc = fragShaderStr.c_str();

  GLint result = GL_FALSE;
  int logLength;

  // Compile vertex shader
  std::cerr << "Compiling vertex shader." << std::endl;
  glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(vertShader);

  // Check vertex shader
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
  std::cerr << &vertShaderError[0] << std::endl;

  // Compile fragment shader
  std::cerr << "Compiling fragment shader." << std::endl;
  glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
  std::cerr << &fragShaderError[0] << std::endl;

  std::cerr << "Linking program" << std::endl;
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

  std::vector<char> programError( (logLength > 1) ? logLength : 1 );
  glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
  std::cerr << &programError[0] << std::endl;


  glDeleteShader(vertShader);
  glDeleteShader(fragShader);

  this->program = program;

  glUseProgram(program);
}
ShaderHandler& ShaderHandler::getInstance() {
  static ShaderHandler instance;
  return instance;
}
