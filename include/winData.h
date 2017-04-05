#ifndef __WINDATA_H__
#define __WINDATA_H__
#include <string>
#include <vector>
#include "../include/data.h"

class WinData {
public:
  WinData();
  int operator[](int i) const { return coords[i]; }
  std::string getTitle() const { return title; }
private:
  Data &d;
  std::vector<int> coords;
  std::string title;
};

#endif
