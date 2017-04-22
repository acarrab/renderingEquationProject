#ifndef __UNIFORMHANDLER_H__
#define __UNIFORMHANDLER_H__
#include "common.h"
#include "dataHandler.h"
class UniformObject {
protected:
  static DataHandler *dh;
  UniformObject();
public:
  virtual void loadAttributes(GLuint programId) = 0;
};

#endif
