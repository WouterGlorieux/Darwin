/*
 * Recombination.h
 *
 *  Created on: 16-feb.-2012
 *      Author: woutergl
 */

#ifndef RECOMBINATION_H_
#define RECOMBINATION_H_

#include "Globals.h"


class Recombination
{
private:

	std::vector<std::string> vstrParents;


public:

    Recombination() // default constructor
    {


    }


    void Clear();

    void AddParent(const std::string& input_xml);

    std::string	RecombinedGenomeXML();

};


#endif /* RECOMBINATION_H_ */