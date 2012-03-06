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
private:


public:
	rapidxml::xml_node<>* m_Node;

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
};

class BitMutation : public Mutation
{
private:

public:

	BitMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;
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

	IntegerMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;
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

	DoubleMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;

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

	AlphanumMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;

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

	CustomMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;
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

class TreeMutation : public Mutation
{
private:

public:

	TreeMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;
    }

	virtual ~TreeMutation() // default deconstructor
    {    }

    //virtual std::string BitString();
    //virtual std::string FlipBits();
    //virtual std::string Boundary();
    //virtual std::string Uniform();
    //virtual std::string Gaussian(double sigma );
    //virtual std::string Duplication();
    //virtual std::string Deletion();
    //virtual std::string Insertion();
    //virtual std::string Swap();

};

class ListMutation : public Mutation
{
private:

public:

	ListMutation(rapidxml::xml_node<>* node) // default constructor
    {
		m_Node = node;
    }

	virtual ~ListMutation() // default deconstructor
    {    }

    //virtual std::string BitString();
    //virtual std::string FlipBits();
    //virtual std::string Boundary();
    //virtual std::string Uniform();
    //virtual std::string Gaussian(double sigma );
    //virtual std::string Duplication();
    //virtual std::string Deletion();
    //virtual std::string Insertion();
    //virtual std::string Swap();

};


#endif /* MUTATION_H_ */
