/*
 * Genome.h
 *
 *  Created on: 6-feb.-2012
 *      Author: Skidzobolder
 */

#ifndef GENOME_H_
#define GENOME_H_

#include <string>
#include <iostream>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

class Genome
{
private:
	rapidxml::xml_document<> m_Genome;



public:


    Genome() // default constructor
    {


    }

    void load(std::string strFileName);
    void traverse_xml(const std::string& input_xml);

    void newGenome(std::string &strType);
    void addChromosome(const char* chId );
    void addGene(std::string &strId);

    std::string GetGenome();

};


#endif /* GENOME_H_ */
