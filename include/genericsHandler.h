#ifndef __GENERICHANDLER_H__
#define __GENERICHANDLER_H__

#include "genericObject.h"
#include "teapot.h"
#include "wall.h"

class GenericsHandler{
  std::vector<GenericObject *> gens;
  GenericsHandler() {
    gens.push_back(new Teapot());
    for (int i = 0; i < 6; i++) gens.push_back(new Wall());
  }
public:
  static GenericsHandler& getInstance() { static GenericsHandler inst; return inst; }
  ~GenericsHandler() { for (auto thing : gens) delete thing; }
  std::vector<GenericObject *>::iterator begin() { return gens.begin(); }
  std::vector<GenericObject *>::iterator end() { return gens.end(); }
};

#endif
