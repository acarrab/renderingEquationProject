#include <sstream>
#include <iostream>
#include <limits>
#include <cmath>
#include "../include/data.h"

Data& Data::getInstance() {
  static Data instance;
  return instance;
}

Data::~Data( ) { }

Data::Data(const std::string& fn ) :
  parser(fn),
  savedData(parser.getXmlData())
{ }

float Data::getRandInRange(int min, int max) const {
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

float Data::getRandFloat(float min, float max) const {
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}

bool  Data::checkTag(const std::string& tag)const{
  return savedData.count(tag)!=0;
}

bool Data::getXmlBool(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find boolean tag ")+tag+std::string(" in xml");
  else {
    if ( ptr->second == "true" ) return true;
    else return false;
  }
}

int Data::getXmlInt(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find integer tag ")+tag+std::string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float Data::getXmlFloat(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find float tag ")+tag+std::string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    float data;
    strm >> data;
    return data;
  }
}

const std::string& Data::getXmlStr(const std::string& tag) const {
  std::map<std::string, std::string>::const_iterator ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find string tag ")+tag+std::string(" in xml");
  else return ptr->second;
}

void Data::displayData() const {
  std::map<std::string, std::string>::const_iterator ptr = savedData.begin();
  while ( ptr != savedData.end() ) {
    std::cerr << ptr->first << ", " << ptr->second << std::endl;
    ++ptr;
  }
}
