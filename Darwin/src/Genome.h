/*
 * Genome.h
 *
 *  Created on: 6-feb.-2012
 *      Author: Skidzobolder
 */

#ifndef GENOME_H_
#define GENOME_H_

#include "Globals.h"

class Genome
{
private:
	rapidxml::xml_document<> m_Genome;

public:

    Genome() // default constructor
    {


    }

    void newGenome(const char* pchId );
    void addChromosome(const char* pchId );
    void addGene(const char* pchId , const char* pchChromosomeId );

    std::string GetGenomeXML();
    void SetGenomeXML(const std::string& input_xml);
};


#endif /* GENOME_H_ */