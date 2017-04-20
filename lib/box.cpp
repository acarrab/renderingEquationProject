#include "../include/box.h"
BufferData Box::buffer = BufferData();
glm::vec3 Box::corners[2][2][2];

//pushes back vert
std::vector<GLfloat> & operator<<(std::vector<GLfloat> &out,
				  const glm::vec3 &vec) {
  out.push_back(vec.x);
  out.push_back(vec.y);
  out.push_back(vec.z);
  return out;
}

Box::Box(const std::string &programName) :
    GenericObject(programName),
    rtnMtxId(glGetUniformLocation(getProgramId(), "rotationMtx")),
    diffuseId(glGetUniformLocation(getProgramId(), "diffuseColor")),
    specularId(glGetUniformLocation(getProgramId(), "specularColor")),
    shineId(glGetUniformLocation(getProgramId(), "shine")),
    rtn(glm::rotate(45.0f, glm::vec3(0.0, 1.0, 0.0))),

    diffuseColor({Data::g().getXmlVec4("box/diffuse1"),
	  Data::g().getXmlVec4("box/diffuse2"),
	  Data::g().getXmlVec4("box/diffuse3")}),

    specularColor({Data::g().getXmlVec4("box/specular1"),
	  Data::g().getXmlVec4("box/specular2"),
	  Data::g().getXmlVec4("box/specular3")}),

    shininess({Data::g().getXmlFloat("box/shininess1"),
	  Data::g().getXmlFloat("box/shininess2"),
	  Data::g().getXmlFloat("box/shininess3")})
{

  if (!buffer.instantiated) {
    buffer.instantiated = true;
    //generate corners
    float w = Data::getInstance().getXmlFloat("box/width");
    for (int v = 0; v < 8; v++)
      corners[v] = glm::vec3(-w/2 + (v&4) * w, (v&2)*w,-w/2 + (v&1) * w);

    //testing
    //0, 2, 3 | x
    //0, 3, 1 | x
    for (int v = 0; v < 3; v++) {
      for (int b = 0; b < 2; b++) {
	unsigned int i = x << 2 +
	  buffer.data, corners[x][0][0]), corners[x][1][0]), corners[x][1][1]);
	in(in(in(buffer.data, corners[x][0][0]), corners[x][1][1]), corners[x][0][1]);
    }



    glGenBuffers(1, &buffer.id);
    std::cout << buffer.id << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
    glBufferData(GL_ARRAY_BUFFER,
    		 sizeof(GLfloat) * buffer.data.size(),
    		 &buffer.data[0],
    		 GL_STATIC_DRAW);
    /*
    //each quad in the wall is split up into two triangles
    int splits = Data::getInstance().getXmlInt("box/rowColNum");


    //with x fixed - left and right wall
    glm::vec3 verts[2][2];
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < splits; y++) {
	for (int z = 0; z < splits; z++) {
	  for (int i = 0; i < 2; i++) {
	    for (int j = 0; j < 2; j++) {
	      verts[i][j] =                 //gives y position
		(corners[x][1][0] - corners[x][0][0]) * (((float)y + i)/splits) +
		                            //gives z position
		(corners[x][0][1] - corners[x][0][1]) * (((float)z + i)/splits) +
		corners[x][0][0]; //gives base
	    }
	  }
	  //all the vertices are generated now
	  //overwrote operator to be able to do this
	  buffer.data << verts[0][0] << verts[1][0] << verts[1][1];
	  buffer.data << verts[0][0] << verts[1][1] << verts[0][1];
	}
      }
      }*/
    //two walls are now generated
  }
}
void Box::display() {
  displayStart();
  glBindBuffer(GL_ARRAY_BUFFER, buffer.id);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glDrawArrays(GL_TRIANGLES, 0, 12);
  glDisableVertexAttribArray(0);
}
