#include "../include/objectHandler.h"

std::vector<int> parseFace(std::string s) {
  std::vector<int> x;
  std::stringstream ss(s);
  while (getline(ss, s, '/')) x.push_back(stoi(s));
  return x;
}

void ObjectHandler::loadDataFromFile(const std::string &objectName) {
  static Data &xml = Data::getInstance();
  objects[objectName] = ReadData();
  ReadData *d = &objects[objectName];
  std::ifstream fin(xml.getXmlStr(objectName + "/objFile"));
  if (!fin.is_open()) {
    std::cout << "Failed to open "
	      << xml.getXmlStr(objectName + "/objFile")
	      << std::endl;
  }
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
    }
    else if (tag[0] == 'f') {
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
}


const ReadData & ObjectHandler::generate(const std::string &objectName) {
  if (objects.count(objectName)) return objects[objectName];
  //load the data since it isn't there yet
  loadDataFromFile(objectName);
  const ReadData *rd = &objects[objectName];
  //print out info, not really necessary
  std::cout << "------------------------ "
	    << objectName << " info "
	    << "------------------------"
	    << std::endl;

  GLfloat a[3], b[3];
  for (int i = 0; i < 3; i++) a[i] = b[i] = rd->v[0][i];
  for (auto vert : rd->v)
    for (int i = 0; i < 3; i++) {
      a[i] = std::min(a[i], vert[i]);
      b[i] = std::max(b[i], vert[i]);
    }

  std::cout << "Dimensions: " << std::endl
	    << "\tx: (" << a[0] << ", " << b[0] << ")" << std::endl
	    << "\ty: (" << a[1] << ", " << b[1] << ")" << std::endl
	    << "\tz: (" << a[2] << ", " << b[2] << ")" << std::endl;

  //we now have ReadData which contains parsed data
  return objects[objectName];
}
