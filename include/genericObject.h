#ifndef __GENERICOBJECT_H__
#define __GENERICOBJECT_H__
#include "common.h"

#include "dataHandler.h"
#include "objectHandler.h"

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
  static DataHandler *dh;
  static ObjectHandler *oh;
  GenericObject();
public:
  virtual ~GenericObject() {}
  //we can do this on the gpu by using a depth buffer like with the shadow
  //uses depth buffer texture to generate shadow through shadow mapping
  //called in main, must be done in display loop
  virtual void loadAttributes(GLuint programId) = 0;
  virtual void drawVerts() = 0;
};
#endif
