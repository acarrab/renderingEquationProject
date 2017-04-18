#include "../include/objectHandler.h"



//converts to triangles
void triangularize(std::vector<GLfloat> &data,
		   std::vector< std::vector< std::vector<int> > > &f,
		   std::vector< std::vector<GLfloat> > &v,
		   int index) {
 for (auto face : f) {
    for (int i = 0; i < 3; i++)
      for (GLfloat point : v[face[i][index] - 1]) data.push_back(point);
    for (int i = 2; i < 5; i++)
      for (GLfloat point : v[face[i%4][index] - 1]) data.push_back(point);
  }
}
void baseConvert(std::vector<GLfloat> &data,
		 std::vector< std::vector< std::vector<int> > > &f,
		 std::vector< std::vector<GLfloat> > &v,
		 int index) {
  for (auto face : f)
    for (int i = 0; i < 3; i++)
      for (GLfloat point : v[face[i][index] - 1]) data.push_back(point);
}

std::vector<int> parseFace(std::string s) {
  std::vector<int> x;
  std::stringstream ss(s);
  while (getline(ss, s, '/')) x.push_back(stoi(s));
  return x;
}

read_data * ObjectHandler::getDataFromFile(std::string fileName) {
  read_data *d = new read_data();
  std::ifstream fin(fileName);
  std::string tag, s;
  while (fin >> tag) {
    std::getline(fin, s);
    if (tag[0] == 'v') {
      std::stringstream ss(s);
      std::vector< GLfloat > v;
      GLfloat x;
      while (ss >> x) v.push_back(x);//read in all floats in that line
      if (tag == "v") d->v.push_back(v);
      else if (tag == "vt") d->vt.push_back(v);
      else if (tag == "vn") d->vn.push_back(v);
      else if (tag == "vx") d->vx.push_back(v);
      else if (tag == "vy") d->vy.push_back(v);
      else std::cerr << "UNKNOWN TAG: " << tag << ' ' << s << std::endl;
    } else if (tag[0] == 'f') {
      std::stringstream ss(s);
      std::string face;
      std::vector< std::vector<int> > all;
      for (int i = 0; i < 4; i++) {
	ss >> face;
	all.push_back(parseFace(face));
      }
      d->f.push_back(all);
    } else if (tag[0] != '#') {
      std::cerr << "UNKNOWN TAG: " << tag << ' ' << s << std::endl;
    }
  }
  return d;
}


const Draw_Data & ObjectHandler::generate(const std::string &objectName) {
  static Data &xml = Data::getInstance();
  if (objects.count(objectName)) return objects[objectName];

  /*
    In order to generate a program we have to load the vertex
    information and store it in vbo
  */
  //set shader
  //if quads we have to convert to triangles
  std::string fileName = xml.getXmlStr(objectName + "/objFile");
  read_data *rd = getDataFromFile(fileName);
  Draw_Data drawData;
  drawData.setShader(xml.getXmlStr(objectName + "/shader"));
  std::vector<GLfloat> data;
  void (*convert)(std::vector<GLfloat> &data,
		     std::vector< std::vector< std::vector<int> > > &f,
		     std::vector< std::vector<GLfloat> > &v,
		  int index);

  //set buffer generator
  auto genBuf = [](std::vector<GLfloat> &data)->GLuint{
    GLuint tmpId;
    glGenBuffers(1, &tmpId);
    glBindBuffer(GL_ARRAY_BUFFER, tmpId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(),
		 &data[0], GL_STATIC_DRAW);
    return tmpId;
  };
  //set conversion
  if (xml.getXmlBool(objectName + "/quads")) {
    convert = &triangularize;
  } else {
    convert = &baseConvert;
  }

  //get vertice data
  int face = 0;
  convert(data, rd->f, rd->v, face);//converts data to triangles
  drawData.setVertexCount(data.size() / 3);   //from quads
  //load data to gpu, then push it back VBO_Data
  drawData.push_back(VBO_Data(genBuf(data), 0, 3));

  //tangents
  if (rd->vx.size() && rd->vy.size()) {
    data.resize(0); //does not change underlying capacity, i.e. no new mallocs
    convert(data, rd->f, rd->vx, face);
    //load data to gpu then push it back VBO_Data
    drawData.push_back(VBO_Data(genBuf(data), 3, 3));

    data.resize(0);
    convert(data, rd->f, rd->vy, face);
    //load data to gpu then push it back VBO_Data
    drawData.push_back(VBO_Data(genBuf(data), 4, 3));
  }

  if (rd->vt.size()) {
    face++;
    data.resize(0);
    convert(data, rd->f, rd->vt, face);
    //load data to gpu then push it back VBO_Data
    drawData.push_back(VBO_Data(genBuf(data), 1, 2));
    //only 2 for texture
  }

  if (rd->vn.size()) {
    face++;
    data.resize(0);
    convert(data, rd->f, rd->vn, face);
    drawData.push_back(VBO_Data(genBuf(data), 2, 3));
  }
  delete rd;
  //we now have drawData which contains all attributes and whatnot
  objects[objectName] = drawData;
  return objects[objectName];
}

void ObjectHandler::attributeLoad(const std::string &objectName) {
  static ShaderHandler &sh = ShaderHandler::getInstance();
  //check if we have vbo's generated
  currentObj = &generate(objectName);
  //start up the shader program
  sh.useProgram(currentObj->getShader());
  //enable all attributes necessary
  //load each vertex attribute
  for (const VBO_Data & va : currentObj->getAttribs()) {
    glEnableVertexAttribArray(va.attribNum);
    glVertexAttribPointer(va.attribNum, va.vecSize, va.dataType,
			  va.normalized, va.stride, va.address);
    glBindBuffer(GL_ARRAY_BUFFER, va.id);
  }
}
void ObjectHandler::attributeDraw() {
  //draw the array
  glDrawArrays(currentObj->getVertexType(), 0, currentObj->getVertexCount());
  std::cout << currentObj->getVertexCount() << std::endl;
}
void ObjectHandler::attributeClear() {
  //disable the attributes
  for (const VBO_Data & va : currentObj->getAttribs()) {
    glDisableVertexAttribArray(va.attribNum);
  }
}
