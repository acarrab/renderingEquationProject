#ifndef __TEAPOT_H__
#define __TEAPOT_H__
#include "common.h"

#include "objectHandler.h"
#include "genericObject.h"


class Teapot : public GenericObject {
 public:
  Teapot();
  void drawVerts();
};

#endif
