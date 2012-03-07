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

std::string	Recombination::RecombinedGenomeXML(){



	Genome newGenome;
    newGenome.newGenome("next generation");

    std::string newGenomeXML = newGenome.GetXML();
    std::vector<char> xml_copyNewGenome(newGenomeXML.begin(), newGenomeXML.end());
    xml_copyNewGenome.push_back('\0');

    rapidxml::xml_document<> docNewGenome;
    docNewGenome.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copyNewGenome[0]);

    rapidxml::xml_node<>* newRootNode = docNewGenome.first_node("Genome");

    rapidxml::xml_document<>* paDocs = new rapidxml::xml_document<>[vstrParents.size()];	//all documents need to be in an array, otherwise the clonedNode contains garbage
    std::vector<char>* xml_copies = new std::vector<char>[vstrParents.size()];

    for(unsigned int i = 0; i < vstrParents.size(); i++){
    	xml_copies[i].assign(vstrParents[i].begin(), vstrParents[i].end());
    	xml_copies[i].push_back('\0');
    	paDocs[i].parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copies[i][0]);

    }

	int nChromosomes = 0;
	//count genes
	rapidxml::xml_node<>* tmpRootNode = paDocs[0].first_node("Genome");
	for (rapidxml::xml_node<>* chromosomeNode = tmpRootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome")){
		nChromosomes++;
	}

	for(int i = 0; i < nChromosomes; i++){
		int nLow = 0;
		int nHigh = vstrParents.size()-1;
		int parent =  (rand() % (nHigh - nLow + 1)) + nLow;

	    rapidxml::xml_node<>* rootNode = paDocs[parent].first_node("Genome");
	    rapidxml::xml_node<>* chromosomeNode = rootNode->first_node("Chromosome");

	    for(int j = 0; j < i; j++){
	    	chromosomeNode = chromosomeNode->next_sibling("Chromosome");		//go to nth chromosome of this parent
	    }

	    rapidxml::xml_node<>* clonedNode = docNewGenome.allocate_node(rapidxml::node_element);
	    clonedNode = paDocs[parent].clone_node(chromosomeNode);

	    newRootNode->append_node(clonedNode);

	}

	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), docNewGenome);


	delete[] paDocs;	//clean up memory
	delete[] xml_copies;

	return xml_as_string;
}

void Recombination::PrintRecombination(){
	std::cout << "recombination contains " << vstrParents.size() << " parents" << std::endl;

	for(unsigned int i = 0; i < vstrParents.size(); i++){
		std::cout << vstrParents[i] << std::endl;
	}


}
