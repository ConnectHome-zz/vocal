#include "createXml.h"


xml_node<>* createHeader(xml_document<>* document, map<string,string>& attributs)
{
	map<string, string>::iterator it;
	xml_node<>* header = document->allocate_node(node_declaration);
	for(it = attributs.begin(); it != attributs.end(); it++)
	{
		header->append_attribute(document->allocate_attribute((*it).first.c_str(), (*it).second.c_str()));
	}
	
	return header;
}

xml_node< > * createNode(xml_document<>* document, string nodeName,map<string,string>& attributs, string nodeValue)
{
	map<string, string>::iterator it;
	xml_node<>* n = document->allocate_node(node_element, document->allocate_string(nodeName.c_str()));
	if(nodeValue != "")
		n->value(document->allocate_string(nodeValue.c_str()));
	
	for(it = attributs.begin(); it != attributs.end(); it++)
	{
		n->append_attribute(document->allocate_attribute((*it).first.c_str(), (*it).second.c_str()));
	}
	
	return n;
}

std::string acreateGestureXml(std::string exp, std::string dest, std::string msgType, std::string Id, std::string movId)
{
	xml_document<>* document = new xml_document<>();
	std::string xml_string = "";

	map<string,string> values;
	map<string, string> emptyMap;
	values.insert(make_pair("version", "1.0"));
	values.insert(make_pair("encoding", "iso-8859-1"));
	//document->append_node(createHeader(document, values));
	xml_node<> *doc = NULL;
	doc = createNode(document, "doc", emptyMap);
	document->append_node(doc);

	doc->append_node(createNode(document, "exp", emptyMap, exp));
	doc->append_node(createNode(document, "dest", emptyMap, dest));
	doc->append_node(createNode(document, "msgtype", emptyMap, msgType));

	xml_node<> *msg = NULL;
	msg = createNode(document, "msg", emptyMap);
	doc->append_node(msg);

	msg->append_node(createNode(document, "ID", emptyMap, Id));
	msg->append_node(createNode(document, "movID", emptyMap, movId));

	rapidxml::print(back_inserter(xml_string), (*document), 0);

	return xml_string;
}




std::string createInitGestureXml()
{

	xml_document<>* document = new xml_document<>();
	std::string xml_string = "";

	map<string,string> values;
	map<string, string> emptyMap;
	values.insert(make_pair("version", "1.0"));
	values.insert(make_pair("encoding", "iso-8859-1"));
	//document->append_node(createHeader(document, values));
	
	
	xml_node<> *doc = NULL;
	doc = createNode(document, "doc", emptyMap);
	document->append_node(doc);

	doc->append_node(createNode(document, "exp", emptyMap, "1"));
	doc->append_node(createNode(document, "dest", emptyMap, "0"));
	doc->append_node(createNode(document, "msgtype", emptyMap, "1"));
	
	xml_node<> *msg = NULL;
	msg = createNode(document, "msg", emptyMap);
	doc->append_node(msg);

	msg->append_node(createNode(document, "ID", emptyMap, "2"));
	msg->append_node(createNode(document, "nameP", emptyMap, "Microphone"));
	msg->append_node(createNode(document, "descP", emptyMap, "Speak to command your house !"));
	
	//Ajout d'un "mov"
	xml_node<> *mov1 = NULL;
	mov1 = createNode(document, "mov", emptyMap);
	msg->append_node(mov1);

	mov1->append_node(createNode(document, "movID", emptyMap, "1"));
	mov1->append_node(createNode(document, "nameM", emptyMap, "Action 1"));
	mov1->append_node(createNode(document, "descM", emptyMap, "Say Action 1"));


	
	//Ajout d'un "mov"
	xml_node<> *mov2 = NULL;
	mov2 = createNode(document, "mov", emptyMap);
	msg->append_node(mov2);

	mov2->append_node(createNode(document, "movID", emptyMap, "2"));
	mov2->append_node(createNode(document, "nameM", emptyMap, "Action 2"));
	mov2->append_node(createNode(document, "descM", emptyMap, "Say Action 2"));


	//Ajout d'un "mov"
	xml_node<> *mov3 = NULL;
	mov3 = createNode(document, "mov", emptyMap);
	msg->append_node(mov3);

	mov3->append_node(createNode(document, "movID", emptyMap, "3"));
	mov3->append_node(createNode(document, "nameM", emptyMap, "Action 3"));
	mov3->append_node(createNode(document, "descM", emptyMap, "Say Action 3"));

	//Ajout d'un "mov"
	xml_node<> *mov4 = NULL;
	mov4 = createNode(document, "mov", emptyMap);
	msg->append_node(mov4);

	mov4->append_node(createNode(document, "movID", emptyMap, "4"));
	mov4->append_node(createNode(document, "nameM", emptyMap, "Action 4"));
	mov4->append_node(createNode(document, "descM", emptyMap, "Say Action 4"));
	
	//Ajout d'un "mov"
	xml_node<> *mov5 = NULL;
	mov5 = createNode(document, "mov", emptyMap);
	msg->append_node(mov5);

	mov5->append_node(createNode(document, "movID", emptyMap, "5"));
	mov5->append_node(createNode(document, "nameM", emptyMap, "Action 5"));
	mov5->append_node(createNode(document, "descM", emptyMap, "Say Action 5"));

	/*
	//Ajout d'un "mov"
	xml_node<> *mov4 = NULL;
	mov4 = createNode(document, "mov", emptyMap);
	msg->append_node(mov4);

	mov4->append_node(createNode(document, "movID", emptyMap, "4"));
	mov4->append_node(createNode(document, "nameM", emptyMap, "Mouvement 4"));
	mov4->append_node(createNode(document, "descM", emptyMap, "Description 4"));
	*/

	rapidxml::print(back_inserter(xml_string), (*document), 0);

	return xml_string;
}
