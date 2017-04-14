#include "../include/objectHandler.h"

std::map<std::string, obj_data> ObjHandler::objects = std::map<std::string, obj_data>();

void addFloats(std::vector<float> &fvec, std::string s) {
  std::stringstream ss(s);
  float tmp;
  while (ss >> tmp) fvec.push_back(tmp);
}
void addFace(std::vector< std::vector<int> > &faces, std::string s) {
  std::stringstream stream(s);
  while(std::getline(stream, s, ' ')) {
    std::stringstream stream2(s);
    std::vector<int> oneFace;
    while (std::getline(stream2, s, '/')) oneFace.push_back(stoi(s));
    faces.push_back(oneFace);
  }
}
read_data ObjHandler::getDataFromFile(std::string fileName) {
  read_data d;
  std::ifstream fin(fileName);
  for (std::string s1, s2; std::getline(fin, s1, ' ');) {
    std::getline(fin, s2);
    switch(s1) {
    case "v": addFloats(d.v, s2); break;
    case "vt": addFloats(d.vn, s2); break;
    case "vx": addFloats(d.vx, s2); break;
    case "vy": addFloats(d.vy, s2); break;
    case "f": addFace(d.f, s2); break;
    }
    if (s1 == "v")  addFloats(d.v, s2);
    else if (s1 == "vt") while (stream1 >> fTmp) d.vt.push_back(fTmp);
    else if (s1 == "vn") while (stream1 >> fTmp) d.vn.push_back(fTmp);
    else if (s1 == "vx") while (stream1 >> fTmp) d.vx.push_back(fTmp);
    else if (s1 == "vy") while (stream1 >> fTmp) d.vy.push_back(fTmp);
    else if (s1 == "f")  {
    }
    else if (s1[0] != '#') {
      std::cerr << "Unknown line: " << s1 << " " << stream1.str() << std::endl;
    }
  }
  /* test block
     std::ofstream out("testOut.txt");
     for (int i = 0; i < d.v.size(); i += 3)
     out << "v " << d.v[i] << " " << d.v[i + 1] << " " << d.v[i + 2] << std::endl;
     for (int i = 0; i < d.vt.size(); i += 2)
     out << "vt " << d.vt[i] << " " << d.vt[i + 1] << std::endl;
     for (int i = 0; i < d.vn.size(); i += 3)
     out << "vn " << d.vn[i] << " " << d.vn[i + 1] << " " << d.vn[i + 2] << std::endl;
     for (int i = 0; i < d.f.size(); i += 9) {
     out << "f";
     for (int j = 0; j < 3; j++)
     out << " " << d.f[i + j*3] << "/" << d.f[i + j * 3 + 1] << "/" << d.f[i + j * 3 + 2];
     out << std::endl;
     }
     out.close();
  */
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

  std::cout << "vertices: " << rd.v.size() << std::endl;
  std::cout << "texture Coords: " << rd.vt.size() << std::endl;
  std::cout << "vertex normals: " << rd.vn.size() << std::endl;
  std::cout << "vx tangents: " << rd.vx.size() << std::endl;
  std::cout << "vy tangents: " << rd.vy.size() << std::endl;
  std::cout << "faces: " << rd.f.size() << std::endl;

  int mx = rd.f[0][2];
  int mn = rd.f[0][2];
  for (std::vector<int> x : rd.f) {
    mx = std::max(x[2], mx);
    mn = std::min(x[2], mn);
  }
  /*
    for each point of face,
    3 vertices, 2 texture coords, 3 vertex normals, 3 vx tangents, 3 vy tangents
    f.size() * (3 + 2 + 3 + 3 + 3) = f.size() * 14
    like 7mb not bad
  */

  od.data = new GLfloat[rd.f.size() * 14];

  //put in vertices first
  int i = 0;
  int index;
  for (std::vector<int> x : rd.f) {
    index = (x[0] - 1)*3;
    for (int k = 0; k < 3; k++) od.data[i++] = rd.v[index++];
  }
  od.normalIndex = i;
  //put in normals
  for (std::vector<int> x : rd.f) {
    index = (x[2] - 1)*3;
    for (int k = 0; k < 3; k++) od.data[i++] = rd.vn[index++];
  }
  od.tangentIndex = i;
  //put in vertex tangents
  for (std::vector<int> x : rd.f) {
    index = (x[2] - 1)*3;
    for (int k = 0; k < 3; k++)  {
      od.data[i++] = rd.vx[index];
      od.data[i++] = rd.vy[index++];
    }
  }
  od.textureIndex = i;
  for (std::vector<int> x : rd.f) {
    index = (x[1] - 1)*2;
    for (int k = 0; k < 2; k++) od.data[i++] = rd.vt[index++];
  }
  objects[objectName] = od;
  return &objects[objectName];
}
