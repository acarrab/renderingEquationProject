#include "../include/objectHandler.h"

ObjHandler& ObjHandler::getInstance() {
  static ObjHandler instance;
  return instance;
}
std::vector<int> parseFace(std::string s) {
  std::vector<int> x;
  std::stringstream ss(s);
  while (getline(ss, s, '/')) x.push_back(stoi(s));
  return x;
}

read_data ObjHandler::getDataFromFile(std::string fileName) {
  read_data d;
  std::ifstream fin(fileName);
  std::string tag, s;

  bool first = true;
  while (fin >> tag) {
    std::getline(fin, s);
    if (tag[0] == 'v') {
      std::stringstream ss(s);
      std::vector< GLfloat > v;
      GLfloat x;
      while (ss >> x) v.push_back(x);

      if (tag == "v") d.v.push_back(v);
      else if (tag == "vt") d.vt.push_back(v);
      else if (tag == "vn") d.vn.push_back(v);
      else if (tag == "vx") d.vx.push_back(v);
      else if (tag == "vy") d.vy.push_back(v);
      else std::cerr << "UNKNOWN TAG: " << tag << ' ' << s << std::endl;



    } else if (tag[0] == 'f') {
      if (first) {
	std::stringstream ss(s);
	std::string face;

	std::vector< std::vector<int> > all;
	for (int i = 0; i < 4; i++) {
	  ss >> face;
	  all.push_back(parseFace(face));
	}
	d.f.push_back(all);
	//first = false;
      }
    } else if (tag[0] != '#') {
      std::cerr << "UNKNOWN TAG: " << tag << ' ' << s << std::endl;
    }
  }

  return d;
}

//converts to triangles
void triangularize(obj_data &od,
		   std::vector< std::vector< std::vector<int> > > &f,
		   std::vector< std::vector<GLfloat> > &v,
		   int index) {
 for (auto face : f) {
    for (int i = 0; i < 3; i++)
      for (GLfloat point : v[face[i][index] - 1]) od.data.push_back(point);
    for (int i = 2; i < 5; i++)
      for (GLfloat point : v[face[i%4][index] - 1]) od.data.push_back(point);
  }
}
obj_data* ObjHandler::getObjDataOf(std::string objectName) {
  if (objects.find(objectName) != objects.end())
    return &objects.find(objectName)->second;
  std::string fileName;
  try {
    fileName = Data::g().getXmlStr(objectName + "/fileName");
  } catch (...) {
    std::cerr << "Failed to find" << objectName << "/fileName" << std::endl;
    return nullptr;
  }
  read_data rd = getDataFromFile(fileName);
  obj_data od;
  triangularize(od, rd.f, rd.v, 0);
  od.vertices = od.data.size() / 3;

  od.normalIndex =  od.data.size();
  triangularize(od, rd.f, rd.vn, 2);

  od.textureIndex = od.data.size();
  triangularize(od, rd.f, rd.vt, 1);

  od.tangentIndexX = od.data.size();
  triangularize(od, rd.f, rd.vx, 0);

  od.tangentIndexY = od.data.size();
  triangularize(od, rd.f, rd.vy, 0);

  /*

  od.normalIndex = od.data.size();
  for (auto face : rd.f) {
    for (int i = 0; i < 3; i++)
      for (GLfloat point : rd.v[face[i][0] - 1]) od.data.push_back(point);
    for (int i = 2; i < 5; i++)
      for (GLfloat point : rd.v[face[i%4][0] - 1]) od.data.push_back(point);
  }


  for (auto face : rd.f)
    for (int normal : face[1])
      for (float val : rd.vn[normal - 1])
	od.data.push_back(val);

  od.textureIndex = od.data.size();
  for (auto face : rd.f)
    for (int textCoord : face[2])
      for (float val : rd.vt[textCoord - 1])
	od.data.push_back(val);
  */


  objects[objectName] = od;
  return &objects[objectName];
}

void ObjHandler::bindOn(std::string objectName) {
  obj_data *od;
  if (objects.find(objectName) != objects.end())
    od = getObjDataOf(objectName);
  else
    od = &objects.find(objectName)->second;

  glGenBuffers(1,&od->pointer);
  glBindBuffer(GL_ARRAY_BUFFER, od->pointer);

  glBufferData(GL_ARRAY_BUFFER,
	       od->data.size() * sizeof(float),
	       &od->data[0],
	       GL_STATIC_DRAW);

  glVertexPointer(3, GL_FLOAT,
		  3 * sizeof(GLfloat),
		  NULL);
  glNormalPointer(GL_FLOAT,
		  3 * sizeof(GLfloat),
		  (GLfloat *)(od->normalIndex * sizeof(GLfloat)));
  // glTexCoordPointer(2,
  // 		    GL_FLOAT,
  // 		    2 * sizeof(GLfloat),
  // 		    (GLfloat *)(od->textureIndex * sizeof(GLfloat)));

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
