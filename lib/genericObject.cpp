#include "../include/genericObject.h"
GenericObject::GenericObject(const std::string &programName) :
  oh(ObjectHandler::getInstance()),
  sh(ShaderHandler::getInstance()),
  //things that need to load their uniform data attributes.
  uniformList({&LightHandler::getInstance(), &PerspectiveHandler::getInstance()}),
  programId(sh.getProgramId(programName))
{}

void GenericObject::displayStart() {
  glUseProgram(programId);
  for (UniformHandler *uh : uniformList) uh->loadElements(programId);
}
void GenericObject::displayStop() {
  glUseProgram(0);
}
