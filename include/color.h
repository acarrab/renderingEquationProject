#ifndef __COLOR_H__
#define __COLOR_H__

#include "dataHandler.h"

struct Color {
  glm::vec3 Ka, Kd, Ks, Ke;
  float Ns;
  Color() :
    Ka(0.00, 0.00, 0.00),
    Kd(1.00, 0.80, 0.70),
    Ks(0.15, 0.15, 0.15),
    Ns(60.0)
  {}
  Color(const std::string &type) :
    Ka(DataHandler::getInstance().getXmlVec3(type + "/Ka")),
    Kd(DataHandler::getInstance().getXmlVec3(type + "/Kd")),
    Ks(DataHandler::getInstance().getXmlVec3(type + "/Ks")),
    Ns(DataHandler::getInstance().getXmlFloat(type + "/Ns"))
  {}
  void loadAttributes(GLuint programId) {
    GLuint id = glGetUniformLocation(programId, "Ka");
    glUniform3f(id, Ka.r, Ka.g, Ka.b);

    id = glGetUniformLocation(programId, "Kd");
    glUniform3f(id, Kd.r, Kd.g, Kd.b);

    id = glGetUniformLocation(programId, "Ks");
    glUniform3f(id, Ks.r, Ks.g, Ks.b);

    id = glGetUniformLocation(programId, "Ns");
    glUniform1f(id, Ns);
  }
};
#endif
