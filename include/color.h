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
    glUniform4f(id, Ka.r, Ka.g, Ka.b, 0.0);

    id = glGetUniformLocation(programId, "Kd");
    glUniform4f(id, Kd.r, Kd.g, Kd.b, 1.0);

    id = glGetUniformLocation(programId, "Ks");
    glUniform4f(id, Ks.r, Ks.g, Ks.b, 1.0);

    id = glGetUniformLocation(programId, "Ns");
    glUniform1f(id, Ns);
  }
  Color& operator*=(Color & a) {
    Ka = Ka * a.Ka;
    Kd = Kd * a.Kd;
    Ks = Ks * a.Ks;
    Ns = Ns * a.Ns;
    return *this;
  }
  Color& operator*=(float f) {
    Ka *= f;
    Kd *= f;
    Ks *= f;
    Ns *= f;
    return *this;
  }
};
#endif
