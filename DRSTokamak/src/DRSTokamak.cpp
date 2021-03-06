//============================================================================
// Name        : DRSTokamak.cpp
// Author      : Wouter Glorieux
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include "rapidxml.hpp"
#include <fstream>
#include <sstream>


using namespace std;


int main(int argc, char *argv[]) {
	std::string strFileName = "";
	std::string strOutputFileName = "";


	if(argc == 3){
		strFileName= argv[1];
		strOutputFileName= argv[2];
	}
	else{
		std::cout << "Usage: Tokamak.exe inputFilename outputFilename" << std::endl;
		exit(1);
	}

	//std::cout << "loading file: " << strFileName << std::endl;
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
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

    double dPower = 0.0;
    double dMagnetic = 0.0;
    double dPlasma = 0.0;

    //the chromosomes are encoded to have a value between 0 and 100, so we need a multiplier to put the value in the correct range
    double dPowerMultiplier  = 1;		//power is from 0 to 100
    double dMagneticMultiplier  = 0.14; //magnetic is from 0 to 14
    double dPlasmaMultiplier  = 0.06;   //plasma is from 0 to 6


    /***********************************************************************************************************************
     * double
     ***********************************************************************************************************************/

    rapidxml::xml_node<>* powerNode = rootNode->first_node("Chromosome");
    rapidxml::xml_node<>* magneticNode = powerNode->next_sibling("Chromosome");
    rapidxml::xml_node<>* plasmaNode = magneticNode->next_sibling("Chromosome");

    rapidxml::xml_node<>* powerGene = powerNode->first_node("Gene");
    rapidxml::xml_node<>* magneticGene = magneticNode->first_node("Gene");
    rapidxml::xml_node<>* plasmaGene = plasmaNode->first_node("Gene");

	dPower = atof(powerGene->value()) * dPowerMultiplier;
	dMagnetic = atof(magneticGene->value()) * dMagneticMultiplier;
	dPlasma = atof(plasmaGene->value()) * dPlasmaMultiplier;

	output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;

	while(powerGene->next_sibling("Gene")) {
	    powerGene = powerGene->next_sibling("Gene");
	    magneticGene = magneticGene->next_sibling("Gene");
	    plasmaGene = plasmaGene->next_sibling("Gene");

    	dPower = atof(powerGene->value()) * dPowerMultiplier;
    	dMagnetic = atof(magneticGene->value()) * dMagneticMultiplier;
    	dPlasma = atof(plasmaGene->value()) * dPlasmaMultiplier;

    	output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;
    }

    output.close();
    return 0;

}

