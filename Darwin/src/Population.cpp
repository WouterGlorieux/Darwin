/*
 * Population.cpp
 *
 *  Created on: 3-feb.-2012
 *      Author: woutergl
 */

#include "Population.h"


void Population::initGenome(std::string genomeTemplate){

	std::ifstream t(genomeTemplate.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string input_xml = buffer.str();

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* genomeNode = doc.first_node("Genome");
	for (rapidxml::xml_node<>* chromosomeNode = genomeNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{
		int nGenes = 0;
		if(chromosomeNode->first_attribute("genes")){
			nGenes = atoi(chromosomeNode->first_attribute("genes")->value());
		}
		else{
			nGenes = rand() % 10;
		}

		for(int i = 0 ; i < nGenes; i++){
		    // gene node
			rapidxml::xml_node<>* geneNode = doc.allocate_node(rapidxml::node_element, "Gene");
			chromosomeNode->append_node(geneNode);
		}

	}


	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	cGenome.SetXML(xml_as_string);

}

/*void Population::initTokamak(){

	cGenome.newGenome("Tokamak steady state");

	cGenome.addChromosome("Auxiliary Heating Power", ENCODING_BINARY);
	cGenome.addChromosomeAttribute("Auxiliary Heating Power", "bits", "16");
	cGenome.addGene("1", "Auxiliary Heating Power");
	cGenome.addGene("2", "Auxiliary Heating Power");
	cGenome.addGene("3", "Auxiliary Heating Power");


	cGenome.addChromosome("Magnetic Field", ENCODING_INTEGER);
	cGenome.addChromosomeAttribute("Magnetic Field", "min", "-1000");
	cGenome.addChromosomeAttribute("Magnetic Field", "max", "1000");
	cGenome.addGene("1", "Magnetic Field");
	cGenome.addGene("2", "Magnetic Field");
	cGenome.addGene("3", "Magnetic Field");

	cGenome.addChromosome("Plasma Density", ENCODING_DOUBLE);
	cGenome.addChromosomeAttribute("Plasma Density", "min", "-1000");
	cGenome.addChromosomeAttribute("Plasma Density", "max", "1000");
	cGenome.addChromosomeAttribute("Plasma Density",  "decimals", "5");
	cGenome.addGene("1", "Plasma Density");
	cGenome.addGene("2", "Plasma Density");
	cGenome.addGene("3", "Plasma Density");

	cGenome.addChromosome("Auxiliary Heating Power2", ENCODING_ALPHANUM);
	cGenome.addChromosomeAttribute("Auxiliary Heating Power2", "maxChars", "50");
	cGenome.addGene("1", "Auxiliary Heating Power2");
	cGenome.addGene("2", "Auxiliary Heating Power2");
	cGenome.addGene("3", "Auxiliary Heating Power2");

	cGenome.addChromosome("Magnetic Field2", ENCODING_CUSTOM);
	cGenome.addChromosomeAttribute("Magnetic Field2", "chars", "ACGT");
	cGenome.addChromosomeAttribute("Magnetic Field2", "maxChars", "50");
	cGenome.addGene("1", "Magnetic Field2");
	cGenome.addGene("2", "Magnetic Field2");
	cGenome.addGene("3", "Magnetic Field2");

	cGenome.addChromosome("Magnetic Field3", ENCODING_LIST);
	cGenome.addChromosomeAttribute("Magnetic Field3",  "elements", "3");
	cGenome.addChromosomeAttribute("Magnetic Field3", "min", "-1000");
	cGenome.addChromosomeAttribute("Magnetic Field3", "max", "1000");
	cGenome.addChromosomeAttribute("Magnetic Field3",  "decimals", "5");
	cGenome.addGene("1", "Magnetic Field3");
	cGenome.addGene("2", "Magnetic Field3");
	cGenome.addGene("3", "Magnetic Field3");

	cGenome.addChromosome("tree graph", ENCODING_TREE);

	Vertex sVertex;
	std::vector<Vertex> vsVertices;

	sVertex.nX = 1.61754;
	sVertex.nY = 3.68479;
	vsVertices.push_back(sVertex);
	sVertex.nX = 9.18746;
	sVertex.nY = 6.16434;
	vsVertices.push_back(sVertex);
	sVertex.nX = 5.62784;
	sVertex.nY = 7.16856;
	vsVertices.push_back(sVertex);
	sVertex.nX = 2.95121;
	sVertex.nY = 1.65446;
	vsVertices.push_back(sVertex);
	sVertex.nX = 8.36979;
	sVertex.nY = 4.15946;
	vsVertices.push_back(sVertex);

	cGenome.AddVertices("tree graph", vsVertices);
	cGenome.addChromosomeAttribute("tree graph", "vertices", "5");
	cGenome.addGene("1", "tree graph");



}*/

void Population::CalcFitness(std::vector<TestChamber> aperture, std::string candidate){

	std::string strTestChamber;
	std::string strArguments;

	double dFitness = 0;

	for(unsigned int i = 0; i < aperture.size(); i++){
		strTestChamber = aperture.at(i).strFileName;
		strArguments = aperture.at(i).strArguments;
		int nFitness = spawnl(P_WAIT, strTestChamber.c_str(), strTestChamber.c_str(), candidate.c_str(), strArguments.c_str() , NULL);

		dFitness += (nFitness * aperture.at(i).dMultiplier);
	}

	m_dFitness = dFitness;

}

void Population::SetGenome(const std::string& input_xml){
	//cGenome.SetGenomeXML(input_xml);
	cGenome.SetXML(input_xml);
}

void Population::randomGenome(){
	cGenome.FillWithRandomData();
}

void Population::DoMutations(MutationChances mutationChances){
	cGenome.DoMutations(mutationChances);

}
