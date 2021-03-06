/*
 * Encoding.h
 *
 *  Created on: 21-feb.-2012
 *      Author: woutergl
 */

#ifndef ENCODING_H_
#define ENCODING_H_

#include "Globals.h"

class Encoding
{
private:



public:

    Encoding() // default constructor
    {    }
    virtual ~Encoding() // default deconstructor
    {    }

    virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);

};

class BinaryEncoding : public Encoding
{
private:

	int m_nbits;	// number of random bits

public:

	BinaryEncoding() // default constructor
    {
		m_nbits = 64;	//set default nBits to 64

    }
	virtual ~BinaryEncoding() // default deconstructor
    {    }

	virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);

};

class IntegerEncoding : public Encoding
{
private:



public:

	IntegerEncoding() // default constructor
    {    }
    virtual ~IntegerEncoding() // default deconstructor
    {    }

    virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);

};

class DoubleEncoding : public Encoding
{
private:



public:

	DoubleEncoding() // default constructor
    {    }
    virtual ~DoubleEncoding() // default deconstructor
    {    }

    virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);

};


class AlphanumEncoding : public Encoding
{
private:

	std::vector<char> m_vChars;

public:

	AlphanumEncoding() // default constructor
    {
		std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		std::copy ( characters.begin(), characters.end(), std::back_inserter ( m_vChars ) );
    }
    virtual ~AlphanumEncoding() // default deconstructor
    {    }

    virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);
    std::vector<char> GetChars(){ return m_vChars; }

};

class CustomEncoding : public Encoding
{
private:

	std::vector<char> m_vChars;

public:

	CustomEncoding() // default constructor
    {
		m_vChars.push_back(' ');	//add space in case there is no custom character set, will be cleared when characters are set
    }
    virtual ~CustomEncoding() // default deconstructor
    {    }

    virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);

    void SetChars(std::string characters);
    std::vector<char> GetChars(){ return m_vChars; }
};


class ListEncoding : public Encoding
{
private:



public:

	ListEncoding() // default constructor
    {    }
	virtual ~ListEncoding() // default deconstructor
    {    }

    virtual std::string RandomData(rapidxml::xml_node<>* chromosomeNode);

};

#endif /* ENCODING_H_ */
