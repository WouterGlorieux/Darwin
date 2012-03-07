/*
 * Recombination.h
 *
 *  Created on: 16-feb.-2012
 *      Author: woutergl
 */

#ifndef RECOMBINATION_H_
#define RECOMBINATION_H_

#include "Globals.h"

#include "Genome.h"


class Recombination
{
private:

	std::vector<std::string> vstrParents;

public:

    Recombination() // default constructor
    {


    }

    ~Recombination() // default deconstructor
    {
    	//std::cout << "recombination class destroyed" << std::endl;

    }

    void Clear();

    void AddParent(const std::string& input_xml);

    std::string	RecombinedGenomeXML();

    void PrintRecombination();

};


#endif /* RECOMBINATION_H_ */
