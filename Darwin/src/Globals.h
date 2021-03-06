/*
 * Globals.h
 *
 *  Created on: 9-feb.-2012
 *      Author: woutergl
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <math.h>


#include "rapidxml.hpp"
#include "rapidxml_print.hpp"



enum GenomeType
{
	GENOME_TOKAMAK = 1, //steady state tokamak
	GENOME_TOKAMAKTIME = 2 //time dependent tokamak
};


enum NormalizationType
{
	NORM_PROPORTIONAL = 1,		// normalized fitness is based on proportional fitness
	NORM_RANK = 2,				// normalized fitness is based on rank
	NORM_EQUAL = 3				// normalized fitness is equal for all genomes

};

enum RecombinationType
{
	RECOMBINATION_RWS = 1,			//Roulette Wheel selection
	RECOMBINATION_SUS = 2,			//Stochastic Universal Sampling
	RECOMBINATION_TOURNAMENT = 3	//Tournament selection
};

enum EncodingType
{
	ENCODING_BINARY = 1,			//genes are encoded as binary numbers
	ENCODING_INTEGER = 2,			//genes are encoded as integer numbers
	ENCODING_DOUBLE = 3,			//genes are encoded as numeric values
	ENCODING_ALPHANUM = 4,			//genes are encoded as alphanumeric characters
	ENCODING_CUSTOM = 5,			//genes are encodes as a custom string of characters
	ENCODING_LIST = 6				//genes are encoded as a list of doubles
};

struct Parent
{
    int nIndex;								//index in current population
    double dFitness;						//fitness
    double dNormalizedFitness;				//percentual chance that this parent is selected for reproduction
    double dAccumulatedNormalizedFitness;	//accumulated percentual chance that this parent is selected for reproduction

};

struct TestChamber
{
	std::string strFileName;   //filename of testchamber executable
	std::string strArguments;  //optional arguments
	double dMultiplier;		   //multiplier for score, in case of multiple testchambers the sum of the multipliers must be 1
};

struct Vertex
{
	double nX;
	double nY;
};

struct Edge
{
	int nVertex1;
	int nVertex2;
	double dCost;
};

#endif /* GLOBALS_H_ */
