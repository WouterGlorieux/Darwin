//============================================================================
// Name        : DRSDarwin.cpp
// Author      : Wouter Glorieux
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <fstream>
#include <sstream>


using namespace std;


int main(int argc, char *argv[]) {
	std::string strFileName = "";
	std::string strOutputFileName = "";
	std::string strTemplateFileName = "";


	if(argc == 4){
		strFileName= argv[1];
		strOutputFileName= argv[2];
		strTemplateFileName = argv[3];
	}
	else{
		std::cout << "Usage: DRSDarwin.exe inputFilename.xml outputFilename.xml config.xml" << std::endl;
		exit(1);
	}

	std::cout << "loading file: " << strFileName << std::endl;
	std::cout << "output file: " << strOutputFileName << std::endl;
	std::cout << "config file: " << strTemplateFileName << std::endl;



	std::ifstream configFile(strTemplateFileName.c_str());
	std::stringstream configbuffer;
	configbuffer << configFile.rdbuf();

	std::string config_xml = configbuffer.str() ;

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> configxml_copy(config_xml.begin(), config_xml.end());
    configxml_copy.push_back('\0');

    // only use xml_copy from here on!
    rapidxml::xml_document<> configdoc;
    configdoc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&configxml_copy[0]);
    rapidxml::xml_node<>* configNode = configdoc.first_node("Config");
    rapidxml::xml_node<>* mutationsNode = configNode->first_node("Mutations");
    rapidxml::xml_node<>* binaryNode = mutationsNode->first_node("Binary");
    rapidxml::xml_node<>* integerNode = mutationsNode->first_node("Integer");
    rapidxml::xml_node<>* doubleNode = mutationsNode->first_node("Double");
    rapidxml::xml_node<>* alphanumNode = mutationsNode->first_node("Alphanum");
    rapidxml::xml_node<>* customNode = mutationsNode->first_node("Custom");
    rapidxml::xml_node<>* listNode = mutationsNode->first_node("List");

	std::ifstream t(strFileName.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::string input_xml = buffer.str() ;

	std::ofstream output(strOutputFileName.c_str());


    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* genomeNode = doc.first_node("Genome");
    rapidxml::xml_node<>* chromosomeNode = genomeNode->first_node("Chromosome");


    char* pchValue;


    /**
     * Binary mutations
     */

    rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("BitString")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("FlipBits")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Boundary")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Uniform")->value(pchValue);
/*
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Gaussian")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Gaussian")->first_attribute("sigma")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Duplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Insertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Deletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("Swap")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("GeneDuplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("GeneInsertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("GeneDeletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    binaryNode->first_node("GeneSwap")->value(pchValue);

    /**
     * Integer mutations
     */

    chromosomeNode = chromosomeNode->next_sibling("Chromosome");

    geneNode = chromosomeNode->first_node("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("BitString")->value(pchValue);

/*    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("FlipBits")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Boundary")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Uniform")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Gaussian")->value(pchValue);

   geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Gaussian")->first_attribute("sigma")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Duplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Insertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Deletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("Swap")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("GeneDuplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("GeneInsertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("GeneDeletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    integerNode->first_node("GeneSwap")->value(pchValue);

    /**
     * Double mutations
     */

    chromosomeNode = chromosomeNode->next_sibling("Chromosome");

    geneNode = chromosomeNode->first_node("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("BitString")->value(pchValue);

/*    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("FlipBits")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Boundary")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Uniform")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Gaussian")->value(pchValue);

   geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Gaussian")->first_attribute("sigma")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Duplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Insertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Deletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("Swap")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("GeneDuplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("GeneInsertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("GeneDeletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    doubleNode->first_node("GeneSwap")->value(pchValue);

    /**
     * Alphanum mutations
     */

    chromosomeNode = chromosomeNode->next_sibling("Chromosome");

    geneNode = chromosomeNode->first_node("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("BitString")->value(pchValue);

/*    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("FlipBits")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Boundary")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Uniform")->value(pchValue);
/*
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Gaussian")->value(pchValue);

   geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Gaussian")->first_attribute("sigma")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Duplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Insertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Deletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("Swap")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("GeneDuplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("GeneInsertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("GeneDeletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    alphanumNode->first_node("GeneSwap")->value(pchValue);


    /**
     * custom mutations
     */

    chromosomeNode = chromosomeNode->next_sibling("Chromosome");

    geneNode = chromosomeNode->first_node("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("BitString")->value(pchValue);

/*    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("FlipBits")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Boundary")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Uniform")->value(pchValue);
/*
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Gaussian")->value(pchValue);

   geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Gaussian")->first_attribute("sigma")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Duplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Insertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Deletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("Swap")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("GeneDuplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("GeneInsertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("GeneDeletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    customNode->first_node("GeneSwap")->value(pchValue);


    /**
     * list mutations
     */

    chromosomeNode = chromosomeNode->next_sibling("Chromosome");

    geneNode = chromosomeNode->first_node("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("BitString")->value(pchValue);

/*    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("FlipBits")->value(pchValue);
*/
    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Boundary")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Uniform")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Gaussian")->value(pchValue);

   geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Gaussian")->first_attribute("sigma")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Duplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Insertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Deletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("Swap")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("GeneDuplication")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("GeneInsertion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("GeneDeletion")->value(pchValue);

    geneNode = geneNode->next_sibling("Gene");
    pchValue = doc.allocate_string(geneNode->value());
    listNode->first_node("GeneSwap")->value(pchValue);



	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), configdoc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	output << xml_as_string;
    output.close();
    return 0;

}
