#include "../include/objectHandler.h"

ObjHandler& ObjHandler::getInstance() {
  static ObjHandler instance;
  return instance;
}
void ObjHandler::addFloats(std::vector< std::vector<float> > *fvec, std::stringstream &ss) {
  std::stringstream &ss(s);
  float tmp;
  std::vector<float> ftemp;
  while (ss >> tmp) ftemp.push_back(tmp);
  fvec->push_back(ftemp);
}
void ObjHandler::addFace(std::vector< std::vector< std::vector<int> > > *faces, std::stringstream &ss) {
  std::vector< std::vector<int> >  f(3);
  while(std::getline(ss, s, ' ')) {
    std::stringstream stream2(s);
    for (int i = 0; i < 3; i++) {
      std::getline(stream2, s, '/');
      f[i].push_back(stoi(s));
    }
  }
  faces->push_back(f);
}
read_data ObjHandler::getDataFromFile(std::string fileName) {
  read_data d;
  std::ifstream fin(fileName);
  for (std::string s; std::getline(fin, s);) {
    std::stringstream ss(s);
    if (s1 == "v")  addFloats(&d.v, ss);
    else if (s1 == "vt") addFloats(&d.vn, ss);
    else if (s1 == "vx") addFloats(&d.vx, ss);
    else if (s1 == "vy") addFloats(&d.vy, ss);
    else if (s1 == "f") addFace(&d.f, ss);
    else
      std::cerr << "Unknown line: " << s1 << " " << ss.str() << std::endl;
  }
  return d;
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

  for (auto face : rd.f)
    for (int vertice : face[0])
      for (float val : rd.v[vertice])
	od.data.push_back(val);

  od.normalIndex = od.data.size();
  for (auto face : rd.f)
    for (int normal : face[1])
      for (float val : rd.vn[normal])
	od.data.push_back(val);

  od.textureIndex = od.data.size();
  for (auto face : rd.f)
    for (int textCoord : face[2])
      for (float val : rd.vt[textCoord])
	od.data.push_back(val);




  objects[objectName] = od;
  return &objects[objectName];
}
