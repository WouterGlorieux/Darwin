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
	        case GENOMETYPE_TOKAMAK:
	            std::cout << "Initializing steady state tokamak genome" << std::endl;
	            initTokamak();
	            break;
	        case GENOMETYPE_TOKAMAKTIME:
	            std::cout << "Initializing time dependent tokamak genome" << std::endl;
	            initTokamak();
	            break;

	        default:
	            std::cout << "Unknown genome type" << std::endl;
	            break;
	    }


}

void Rosetta::initTokamak(){


	std::string strType = "Tokamak steady state";

	m_cGenome.newGenome(strType);

	m_cGenome.addChromosome("Auxiliary Heating Power");
	m_cGenome.addGene("1", "Auxiliary Heating Power");

	m_cGenome.addChromosome("Magnetic Field");
	m_cGenome.addGene("1", "Magnetic Field");

	m_cGenome.addChromosome("Plasma Density");
	m_cGenome.addGene("1", "Plasma Density");

	std::cout << m_cGenome.GetGenomeXML() << std::endl;

}

void Rosetta::CalcFitness(){

	int nLow = 0;
	int nHigh = 100;

	m_dFitness = (rand() % (nHigh - nLow + 1)) + nLow;

}

