#ifndef __OBJECTHANDLER_H__
#define __OBJECTHANDLER_H__
#include "common.h"

#include <map>

#include "data.h"

struct ReadData {
  std::vector< std::vector<float> > v, vt, vn, vx, vy;
  std::vector< std::vector< std::vector<int> > > f;
};

class ObjectHandler {
  //flyweight - so we don't re-read stuff
  std::map<std::string, ReadData> objects;
  //gets data from file and stores it in map
  void loadDataFromFile(const std::string &objectName);
  //handles flyweight stuff
  const ReadData& generate(const std::string &objectName);
public:
  //make it a singleton
  static ObjectHandler& getInstance() {
    static ObjectHandler instance; return instance;
  }
  //get data
  const ReadData& getDataFor(const std::string &name) {
    return generate(name);
  }
};

#endif
