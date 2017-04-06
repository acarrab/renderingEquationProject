#include "../include/objectHandler.h"
std::map<std::string, obj_data> ObjHandler::objects = std::map<std::string, obj_data>();
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

  obj_data d;
  std::ifstream fin(fileName);
  int iTmp; float fTmp;
  for (std::string s1, s2; std::getline(fin, s1, ' ');) {
    std::getline(fin, s2);
    std::stringstream stream1(s2);
    if (s1 == "v")  while (stream1 >> fTmp) d.v.push_back(fTmp);
    else if (s1 == "vt") while (stream1 >> fTmp) d.vt.push_back(fTmp);
    else if (s1 == "vn") while (stream1 >> fTmp) d.vn.push_back(fTmp);
    else if (s1 == "f")  {
      for (int i = 0; i < 3; i++) {
	std::getline(stream1, s2, ' ');
	std::stringstream stream2(s2);
	for (int j = 0; j < 3; j++) {
	  std::getline(stream2, s2, '/');
	  d.f.push_back(stoi(s2));
	}
      }
    }
    else if (s1[0] != '#') {
      std::cerr << "Unknown line: " << s1 << " " << stream1.str() << std::endl;
    }
  }
  objects[objectName] = d;
  /* test block
     std::ofstream out("testOut.txt");
     d = objects[objectName];
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
  return &objects[objectName];
}
