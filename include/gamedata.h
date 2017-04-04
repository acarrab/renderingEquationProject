#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__
#include "common.h"
#include "parseXML.h"

class Gamedata {
public:
  static Gamedata& getInstance();
  static Gamedata& g() { return Gamedata::getInstance(); }
  ~Gamedata();
  void displayData() const;

  bool getXmlBool(const std::string&) const;
  const std::string& getXmlStr(const std::string&) const;
  float getXmlFloat(const std::string&) const;
  int getXmlInt(const std::string&) const;
  float getRandInRange(int min, int max) const;
  float getRandFloat(float min, float max) const;
  bool  checkTag(const std::string&)const;

private:
  ParseXML parser;
  const std::map<std::string, std::string> gameData;

  Gamedata(const std::string& fn = "xmlSpec/game.xml");
  Gamedata(const Gamedata&);
  Gamedata& operator=(const Gamedata&);
};
#endif
