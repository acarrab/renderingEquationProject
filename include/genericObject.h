#ifndef __GENERICOBJECT_H__
#define __GENERICOBJECT_H__
#include "common.h"

#include "dataHandler.h"
#include "objectHandler.h"

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

class Intersects {
  static constexpr float precision = .0000001;
public:
  //result
  float units;
  Color color;

  //input
  glm::vec3 d, o; // ray direction, ray origin
  Intersects(const glm::vec3 &rp, const glm::vec3 &rd) :
    units(10000000.0), color(), d(rd), o(rp)
  {}
  void withTri(const glm::vec3 *v, const glm::vec3 &N, const Color &color);
  void with(const std::vector<glm::vec3> &verts,
	    const std::vector<glm::vec3> &norms,
	    const Color &realColor) {
    //find intersections
    for (unsigned int i = 0; i < verts.size(); i += 3)
      withTri(&verts[i], norms[i/3], realColor);
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
  //inline because only called in one particular place, gets rid of overhead
public:
  virtual ~GenericObject() {}
  virtual void loadAttributes(GLuint programId) {
    color.loadAttributes(programId);
  }
  virtual bool quickIntersectionTest(Intersects &intersect) const { return true; }
  void getIntersects(Intersects &intersect) const {
    if (quickIntersectionTest(intersect)) {
      float t = intersect.units;
      intersect.with(buffer.verts, buffer.norms, color);
      if (intersect.units <  20000)
	std::cout << "HIT" << std::endl;
    }
  }

  virtual void drawVerts() = 0;
};



#endif
