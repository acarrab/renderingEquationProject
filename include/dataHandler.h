#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__
#include "common.h"
#include "parseXML.h"

class DataHandler {
public:
  static DataHandler& getInstance();
  ~DataHandler();
  void displayData() const;

  bool getXmlBool(const std::string&) const;
  std::string getXmlStr(const std::string&) const;
  float getXmlFloat(const std::string&) const;
  int getXmlInt(const std::string&) const;
  float getRandInRange(int min, int max) const;
  float getRandFloat(float min, float max) const;
  bool  checkTag(const std::string&)const;

  glm::vec4 getXmlVec4(const std::string&)const;
  glm::vec3 getXmlVec3(const std::string&)const;

private:
  ParseXML parser;
  const std::map<std::string, std::string> savedData;

  DataHandler(const std::string& fn = "settings.xml");
  DataHandler(const DataHandler&);
  DataHandler& operator=(const DataHandler&);
};
#endif
