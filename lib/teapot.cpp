#include "../include/teapot.h"
BufferData Teapot::buffer = BufferData();
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
Teapot::Teapot(const std::string &programName) :
    GenericObject(programName),
    rtnMtxId(glGetUniformLocation(getProgramId(), "rotationMtx")),
    diffuseId(glGetUniformLocation(getProgramId(), "diffuseColor")),
    specularId(glGetUniformLocation(getProgramId(), "specularColor")),
    shineId(glGetUniformLocation(getProgramId(), "shine")),
    rtn(glm::rotate(45.0f, glm::vec3(0.0, 1.0, 0.0))),
    diffuseColor(Data::g().getXmlVec4("teapot/diffuse")),
    specularColor(Data::g().getXmlVec4("teapot/specular")),
    shininess(Data::g().getXmlFloat("teapot/shininess"))
{
  if (!buffer.instantiated) {
    buffer.instantiated = true;
    //load the data
    const ReadData &parsedStuff = oh.getDataFor("teapot");

    buffer.vertCount = parsedStuff.f.size() * 6;
    //convert
    //buffer vertices
    buffer.addresses.push_back((void *) 0);
    buffer.elements.push_back(3);
    fromQuads(parsedStuff.f, parsedStuff.v, buffer.data, 0);

    //buffer texture coords
    buffer.addresses.push_back((void *)(buffer.data.size() * sizeof(GLfloat)));
    buffer.elements.push_back(2);
    fromQuads(parsedStuff.f, parsedStuff.vt, buffer.data, 1);

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
    std::cout << buffer.id << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
    glBufferData(GL_ARRAY_BUFFER,
		 sizeof(GLfloat) * buffer.data.size(),
		 &buffer.data[0],
		 GL_STATIC_DRAW);
  }
}

void Teapot::display() {
  displayStart();

  glUniformMatrix4fv(rtnMtxId, 1, GL_FALSE, &rtn[0][0]);
  glUniform4f(diffuseId, diffuseColor.r, diffuseColor.g,
	      diffuseColor.b, diffuseColor.a);
  glUniform4f(specularId, specularColor.r, specularColor.g,
	      specularColor.b, specularColor.a);
  glUniform1f(shineId, shininess);

  //glGetUniformLocation();
  glBindBuffer(GL_ARRAY_BUFFER, buffer.id);
  for (int i = 0; i < buffer.addresses.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, buffer.elements[i], GL_FLOAT,
			  GL_FALSE, 0, buffer.addresses[i]);
  }

  glDrawArrays(GL_TRIANGLES, 0, buffer.vertCount);

  for (int i = 0; i < buffer.addresses.size(); i++)
    glDisableVertexAttribArray(i);

}
