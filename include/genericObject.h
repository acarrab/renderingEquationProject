#ifndef __GENERICOBJECT_H__
#define __GENERICOBJECT_H__
#include "common.h"

#include "dataHandler.h"
#include "objectHandler.h"
#include "intersects.h"
#include "color.h"


struct BufferData {
  std::vector< GLfloat > data;
  std::vector< glm::vec3 > verts;
  std::vector< glm::vec3 > norms; // 1 normal per vertex
  GLuint id;
  GLuint vertCount;
  std::vector< void * > addresses;
  std::vector< GLuint > elements;
  BufferData() : data(), id(),vertCount(0), addresses(), elements() {}
  void process() {
    for (GLuint i = 0; i < vertCount; i++)
      verts.push_back(glm::vec3(data[i*3], data[i*3 + 1], data[i*3 + 2]));
    // for each triangle find the normal
    for (GLuint i = 0; i < vertCount; i += 3)
      norms.push_back(glm::normalize(glm::cross(verts[i + 1] - verts[i],
						verts[i + 2] - verts[i])));
  }
};

class GenericObject {
protected:
  static DataHandler *dh;
  static ObjectHandler *oh;
  GenericObject();
  GenericObject(const std::string &type);
  BufferData buffer;
  Color color;
  /*
    | TYPE | Teapot | w_left | w_right | w_back | w_floor | w_ceil | w_front |
    |------+--------+--------+---------+--------+---------+--------+---------|
    | ID   |     10 |      0 |       1 |      2 |       3 |      4 |       5 |

  */
  int myTypeId;
  //inline because only called in one particular place, gets rid of overhead
public:
  virtual ~GenericObject() {}
  void loadAttributes(GLuint programId);
  void getIntersects(Intersects &intersect) const;
  virtual void drawVerts() = 0;
};



#endif
