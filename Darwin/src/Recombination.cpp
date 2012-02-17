/*
 * Recombination.cpp
 *
 *  Created on: 16-feb.-2012
 *      Author: woutergl
 */

#include "Recombination.h"

void Recombination::Clear(){
	vstrParents.clear();
}





void Recombination::AddParent(const std::string& input_xml){
	vstrParents.push_back(input_xml);
}

std::string	Recombination::RecombinedGenomeXML(int chromosomes){
	using namespace rapidxml;

	std::cout << "number of chromosomes: "<< chromosomes << std::endl;

	m_cNewGenome.newGenome("next generation");
    xml_node<>* newRootNode = m_cNewGenome.m_Genome.first_node("Genome");


	for(int i = 0; i < chromosomes; i++){
		int nLow = 0;
		int nHigh = vstrParents.size()-1;
		int parent =  (rand() % (nHigh - nLow + 1)) + nLow;

		std::cout << "adding chromosome " << i << " from parent " << parent << std::endl;

	    // make a safe-to-modify copy of input_xml
	    // (you should never modify the contents of an std::string directly)
	    std::vector<char> xml_copy(vstrParents[parent].begin(), vstrParents[parent].end());
	    xml_copy.push_back('\0');

	    // only use xml_copy from here on!
	    xml_document<> doc;
	    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

	    xml_node<>* rootNode = doc.first_node("Genome");
	    xml_node<>* chromosomeNode = rootNode->first_node("Chromosome");

	    for(int j = 0; j < i; j++){
	    	chromosomeNode = chromosomeNode->next_sibling("Chromosome");		//go to nth chromosome of this parent
	    }

	    xml_node<>* clonedNode = m_cNewGenome.m_Genome.clone_node( chromosomeNode );
	    newRootNode->append_node(clonedNode);


	}

	std::cout << m_cNewGenome.GetGenomeXML();

	return std::string("");
}

void Recombination::PrintRecombination(){
	std::cout << "recombination contains " << vstrParents.size() << " parents" << std::endl;

	for(unsigned int i = 0; i < vstrParents.size(); i++){
		std::cout << vstrParents[i] << std::endl;
	}


}
