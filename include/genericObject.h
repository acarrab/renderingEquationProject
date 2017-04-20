#ifndef __GENERICOBJECT_H__
#define __GENERICOBJECT_H__
#include "common.h"

#include "data.h"
#include "shaderHandler.h"
#include "objectHandler.h"
#include "lightHandler.h"
#include "perspectiveHandler.h"

struct BufferData {
  bool instantiated;
  std::vector< GLfloat > data;
  GLuint id;
  GLuint vertCount;
  std::vector< void * > addresses;
  std::vector< GLuint > elements;
  BufferData() :
    instantiated(false), data(), id(),vertCount(0), addresses(), elements()
  {}
};

class GenericObject {
protected:
  //classes may need object handler
  ObjectHandler &oh;
private:
  //shader is controlled by base class
  ShaderHandler &sh;
  //list of uniformHandlers that is called to load uniform data to shaders
  std::vector<UniformHandler *> uniformList;
  //shader program id
  GLuint programId;
protected:
  GenericObject(const std::string &programName);
  //called by derived classes in order to load elements to program
  void displayStart();
  void displayStop();
public:
  //called in main, must be done in display loop
  virtual void display() = 0;
  GLuint getProgramId() const { return programId; }
};
#endif
