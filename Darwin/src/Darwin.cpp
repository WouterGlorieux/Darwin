//============================================================================
// Name        : Darwin.cpp
// Author      : Skidzobolder
// Version     :
// Description : main for Darwin
//============================================================================

//#include "rapidxml.hpp"
//#include "rapidxml_print.hpp"

#include <String>
#include <conio.h>
#include "Evolver.h"

int main(int argc, char *argv[]) {

	Evolver cEvolver;
	std::cout << cEvolver.GetTitle() << ' ' << cEvolver.GetPopulationSize() << std::endl;


	if(argc == 2){
		std::cout  << "Parameter: " << argv[1] << std::endl;
	}


	std::string strFileName(argv[1]);
	cEvolver.readConfig(strFileName);



	std::cout << "Press any key to terminate this program. " ;
	getch();
	return 0;
}

/*
void makexml(){
	xml_document<> doc;

	// xml declaration
	xml_node<>* decl = doc.allocate_node(node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	// root node
	xml_node<>* root = doc.allocate_node(node_element, "rootnode");
	root->append_attribute(doc.allocate_attribute("version", "1.0"));
	root->append_attribute(doc.allocate_attribute("type", "example"));
	doc.append_node(root);

	// child node
	xml_node<>* child = doc.allocate_node(node_element, "childnode");
	root->append_node(child);

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	std::string xml_no_indent;
	// print_no_indenting is the only flag that print() knows about
	print(std::back_inserter(xml_no_indent), doc, print_no_indenting);
	// xml_no_indent now contains non-indented XML

	cout << xml_as_string << endl;
}
*/
