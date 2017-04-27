#ifndef __INTERSECTS_H__
#define __INTERSECTS_H__
#include "common.h"
#include "color.h"

class Intersects {
  static constexpr float precision = .0000001;
  //this should never be called by anyone else
  void withTri(const glm::vec3 *v,
	       const glm::vec3 &N);
  int tmpType;
  glm::vec3 d, o; // ray direction, ray origin
public:
  //result
  float units;
  Color color;
  glm::vec3 normal;
  int typeId;
  //input
  Intersects(const glm::vec3 &rp, const glm::vec3 &rd) :
    tmpType(-1), d(glm::normalize(rd)), o(rp),
    units(10000000.0), color(), normal(), typeId(-1)
  {}


  void with(const std::vector<glm::vec3> &verts,
	    const std::vector<glm::vec3> &norms,
	    const Color &realColor,
	    int type) {
    tmpType = type;
    //find intersections
    for (unsigned int i = 0; i < verts.size(); i += 3)
      withTri(&verts[i], norms[i/3]);
    if (typeId == type) { // there was a hit with this thing
      color = realColor;
    }
  }
};

#endif
