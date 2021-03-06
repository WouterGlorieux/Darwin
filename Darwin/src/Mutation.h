/*
 * Mutation.h
 *
 *  Created on: 3-feb.-2012
 *      Author: woutergl
 */

#ifndef MUTATION_H_
#define MUTATION_H_

#include "Globals.h"
#include "Encoding.h"


float ranf();
float box_muller(float m, float s);

class Mutation
{
protected:
	std::string m_strValue;
	rapidxml::xml_node<>* m_ChromosomeNode;

public:

	Mutation() // default constructor
    {	}
    virtual ~Mutation() // default deconstructor
    {    }

	virtual std::string BitString();
    virtual std::string FlipBits();
    virtual std::string Boundary();
    virtual std::string Uniform();
    virtual std::string Gaussian(double sigma);
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();

    std::string ValidateMutation(std::string value);		//checks if mutation is valid, and if necessary modifies the string to make it valid

};

class BitMutation : public Mutation
{
private:

public:

	BitMutation(std::string value, rapidxml::xml_node<>* chromosomeNode) // default constructor
    {
		m_strValue = value;
		m_ChromosomeNode = chromosomeNode;
    }

	virtual ~BitMutation() // default deconstructor
    {    }

    virtual std::string BitString();
    virtual std::string FlipBits();
    virtual std::string Boundary();
    virtual std::string Uniform();
    //virtual std::string Gaussian(double sigma = 1.0);
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();


};

class IntegerMutation : public Mutation
{
private:

public:

	IntegerMutation(std::string value, rapidxml::xml_node<>* chromosomeNode) // default constructor
    {
		m_strValue = value;
		m_ChromosomeNode = chromosomeNode;
    }

	virtual ~IntegerMutation() // default deconstructor
    {    }

    virtual std::string BitString();
    //virtual std::string FlipBits();
    virtual std::string Boundary();
    virtual std::string Uniform();
    virtual std::string Gaussian(double sigma);
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();



};

class DoubleMutation : public Mutation
{
private:

public:

	DoubleMutation(std::string value, rapidxml::xml_node<>* chromosomeNode) // default constructor
    {
		m_strValue = value;
		m_ChromosomeNode = chromosomeNode;

    }

	virtual ~DoubleMutation() // default deconstructor
    {  }

    virtual std::string BitString();
    //virtual std::string FlipBits();
    virtual std::string Boundary();
    virtual std::string Uniform();
    virtual std::string Gaussian(double sigma );
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();



};

class AlphanumMutation : public Mutation
{
private:

public:

	AlphanumMutation(std::string value, rapidxml::xml_node<>* chromosomeNode) // default constructor
    {
		m_strValue = value;
		m_ChromosomeNode = chromosomeNode;

    }

	virtual ~AlphanumMutation() // default deconstructor
    {    }

    virtual std::string BitString();
    //virtual std::string FlipBits();
    //virtual std::string Boundary();
    virtual std::string Uniform();
    //virtual std::string Gaussian(double sigma );
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();



};

class CustomMutation : public Mutation
{
private:

public:

	CustomMutation(std::string value, rapidxml::xml_node<>* chromosomeNode) // default constructor
    {
		m_strValue = value;
		m_ChromosomeNode = chromosomeNode;
    }

	virtual ~CustomMutation() // default deconstructor
    {    }

    virtual std::string BitString();
    //virtual std::string FlipBits();
    //virtual std::string Boundary();
    virtual std::string Uniform();
    //virtual std::string Gaussian(double sigma );
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();



};


class ListMutation : public Mutation
{
private:

public:

	ListMutation(std::string value, rapidxml::xml_node<>* chromosomeNode) // default constructor
    {
		m_strValue = value;
		m_ChromosomeNode = chromosomeNode;
    }

	virtual ~ListMutation() // default deconstructor
    {    }

    virtual std::string BitString();
    //virtual std::string FlipBits();
    virtual std::string Boundary();
    virtual std::string Uniform();
    virtual std::string Gaussian(double sigma );
    virtual std::string Duplication();
    virtual std::string Deletion();
    virtual std::string Insertion();
    virtual std::string Swap();



};

class ChromosomeMutation
{
private:

public:
	rapidxml::xml_node<>* m_Node;

	ChromosomeMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;
    }

	virtual ~ChromosomeMutation() // default deconstructor
    {    }

    rapidxml::xml_node<>* GetGeneNode(int n);

	virtual void Duplication();
	virtual void Deletion();
	virtual void Insertion();
	virtual void Swap();

};


#endif /* MUTATION_H_ */
