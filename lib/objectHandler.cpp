#include "../include/objectHandler.h"

ObjHandler& ObjHandler::getInstance() {
  static ObjHandler instance;
  return instance;
}
std::vector<int> ObjHandler::parseFace(std::string s) {
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
  /*
  std::cerr << "v:\t"  << d.v.size() << std::endl;
  std::cerr << "vn:\t" << d.vn.size() << std::endl;
  std::cerr << "vt:\t" << d.vt.size() << std::endl;
  std::cerr << "vx:\t" << d.vx.size() << std::endl;
  std::cerr << "vy:\t" << d.vy.size() << std::endl;
  std::cerr << "f:\t"  << d.f.size() << std::endl;*/
  return d;
}

//converts to triangles
void ObjHandler::triangularize(obj_data &od,
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


  // std::cerr << "size:\t"  << od.data.size() << std::endl;

  objects[objectName] = od;
  return &objects[objectName];
}
