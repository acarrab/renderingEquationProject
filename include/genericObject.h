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
      norms.push_back(glm::normalize(glm::cross(verts[i + 1] - verts[i], verts[i + 2] - verts[i])));
  }
};

class Intersects {
public:
  //result
  float t;
  Color color;
  //input
  glm::vec3 rd, rp; // ray direction, ray origin
  Intersects() : t(-1.0), color(), rd(), rp() {}
  void withTri(const glm::vec3 *v, const glm::vec3 &N, const Color &color) {
    float D = glm::dot(N, v[0]);
    float t2 = glm::dot(N, rd); //get the projection distance per unit
				//of light distance
    if (t2 < .000001) return;
    t2 = (glm::dot(N, rp) + D)/t2;//project light position onto normal
				  //then add the distance to that
				  //plane from that point. Then divide
				  //by the unit length on the vector
    if (t2 < 0) return; //its behind us

    glm::vec3 hp = rp + rd * t2; // this is where we actually
				 // intersect with the plane, hit
				 // point
    /*        *v3
	     /
	    /         *p
	   /
	   *v1______*v2
    cross(a, b)
    n = cross(e1, e2)
    dot(n, cross(e1, p))
    dot(n, cross(p, e2))
    dot(n, cross(v3 - v2, p))
    */
    //failures
    if (glm::dot(N, glm::cross(v[1] - v[0], hp - v[0])) < 0) return;
    if (glm::dot(N, glm::cross(hp - v[0], v[2] - v[0])) < 0) return;
    if (glm::dot(N, glm::cross(v[2] - v[1], hp - v[1])) < 0) return;

    if (this->t < .000001 || (t2 < this->t)) {
      this->t = t2;
      this->color = color;
    }
  }
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
  void getIntersects(Intersects &intersect) const {
    intersect.with(buffer.verts, buffer.norms, color);
  }

  virtual void drawVerts() = 0;
};



#endif
