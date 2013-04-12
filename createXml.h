#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml; 
using namespace std;

xml_node< > * createHeader(xml_document<>* document, map<string,string>& attributs);
xml_node< > * createNode(xml_document<>* document, string nodeName,map<string,string>& attributs, string nodeValue= "");
std::string acreateGestureXml(std::string exp, std::string dest, std::string msgType, std::string Id, std::string movId);

std::string createInitGestureXml();
