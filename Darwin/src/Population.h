/*
 * Population.h
 *
 *  Created on: 3-feb.-2012
 *      Author: woutergl
 */

#ifndef POPULATION_H_
#define POPULATION_H_


#include "Globals.h"

#include "Genome.h"


class Population
{
private:
	GenomeType m_eGenomeType;
	double m_dFitness;

public:

	Genome cGenome;

    Population() // default constructor
    {

    }

    void randomGenome();	//fills the genome with random data
    void initGenome();

    void initTokamak();

    void SetGenomeType(GenomeType eGenomeType) {m_eGenomeType = eGenomeType; }

    GenomeType GetGenomeType() { return m_eGenomeType; }

    double GetFitness() { return m_dFitness; }

    void CalcFitness();
    void SetGenome(const std::string& input_xml);

    void DoMutations(MutationChances mutationChances);



};



#endif /* Population_H_ */
