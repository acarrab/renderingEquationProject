#include "../include/genericObject.h"
DataHandler *GenericObject::dh = nullptr;
ObjectHandler *GenericObject::oh = nullptr;

GenericObject::GenericObject() : buffer(), color() {
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}
GenericObject::GenericObject(const std::string &type) : buffer(), color(type) {
  if (dh == nullptr) dh = &DataHandler::getInstance();
  if (oh == nullptr) oh = &ObjectHandler::getInstance();
}
