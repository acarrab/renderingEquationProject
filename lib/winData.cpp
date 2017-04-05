#include "../include/winData.h"
WinData::WinData() :
  d(Data::getInstance()),
  coords({d.getXmlInt("window/x"),
	d.getXmlInt("window/y"),
	d.getXmlInt("window/width"),
	d.getXmlInt("window/height")}),
  title(d.getXmlStr("window/title"))
{}
