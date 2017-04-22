#include "../include/genericObject.h"
DataHandler *GenericObject::dh = nullptr;
ObjectHandler *GenericObject::oh = nullptr;

GenericObject::GenericObject() {
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}
