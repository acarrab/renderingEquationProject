#include <sstream>
#include <iostream>
#include <limits>
#include <cmath>
#include "../include/dataHandler.h"

DataHandler& DataHandler::getInstance() {
  static DataHandler instance;
  return instance;
}

DataHandler::~DataHandler( ) { }

DataHandler::DataHandler(const std::string& fn ) :
  parser(fn),
  savedData(parser.getXmlData())
{ }

float DataHandler::getRandInRange(int min, int max) const {
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

float DataHandler::getRandFloat(float min, float max) const {
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}

bool  DataHandler::checkTag(const std::string& tag)const{
  return savedData.count(tag)!=0;
}

bool DataHandler::getXmlBool(const std::string& tag) const {
  auto ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find boolean tag ")+tag;
  else {
    if ( ptr->second == "true" ) return true;
    else return false;
  }
}

int DataHandler::getXmlInt(const std::string& tag) const {
  auto ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find integer tag ")+tag;
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float DataHandler::getXmlFloat(const std::string& tag) const {
  auto ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find float tag ")+tag;
  else {
    std::stringstream strm;
    strm << ptr->second;
    float data;
    strm >> data;
    return data;
  }
}
glm::vec4 DataHandler::getXmlVec4(const std::string& tag) const {
  auto ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find vec4 tag ")+tag;
  else {
    glm::vec4 result;
    std::string part;
    std::stringstream ss(ptr->second);
    for(int i = 0; std::getline(ss, part, ','); i++) {
      result[i] = stof(part);
    }
    return result;
  }
}
glm::vec3 DataHandler::getXmlVec3(const std::string& tag) const {
  auto ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find vec3 tag ")+tag;
  else {
    glm::vec3 result;
    std::string part;
    std::stringstream ss(ptr->second);
    for(int i = 0; std::getline(ss, part, ','); i++) {
      result[i] = stof(part);
    }
    return result;
  }
}


std::string DataHandler::getXmlStr(const std::string& tag) const {
  auto ptr = savedData.find(tag);
  if ( ptr == savedData.end() )
    throw std::string("Didn't find string tag ")+tag;
  else return ptr->second;
}

void DataHandler::displayData() const {
  auto ptr = savedData.begin();
  while ( ptr != savedData.end() ) {
    std::cerr << ptr->first << ", " << ptr->second << std::endl;
    ++ptr;
  }
}
