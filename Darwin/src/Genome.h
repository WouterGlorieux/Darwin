/*
 * Genome.h
 *
 *  Created on: 6-feb.-2012
 *      Author: Skidzobolder
 */

#ifndef GENOME_H_
#define GENOME_H_

#include "Globals.h"
#include "Encoding.h"
#include "Mutation.h"
#include "MutationChance.h"
#include "Vertices.h"
#include "Edges.h"


class Genome
{
private:

	std::string m_strXML;
	void FillGenes(rapidxml::xml_document<>& doc, rapidxml::xml_node<>* chromosomeNode, Encoding& encoding);
	void GeneMutations(rapidxml::xml_document<>& doc, rapidxml::xml_node<>* geneNode, Mutation& mutation, MutationChance mutationChance);
	void ChromosomeMutations(rapidxml::xml_node<>* chromosomeNode, ChromosomeMutation& mutation, MutationChance mutationChance);

public:

    Genome() // default constructor
    {


    }
    ~Genome() // default deconstructor
    {
    	//std::cout << "genome class destroyed" << std::endl;

    }

    void newGenome(const char* pchId );
    void addChromosome(const char* pchId , EncodingType encoding);
    void addGene(std::string strChromosomeId );

    void AddVertices(std::string strChromosomeId, std::vector<Vertex> vertices);
    void AddEdges(std::string strChromosomeId, std::vector<Edge> edges);

    void addChromosomeAttribute(std::string strChromosomeId, std::string strName, std::string strValue);
    void addGeneAttribute(std::string strChromosomeId, std::string strGeneId, std::string strName, std::string strValue);

    void FillWithRandomData();
    void DoMutations(MutationChances mutationChances);

    void Save(rapidxml::xml_document<>& doc);
    void SetXML(std::string input_xml);
    std::string GetXML() {return m_strXML;}

    int GetGeneration();
    void SetFitness(double fitness);
};


#endif /* GENOME_H_ */
