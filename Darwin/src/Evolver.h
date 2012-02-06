/*
 * Evolver.h
 *
 *  Created on: 3-feb.-2012
 *      Author: Skidzobolder
 */

#ifndef EVOLVER_H_
#define EVOLVER_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

class Evolver
{
private:
    int m_nPopulationSize;		//total number of children in every epoch
    std::string m_strTitle;		//

public:
    Evolver() // default constructor
    {
         m_nPopulationSize = 100;
         m_strTitle = "mijn titel";
         std::cout << "Evolver created" << std::endl;

    }

    int GetPopulationSize() { return m_nPopulationSize; }
    std::string GetTitle() { return m_strTitle; }

    void readConfig(std::string strFileName);
    void traverse_xml(const std::string& input_xml);


};


#endif /* EVOLVER_H_ */
