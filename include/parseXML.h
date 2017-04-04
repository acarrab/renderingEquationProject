#ifndef __PARSEXML_H__
#define __PARSEXML_H__
#include "common.h"
#include <fstream>
#include <map>
#include <deque>
#include <expat.h>
const int BUFSIZE = 512;

class ParseXML {
public:
  ParseXML( const std::string& fn ) :
    filename(fn),
    parser(NULL),
    tagNames(),
    xmlData()
  { parseXML(); }
  virtual ~ParseXML() { XML_ParserFree(parser); }

  const std::map<std::string, std::string> getXmlData() const { return xmlData; }

  static void wrapper4Start(void *data, const char *el, const char **attr);
  static void wrapper4End(void *data, const char *el);
  static void wrapper4Chars(void *data, const char *text, int textlen);

private:
  const std::string filename;
  XML_Parser parser;
  char buff[BUFSIZE];

  std::deque<std::string>  tagNames;
  std::map<std::string, std::string> xmlData;

  void parseXML();
  void displayData() const;
  void start(const char *el, const char *attr[]);
  void end(const char *);
  void chars(const char *text, int textlen);
  std::string makeTag() const;
  std::string makeTag(const std::string&) const;

  void stripTrailWhiteSpace(std::string&) const;
  ParseXML& operator=(const ParseXML&);
  ParseXML(const ParseXML&);
};

#endif
