/*
 * Evolver.cpp
 *
 *  Created on: 3-feb.-2012
 *      Author: Skidzobolder
 */

#include "Evolver.h"

void readConfig();
void traverse_xml(const std::string& input_xml);


void readConfig()
{
	std::ifstream t("C:\\workspaces\\Darwin\\Darwin\\src\\config.xml");
	std::stringstream buffer;
	buffer << t.rdbuf();


	std::cout << buffer.str() << std::endl;
	traverse_xml(buffer.str());
}

void traverse_xml(const std::string& input_xml)
{
	using namespace rapidxml;
    // (input_xml contains the above XML)

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    xml_document<> doc;
    // we are choosing to parse the XML declaration
    // parse_no_data_nodes prevents RapidXML from using the somewhat surprising
    // behavior of having both values and data nodes, and having data nodes take
    // precedence over values when printing
    // >>> note that this will skip parsing of CDATA nodes <<<
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

    // alternatively, use one of the two commented lines below to parse CDATA nodes,
    // but please note the above caveat about surprising interactions between
    // values and data nodes (also read http://www.ffuts.org/blog/a-rapidxml-gotcha/)
    // if you use one of these two declarations try to use data nodes exclusively and
    // avoid using value()
    //doc.parse<parse_declaration_node>(&xml_copy[0]); // just get the XML declaration
    //doc.parse<parse_full>(&xml_copy[0]); // parses everything (slowest)

    // since we have parsed the XML declaration, it is the first node
    // (otherwise the first node would be our root node)
    std::string encoding = doc.first_node()->first_attribute("encoding")->value();
    // encoding == "utf-8"

    // we didn't keep track of our previous traversal, so let's start again
    // we can match nodes by name, skipping the xml declaration entirely
    xml_node<>* cur_node = doc.first_node("rootnode");
    std::string rootnode_type = cur_node->first_attribute("type")->value();
    // rootnode_type == "example"

    // go straight to the first evendeepernode
    cur_node = cur_node->first_node("childnode")->first_node("evendeepernode");
    std::string attr2 = cur_node->first_attribute("attr2")->value();
    // attr2 == "dog"
    std::cout << attr2 << std::endl;


    // and then to the second evendeepernode
    cur_node = cur_node->next_sibling("evendeepernode");
    attr2 = cur_node->first_attribute("attr2")->value();
    // now attr2 == "wolf"
    std::cout << attr2 << std::endl;

}

