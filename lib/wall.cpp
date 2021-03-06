#include "../include/wall.h"
int Wall::instance = 0;
std::vector< std::string > Wall::types({
    std::string("left"), std::string("right"), std::string("back"),
      std::string("floor"), std::string("ceil"), std::string("front")});

//pushes back vert
std::vector<GLfloat> & operator<<(std::vector<GLfloat> &out,
				  const glm::vec3 &vec) {
  out.push_back(vec.x);
  out.push_back(vec.y);
  out.push_back(vec.z);
  return out;
}

std::vector<glm::vec3> & operator<<(std::vector<glm::vec3> &out,
				  const glm::vec3 &vec) {
  out.push_back(vec);
  return out;
}

Wall::Wall() :
  GenericObject("box/" + types[std::min((int)types.size() - 1, instance)]),
  myType("box/" + types[std::min((int)types.size() - 1, instance)]),
  wallCoords()
{
  myTypeId = instance;
  float w = dh->getXmlFloat("box/width");
  glm::vec3 normal;
  if (instance == 0) {
    //left wall
    wallCoords << glm::vec3(-w/2, 0, -w/2) << glm::vec3(-w/2, w, -w/2)
	       << glm::vec3(-w/2, w, w/2) << glm::vec3(-w/2, 0, w/2);
    normal = glm::vec3(1.0, 0.0, 0.0);

  } else if (instance == 1) {
    //right wall
    wallCoords << glm::vec3(w/2, 0, -w/2) << glm::vec3(w/2, 0, w/2)
	       << glm::vec3(w/2, w, w/2) << glm::vec3(w/2, w, -w/2);
    normal = glm::vec3(-1.0, 0.0, 0.0);
  } else {
    if (instance == 2) {//back
      wallCoords << glm::vec3(-w/2, 0, -w/2) << glm::vec3(w/2, 0, -w/2)
		 << glm::vec3(w/2, w, -w/2) << glm::vec3(-w/2, w, -w/2);
      normal = glm::vec3(0.0, 0.0, 1.0);
    } else if (instance == 3) { //floor
      wallCoords << glm::vec3(-w/2, 0, -w/2) << glm::vec3(w/2, 0, -w/2)
		 << glm::vec3(w/2, 0, w/2) << glm::vec3(-w/2, 0, w/2);
      normal = glm::vec3(0.0, 1.0, 0.0);
    } else if (instance == 4) { //ceiling
      wallCoords << glm::vec3(-w/2, w, -w/2) << glm::vec3(w/2, w, -w/2)
		 << glm::vec3(w/2, w, w/2) << glm::vec3(-w/2, w, w/2);
      normal = glm::vec3(0.0, -1.0, 0.0);
    } else if (instance == 5) { //close
      wallCoords << glm::vec3(-w/2, 0, w/2) << glm::vec3(w/2, 0, w/2)
		 << glm::vec3(w/2, w, w/2) << glm::vec3(-w/2, w, w/2);
      normal = glm::vec3(0.0, 0.0, -1.0);
    } else {
      throw std::string("There aren't that many walls");
    }

  }
  //displace them
  static GLfloat center = dh->getXmlFloat("box/displace");
  for (glm::vec3 &coord : wallCoords) coord += glm::vec3(0, 0, center);
  static int divs = dh->getXmlInt("box/rowColNum");

  if (myTypeId != 5) {
    buffer.vertCount = divs*divs*2*3;
    buffer.addresses.push_back((void *)0);
    buffer.elements.push_back(3);
    for (int x = 0; x < divs; x++) {
      for (int y = 0; y < divs; y++) {
	buffer.data << (wallCoords[1] - wallCoords[0]) * ((float)y/(divs)) + wallCoords[0];//bottom left
	buffer.data << (wallCoords[1] - wallCoords[0]) * ((float)(y + 1)/(divs)) + wallCoords[0];//top left
	buffer.data << (wallCoords[1] - wallCoords[0]) * ((float)(y + 1)/(divs))
	  + (wallCoords[3]-wallCoords[0]) * ((float)(x+1)/(divs))
	  + wallCoords[0];



	buffer.data << (wallCoords[1] - wallCoords[0]) * ((float)y/(divs)) + wallCoords[0];//bottom left
	buffer.data << (wallCoords[1] - wallCoords[0]) * ((float)(y + 1)/(divs))
	  + (wallCoords[3]-wallCoords[0]) * ((float)(x+1)/(divs))
	  + wallCoords[0];//top right
	buffer.data << (wallCoords[3] - wallCoords[0]) * ((float)(x + 1)/(divs)) + wallCoords[0];//bottom right
      }
    }

    /*buffer.addresses.push_back((void *)(buffer.data.size()*sizeof(GLfloat)));
    buffer.elements.push_back(2);
    for (unsigned int i = 0; i < buffer.vertCount; i++) {
      buffer.data.push_back(1);//temporary
      buffer.data.push_back(1);//temporary
    }*/

    buffer.addresses.push_back((void *)(buffer.data.size()*sizeof(GLfloat)));
    buffer.elements.push_back(3);
    for (unsigned int i = 0; i < buffer.vertCount; i++) {
      buffer.data << normal;
    }

    glGenBuffers(1, &buffer.id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(GLfloat) * buffer.data.size(),
		 &buffer.data[0],
		 GL_STATIC_DRAW);
  }
  //just add in 2 triangles
  buffer.verts << wallCoords[0] << wallCoords[1] << wallCoords[2]
	       << wallCoords[0] << wallCoords[2] << wallCoords[3];
  buffer.norms << glm::cross(buffer.verts[1] - buffer.verts[0],
			     buffer.verts[2] - buffer.verts[0])
	       << glm::cross(buffer.verts[4] - buffer.verts[3],
			     buffer.verts[5] - buffer.verts[3]);
  instance++;
}

void Wall::drawVerts() {
  if (myTypeId >= 5) return;
  glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
  for (unsigned int i = 0; i < buffer.addresses.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, buffer.elements[i], GL_FLOAT,
			  GL_FALSE, 0, buffer.addresses[i]);
  }

  glDrawArrays(GL_TRIANGLES, 0, buffer.vertCount);

  for (unsigned int i = 0; i < buffer.addresses.size(); i++)
    glDisableVertexAttribArray(i);

}
