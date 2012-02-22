/*
 * Rosetta.h
 *
 *  Created on: 3-feb.-2012
 *      Author: woutergl
 */

#ifndef ROSETTA_H_
#define ROSETTA_H_


#include "Globals.h"

#include "Genome.h"


class Rosetta
{
private:
	GenomeType m_eGenomeType;
	double m_dFitness;

public:

	Genome cGenome;

    Rosetta() // default constructor
    {

    }

    void ModelToGenome();
    void GenomeToModel();

    void randomGenome();	//fills the genome with random data
    void initGenome();

    void initTokamak();

    void SetGenomeType(GenomeType eGenomeType) {m_eGenomeType = eGenomeType; }

    GenomeType GetGenomeType() { return m_eGenomeType; }

    double GetFitness() { return m_dFitness; }

    void CalcFitness();
    void SetGenome(const std::string& input_xml);



};



#endif /* ROSETTA_H_ */
