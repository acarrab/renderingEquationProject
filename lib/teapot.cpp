#include "../include/teapot.h"
void fromQuads(const std::vector< std::vector< std::vector<int> > > &faceVec,
	       const std::vector< std::vector< GLfloat > > &vertex,
	       std::vector<GLfloat> &data,
	       int faceIndex)
{
  for(auto line : faceVec) {
    for(int vertIndex = 0;  vertIndex < 3; vertIndex++)
      for (GLfloat val : vertex[line[vertIndex][faceIndex] - 1])
        data.push_back(val);
    for(int vertIndex = 2;  vertIndex < 5; vertIndex++)
      for (GLfloat val : vertex[line[vertIndex%4][faceIndex] - 1])
	data.push_back(val);
  }
}

Teapot::Teapot() :
  GenericObject("teapot"),
  rtn(glm::rotate(90.0f, glm::vec3(0.0, 1.0, 0.0)))
{

  /* has to be set eventually in other thing

     diffuseColor(dh->getXmlVec4("teapot/diffuse")),
     specularColor(dh->getXmlVec4("teapot/specular")),
     shininess(dh->getXmlFloat("teapot/shininess"))

  */
  //load the data
  const ReadData &parsedStuff = oh->getDataFor("teapot");

  buffer.vertCount = parsedStuff.f.size() * 6;
  //convert
  //buffer vertices
  buffer.addresses.push_back((void *) 0);
  buffer.elements.push_back(3);
  fromQuads(parsedStuff.f, parsedStuff.v, buffer.data, 0);

  //buffer texture coords
  //buffer.addresses.push_back((void *)(buffer.data.size() * sizeof(GLfloat)));
  //buffer.elements.push_back(2);
  //fromQuads(parsedStuff.f, parsedStuff.vt, buffer.data, 1);

  //buffer normals
  buffer.addresses.push_back((void *)(buffer.data.size() * sizeof(GLfloat)));
  buffer.elements.push_back(3);
  fromQuads(parsedStuff.f, parsedStuff.vn, buffer.data, 2);

  //buffer tangent x
  /*    buffer.addresses.push_back((void *)(buffer.data.size() * sizeof(GLfloat)));
	buffer.elements.push_back(3);
	fromQuads(parsedStuff.f, parsedStuff.vx, buffer.data, 0);

	//buffer tangent y
	buffer.addresses.push_back((void *)(buffer.data.size() * sizeof(GLfloat)));
	buffer.elements.push_back(3);
	fromQuads(parsedStuff.f, parsedStuff.vy, buffer.data, 0);*/

  glGenBuffers(1, &buffer.id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
  glBufferData(GL_ARRAY_BUFFER,
	       sizeof(GLfloat) * buffer.data.size(),
	       &buffer.data[0],
	       GL_STATIC_DRAW);

  buffer.process();// called to generate proper normals
}

void Teapot::loadAttributes(GLuint programId) {
  GenericObject::loadAttributes(programId);

  GLuint id = glGetUniformLocation(programId, "rotationMtx");
  glUniformMatrix4fv(id, 1, GL_FALSE, &rtn[0][0]);
}
void Teapot::drawVerts() {
  glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
  for (unsigned int i = 0; i < buffer.addresses.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, buffer.elements[i], GL_FLOAT,
			  GL_FALSE, 0, buffer.addresses[i]);
  }
  //drawing
  glDrawArrays(GL_TRIANGLES, 0, buffer.vertCount);

  for (unsigned int i = 0; i < buffer.addresses.size(); i++)
    glDisableVertexAttribArray(i);
}
