/*
 * Evolver.h
 *
 *  Created on: 3-feb.-2012
 *      Author: Skidzobolder
 */

#ifndef EVOLVER_H_
#define EVOLVER_H_

#include <string>

class Evolver
{
private:
    int m_nPopulationSize;		//total number of children in every epoch
    std::string m_strTitle;

public:
    Evolver() // default constructor
    {
         m_nPopulationSize = 100;
         m_strTitle = "mijn titel2";
         std::cout << "Evolver created" << std::endl;
    }

    int GetPopulationSize() { return m_nPopulationSize; }
    std::string GetTitle() { return m_strTitle; }
   // double GetFraction() { return static_cast<double>(m_nNumerator) / m_nDenominator; }
};


#endif /* EVOLVER_H_ */
