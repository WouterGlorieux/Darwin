//============================================================================
// Name        : DTCRandomFitness.cpp
// Author      : Wouter Glorieux
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main() {
	  /* initialize random seed: */
	srand ( time(0) );

	int nLow = 0;
	int nHigh = RAND_MAX;
	int nRandom = 0;

	//for(int i = 0; i < 100; i++){
		nRandom =  (rand() % (nHigh - nLow + 1)) + nLow;
    	//std::cout << nRandom << std::endl;
	//}

	return nRandom;
}
