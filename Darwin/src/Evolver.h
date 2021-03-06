/*
 * Evolver.h
 *
 *  Created on: 3-feb.-2012
 *      Author: Skidzobolder
 */

#ifndef EVOLVER_H_
#define EVOLVER_H_

#include "Globals.h"

#include "Genome.h"
#include "Population.h"
#include "Recombination.h"
#include "MutationChance.h"

#include <process.h>

class Evolver
{
private:

	std::string m_strPath; 				//Path to working directory
	std::string m_strSavePath;       	//Path to save directory
	std::string m_strChampionsPath;   	//Path to directory with genomes with highest fitness of each generation
	std::string m_strCandidatesPath;    //Path to directory with candidates

	std::string m_strTemplate;			//filename of genome template xml
	std::string m_strRosetta;			//filename of rosetta exe
	std::string m_strRosettaArgs; 		//optional arguments for rosetta exe
	std::string m_strCandidateExtension; //filename extension of the candidates

	std::vector<TestChamber> m_vsTestChambers; //vector containing the testchambers

	int m_nPeriodicSave;				//Save every n generations

    std::string m_strTitle;			//Title of this job
    std::string m_strDescription; 	//detailed description of this job
    GenomeType m_eGenomeType;       //Type of genomes for this job

    int m_nPopulationSize;			//total number of offspring in every generation
    int m_nMaxGenerations;        	//maximum number of generations to calculate (-1 for unlimited)
    int m_nMaxTimeTotal;			//maximum time in seconds for total evolution
    int m_nMaxTimeGeneration;		//maximum time in seconds for each generation
    int m_nStagnation;				//if n generations with the same highest fitness occur after each other, the evolution has stagnated and will be stopped
    double m_dTargetFitness;		//when a genome with a fitness higher then this is found, the evolution stops
    int m_nMaxParents;              //maximum number of parents for recombination (must be greater of equal to 1)
    RecombinationType m_eRecombination;  //Method used to pick parents for recombination
    int m_nTournamentSize;			//number of genomes selected for each tournament

    double m_dTruncation  ;         //percentage of population that gets to have offspring (0% -> 100%) (100%: every genome has offspring)
    NormalizationType m_eNormalization; //Normalization method used in truncation

    bool m_bElitism;				//Elitism enabled or not?

    int m_nGeneration;
    int m_nStartingGeneration;

    double m_dHighestFitness;
    std::vector<double> m_vdFitness; 		//a vector with the highest fitness of each generation
    std::vector<double> m_vdGenerationTime; 	//a vector with the time in seconds it took to calculate each generation

    Recombination m_cRecombination;

    MutationChance SetMutationChance(rapidxml::xml_node<>* node );
    MutationChance GetMutationChance(EncodingType encodingType);
    MutationChances sMutationChances;


    void RWS(std::vector<Parent> selection, Population* population);
    void SUS(std::vector<Parent> selection, Population* population);
    void Tournament(std::vector<Parent> selection, Population* population);

    bool DoNextGeneration();

public:
    Evolver() // default constructor
    {
    	 srand(time(0)); // set initial seed value to system clock
         m_nPopulationSize = 0;
         m_strTitle = "";

    }

    int GetPopulationSize() { return m_nPopulationSize; }
    std::string GetTitle() { return m_strTitle; }
    std::string GetPath() { return m_strPath; }

    void readConfig(std::string strFileName);
    void traverse_xml(const std::string& input_xml);
    void printSettings();
    void printMutationChance(MutationChance mutationChance);

    int start(bool loadLastSave);

    std::vector<Parent> MakeSelection(Population* population);

    void TranslateGenomes(std::string extension);

    int SaveChampion(Population* champion);
    int SaveFinalSolution(Population* champion);
    int SaveGeneration(Population* population);

    int SaveProgress(Population* champion);

};




#endif /* EVOLVER_H_ */
