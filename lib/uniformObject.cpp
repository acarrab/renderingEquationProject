#include "../include/uniformObject.h"

DataHandler *UniformObject::dh = nullptr;
UniformObject::UniformObject() {
  if (!dh) dh = &DataHandler::getInstance();
}
