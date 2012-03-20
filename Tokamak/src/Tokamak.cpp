//============================================================================
// Name        : Tokamak.cpp
// Author      : Skidzobolder
// Version     :
// Copyright   : 
// Description : Translates tokamak genomes into text-file containing the 3 parameters
//============================================================================

#include <iostream>
#include <String>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
#include <limits>
#include "rapidxml.hpp"


int main(int argc, char *argv[]) {
	std::string strFileName = "";

	if(argc == 2 || argc == 3){
		strFileName= argv[1];
	}

	std::cout << "loading file: " << strFileName << std::endl;
	std::ifstream t(strFileName.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::string input_xml = buffer.str() ;

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

    double dPower = 0.0;
    double dMagnetic = 0.0;
    double dPlasma = 0.0;

    /***********************************************************************************************************************
     * binary
     ***********************************************************************************************************************/

    rapidxml::xml_node<>* intNode;
    rapidxml::xml_node<>* decNode;

    unsigned long lInt;
    unsigned long lDec;

    std::string strBinary1;
    std::string strBinary2;

    rapidxml::xml_node<>* powerNode = rootNode->first_node("Chromosome");
    rapidxml::xml_node<>* magneticNode = powerNode->next_sibling("Chromosome");
    rapidxml::xml_node<>* plasmaNode = magneticNode->next_sibling("Chromosome");

    std::stringstream ss, ss2, ss3;

    /**
     * Power
     */
    intNode = powerNode->first_node("Gene");
    strBinary1 = intNode->value() ;
    lInt = std::bitset<std::numeric_limits<unsigned long>::digits>(strBinary1).to_ulong();

    decNode = intNode->next_sibling("Gene");
    strBinary2 = decNode->value() ;
    lDec = std::bitset<std::numeric_limits<unsigned long>::digits>(strBinary2).to_ulong();

    if(lDec == 255)
    	lDec = 0;

    if(lInt == 255){
    	lDec = 0;
    }

    ss << lInt*100/255 << "." << lDec*100/255;
    dPower = atof(ss.str().c_str());


    /**
     * Magnetic
     */
    intNode = magneticNode->first_node("Gene");
    strBinary1 = intNode->value() ;
    lInt = std::bitset<std::numeric_limits<unsigned long>::digits>(strBinary1).to_ulong();


    decNode = intNode->next_sibling("Gene");
    strBinary2 = decNode->value() ;
    lDec = std::bitset<std::numeric_limits<unsigned long>::digits>(strBinary2).to_ulong();

    if(lDec == 255)
    	lDec = 0;

    if(lInt == 255){
    	lDec = 0;
    }
    ss.str("");
    ss << lInt*100/255 << "." << lDec*100/255;
    dMagnetic = atof(ss.str().c_str());

    /**
     * Plasma
     */
    intNode = plasmaNode->first_node("Gene");
    strBinary1 = intNode->value() ;
    lInt = std::bitset<std::numeric_limits<unsigned long>::digits>(strBinary1).to_ulong();


    decNode = intNode->next_sibling("Gene");
    strBinary2 = decNode->value() ;
    lDec = std::bitset<std::numeric_limits<unsigned long>::digits>(strBinary2).to_ulong();

    if(lDec == 255)
    	lDec = 0;

    if(lInt == 255){
    	lDec = 0;
    }
    ss.str("");
    ss << lInt*100/255 << "." << lDec*100/255;
    dPlasma = atof(ss.str().c_str());



    std::cout << dPower << " " << dMagnetic << " " << dPlasma << std::endl;



    /***********************************************************************************************************************
     * integer
     ***********************************************************************************************************************/


    /***********************************************************************************************************************
     * double
     ***********************************************************************************************************************/


    /***********************************************************************************************************************
     * alphanum
     ***********************************************************************************************************************/


    /***********************************************************************************************************************
     * custom
     ***********************************************************************************************************************/

    /***********************************************************************************************************************
     * list
     ***********************************************************************************************************************/



	return 0;
}
