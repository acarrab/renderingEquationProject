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

Teapot::Teapot() : GenericObject("teapot")
{
  glm::mat4 rtn(glm::rotate(90.0f, glm::vec3(0.0, 1.0, 0.0)));

  //load the data
  const ReadData &parsedStuff = oh->getDataFor("teapot");
  buffer.vertCount = parsedStuff.f.size() * 6;
  //convert
  //buffer vertices
  buffer.addresses.push_back((void *) 0);
  buffer.elements.push_back(3);
  fromQuads(parsedStuff.f, parsedStuff.v, buffer.data, 0);

  //fix position rotation outside of shader
  glm::vec4 v;
  unsigned int i = 0;
  for (; i < buffer.data.size(); i += 3) {
    v = rtn * glm::vec4(buffer.data[i], buffer.data[i + 1], buffer.data[i + 2], 1.0);
    buffer.data[i] = v.x;
    buffer.data[i + 1] = v.y;
    buffer.data[i + 2] = v.z;
  }

  //buffer normals
  buffer.addresses.push_back((void *)(buffer.data.size() * sizeof(GLfloat)));
  buffer.elements.push_back(3);
  fromQuads(parsedStuff.f, parsedStuff.vn, buffer.data, 2);

  //fix the rotation
  for (; i < buffer.data.size(); i += 3) {
    v = rtn * glm::vec4(buffer.data[i], buffer.data[i + 1], buffer.data[i + 2], 0.0);
    buffer.data[i] = v.x;
    buffer.data[i + 1] = v.y;
    buffer.data[i + 2] = v.z;
  }

  glGenBuffers(1, &buffer.id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
  glBufferData(GL_ARRAY_BUFFER,
	       sizeof(GLfloat) * buffer.data.size(),
	       &buffer.data[0],
	       GL_STATIC_DRAW);
  buffer.process();// called to generate proper normals and verts to be used in computation
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
