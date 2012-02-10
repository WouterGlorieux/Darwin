/*
 * Evolver.cpp
 *
 *  Created on: 3-feb.-2012
 *      Author: Skidzobolder
 */

#include "Evolver.h"




void Evolver::readConfig(std::string strFileName)
{
	std::ifstream t(strFileName.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();

	Evolver::traverse_xml(buffer.str());

	Evolver::printSettings();
}

void Evolver::traverse_xml(const std::string& input_xml)
{
	using namespace rapidxml;
    // (input_xml contains the above XML)

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

    xml_node<>* rootNode = doc.first_node("Config");
    m_strTitle = rootNode->first_node("Title")->value();
    m_strDescription = rootNode->first_node("Description")->value();
    m_strPath = rootNode->first_node("DirectoryPath")->value();
    m_eGenomeType = static_cast<GenomeType> (atoi(rootNode->first_node("GenomeType")->value()));

    xml_node<>* settingsNode = rootNode->first_node("Settings");
    m_nPopulationSize = atoi(settingsNode->first_node("PopulationSize")->value());
    m_nMaxGenerations = atoi(settingsNode->first_node("MaxGenerations")->value());



}

void Evolver::printSettings(){
	std::cout << "Config file loaded:" << std::endl;
	std::cout << "Title: " << m_strTitle << std::endl;
	std::cout << "Description: " << m_strDescription << std::endl;
	std::cout << "Directory path: " << m_strPath << std::endl;
	std::cout << "PopulationSize: " << m_nPopulationSize << std::endl;
	std::cout << "Max Generations: " << m_nMaxGenerations << std::endl;


}

void Evolver::start(){

	//create pointer to array of Rosetta objects
	Rosetta *pacRosetta = new Rosetta[m_nPopulationSize];

	//initialize Rosetta objects
	for(int i = 0; i<m_nPopulationSize; i++ ){
		pacRosetta[i].SetGenomeType(m_eGenomeType);
		pacRosetta[i].initGenome();
	}

	//put random data in all genomes

	//create Aperture object

//do until maxGenerations reached

	//calculate fitness
	srand(time(0)); // set initial seed value to system clock
	for(int i = 0; i<m_nPopulationSize; i++ ){
		pacRosetta[i].CalcFitness();
		std::cout << "fitness of " << i << ": " << pacRosetta[i].GetFitness() << std::endl;
	}

	//save state

	//make next generation

	//do mutations
//loop


	delete[] pacRosetta;
}

