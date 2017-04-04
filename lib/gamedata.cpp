#include <sstream>
#include <iostream>
#include <limits>
#include <cmath>
#include "../include/gamedata.h"

Gamedata& Gamedata::getInstance() {
  static Gamedata gamedata;
  return gamedata;
}

Gamedata::~Gamedata( ) { }

Gamedata::Gamedata(const std::string& fn ) :
  parser(fn),
  gameData(parser.getXmlData())
{ }

float Gamedata::getRandInRange(int min, int max) const {
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

float Gamedata::getRandFloat(float min, float max) const {
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}

bool  Gamedata::checkTag(const std::string& tag)const{
  return gameData.count(tag)!=0;
}

bool Gamedata::getXmlBool(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw std::string("Game: Didn't find boolean tag ")+tag+std::string(" in xml");
  else {
    if ( ptr->second == "true" ) return true;
    else return false;
  }
}

int Gamedata::getXmlInt(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw std::string("Game: Didn't find integer tag ")+tag+std::string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float Gamedata::getXmlFloat(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw std::string("Game: Didn't find float tag ")+tag+std::string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    float data;
    strm >> data;
    return data;
  }
}

const std::string& Gamedata::getXmlStr(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
  if ( ptr == gameData.end() )
    throw std::string("Game: Didn't find string tag ")+tag+std::string(" in xml");
  else return ptr->second;
}

void Gamedata::displayData() const {
  std::map<std::string, std::string>::const_iterator ptr = gameData.begin();
  while ( ptr != gameData.end() ) {
    std::cout << ptr->first << ", " << ptr->second << std::endl;
    ++ptr;
  }
}
