#ifndef __WINDATA_H__
#define __WINDATA_H__
#include <string>
#include <vector>
#include "../include/data.h"

class WinData {
public:
  int operator[](int i) const { return coords[i]; }
  std::string getTitle() const { return title; }
  int width() { return coords[2]; }
  int height() { return coords[3]; }
  static WinData & getInstance() {
    static WinData instance;
    return instance;
  }
private:
  WinData();
  Data &d;
  std::vector<int> coords; //x, y, width, height
  std::string title;
};

#endif
