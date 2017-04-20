#ifndef __UNIFORMHANDLER_H__
#define __UNIFORMHANDLER_H__
#include "common.h"

class UniformHandler {
protected:
  UniformHandler() {}
public:
  virtual void loadElements(GLuint programId) = 0;
};

#endif
