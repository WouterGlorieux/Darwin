/*
 * Rosetta.cpp
 *
 *  Created on: 3-feb.-2012
 *      Author: woutergl
 */

#include "Rosetta.h"


void Rosetta::initGenome(){

	switch (m_eGenomeType)
	    {
	        case GENOME_TOKAMAK:
	           // std::cout << "Initializing steady state tokamak genome" << std::endl;
	            initTokamak();
	            break;
	        case GENOME_TOKAMAKTIME:
	           // std::cout << "Initializing time dependent tokamak genome" << std::endl;
	            initTokamak();
	            break;

	        default:
	            std::cout << "Unknown genome type" << std::endl;
	            break;
	    }


}

void Rosetta::initTokamak(){

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



}

void Rosetta::CalcFitness(){

	int nLow = 0;
	int nHigh = RAND_MAX;

	m_dFitness = (rand() % (nHigh - nLow + 1)) + nLow;


}

void Rosetta::SetGenome(const std::string& input_xml){
	//cGenome.SetGenomeXML(input_xml);
	cGenome.SetXML(input_xml);
}

void Rosetta::randomGenome(){
	cGenome.FillWithRandomData();
}

void Rosetta::DoMutations(MutationChances mutationChances){
	cGenome.DoMutations(mutationChances);

}
