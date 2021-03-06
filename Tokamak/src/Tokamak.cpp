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

void StringExplode(std::string str, std::string separator, std::vector<std::string>* results);
double StringToDouble(std::string value);

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

    std::stringstream ss;

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
    dPower = atof(ss.str().c_str()) * dPowerMultiplier;


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
    dMagnetic = atof(ss.str().c_str()) * dMagneticMultiplier;

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
    dPlasma = atof(ss.str().c_str()) * dPlasmaMultiplier;



    output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;



    /***********************************************************************************************************************
     * integer
     ***********************************************************************************************************************/





    int nInt, nDec;
    /**
     * Power
     */
    powerNode = plasmaNode->next_sibling("Chromosome");

    intNode = powerNode->first_node("Gene");
    nInt = atoi(intNode->value());

    powerNode = powerNode->next_sibling("Chromosome");
    decNode = powerNode->first_node("Gene");
    nDec = atoi(decNode->value());

    if(nInt == 100){
    	nDec = 0;
    }

    ss.str("");
    ss << nInt << "." << nDec;
    dPower = atof(ss.str().c_str()) * dPowerMultiplier ;


    /**
     * Magnetic
     */
    magneticNode = powerNode->next_sibling("Chromosome");

    intNode = magneticNode->first_node("Gene");
    nInt = atoi(intNode->value());

    magneticNode = magneticNode->next_sibling("Chromosome");
    decNode = magneticNode->first_node("Gene");
    nDec = atoi(decNode->value());

    if(nInt == 100){
    	nDec = 0;
    }
    ss.str("");
    ss << nInt << "." << nDec;
    dMagnetic = atof(ss.str().c_str()) * dMagneticMultiplier;

    /**
     * Plasma
     */
    plasmaNode = magneticNode->next_sibling("Chromosome");

    intNode = plasmaNode->first_node("Gene");
    nInt = atoi(intNode->value());

    plasmaNode = plasmaNode->next_sibling("Chromosome");
    decNode = plasmaNode->first_node("Gene");
    nDec = atoi(decNode->value());

    if(nInt == 100){
    	nDec = 0;
    }

    ss.str("");
    ss << nInt << "." << nDec;
    dPlasma = atof(ss.str().c_str()) * dPlasmaMultiplier;



    output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;

    /***********************************************************************************************************************
     * double
     ***********************************************************************************************************************/

    powerNode = plasmaNode->next_sibling("Chromosome");
    magneticNode = powerNode->next_sibling("Chromosome");
    plasmaNode = magneticNode->next_sibling("Chromosome");

    dPower = atof(powerNode->first_node("Gene")->value()) * dPowerMultiplier;
    dMagnetic = atof(magneticNode->first_node("Gene")->value()) * dMagneticMultiplier;
    dPlasma = atof(plasmaNode->first_node("Gene")->value()) * dPlasmaMultiplier;

    output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;

    /***********************************************************************************************************************
     * alphanum
     ***********************************************************************************************************************/
    powerNode = plasmaNode->next_sibling("Chromosome");
    magneticNode = powerNode->next_sibling("Chromosome");
    plasmaNode = magneticNode->next_sibling("Chromosome");



    dPower = StringToDouble(powerNode->first_node("Gene")->value()) * dPowerMultiplier;
    dMagnetic = StringToDouble(magneticNode->first_node("Gene")->value()) * dMagneticMultiplier;
    dPlasma = StringToDouble(plasmaNode->first_node("Gene")->value()) * dPlasmaMultiplier;

    output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;

    /***********************************************************************************************************************
     * custom
     ***********************************************************************************************************************/
    powerNode = plasmaNode->next_sibling("Chromosome");
    magneticNode = powerNode->next_sibling("Chromosome");
    plasmaNode = magneticNode->next_sibling("Chromosome");

    dPower = (atof(powerNode->first_node("Gene")->value())/100) * dPowerMultiplier;
    dMagnetic = (atof(magneticNode->first_node("Gene")->value())/100) * dMagneticMultiplier;
    dPlasma = (atof(plasmaNode->first_node("Gene")->value())/100) * dPlasmaMultiplier;

    output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;
    /***********************************************************************************************************************
     * list
     ***********************************************************************************************************************/

    powerNode = plasmaNode->next_sibling("Chromosome");

    std::vector<std::string> vstrData;
	StringExplode(powerNode->first_node("Gene")->value(), "|", &vstrData);
	// vector vstrData now contains each double!

    dPower = atof(vstrData.at(0).c_str()) * dPowerMultiplier;
    dMagnetic = atof(vstrData.at(1).c_str()) * dMagneticMultiplier;
    dPlasma = atof(vstrData.at(2).c_str()) * dPlasmaMultiplier;

    output << dPower << " " << dMagnetic << " " << dPlasma << std::endl;


    output.close();
	return 0;
}

void StringExplode(std::string str, std::string separator, std::vector<std::string>* results){
    std::size_t found;
    found = str.find_first_of(separator);
    while(found != std::string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}


double StringToDouble(std::string value){
	double dValue = 0.0;
	std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


	for(unsigned int i = 0; i < value.size(); i++){
		dValue += characters.find(value.at(i));
	}

	dValue = (dValue / (value.size()*61))*100;

	if(value == ""){
		dValue = 0;
	}

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%.2f", dValue);
	ss << buffer;

	dValue = atof(ss.str().c_str());

	return dValue;
}
