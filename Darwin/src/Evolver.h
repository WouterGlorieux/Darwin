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

    std::string m_strTitle;			//Title of this job
    std::string m_strDescription; 	//detailed description of this job

    int m_nPopulationSize;			//total number of children in every epoch
    int m_nMaxGenerations;        		//maximum number of generations to calculate (-1 for unlimited)

public:
    Evolver() // default constructor
    {
         m_nPopulationSize = 0;
         m_strTitle = "";

    }

    int GetPopulationSize() { return m_nPopulationSize; }
    std::string GetTitle() { return m_strTitle; }

    void readConfig(std::string strFileName);
    void traverse_xml(const std::string& input_xml);
    void printSettings();

    void start();


};


#endif /* EVOLVER_H_ */
