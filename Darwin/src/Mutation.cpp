/*
 * Mutation.cpp
 *
 *  Created on: 3-feb.-2012
 *      Author: woutergl
 */

#include "Mutation.h"


/***************************************************************************************************************
 * Base Class Mutation
 ***************************************************************************************************************/

std::string Mutation::BitString(){
	return "";
}
std::string Mutation::FlipBits(){
	return "";
}
std::string Mutation::Boundary(){
	return "";
}
std::string Mutation::Uniform(){
	return "";
}
std::string Mutation::Gaussian(){
	return "";
}
std::string Mutation::Duplication(){
	return "";
}
std::string Mutation::Deletion(){
	return "";
}
std::string Mutation::Insertion(){
	return "";
}


/***************************************************************************************************************
 * Derived Class BitMutation
 ***************************************************************************************************************/

std::string BitMutation::BitString(){
	std::string strValue = m_Node->value();

	int nRandom = rand() % strValue.size();
	(strValue.at(nRandom) =='1')?strValue.at(nRandom) = '0':strValue.at(nRandom) = '1';

	return strValue;
}
std::string BitMutation::FlipBits(){
	std::string strValue = m_Node->value();

	for(unsigned int i = 0; i < strValue.size(); i++){
		(strValue.at(i) =='1')?strValue.at(i) = '0':strValue.at(i) = '1';
	}

	return strValue;
}
std::string BitMutation::Boundary(){

	std::string strValue = m_Node->value();
	std::stringstream ss;//create a stringstream

	int bit = rand() % 2;

	for(unsigned int i = 0; i < strValue.size(); i++){
		ss << bit;//add bit to the stream
	}

	return ss.str();//return a string with the contents of the stream
}
std::string BitMutation::Uniform(){
	BinaryEncoding cBinaryEncoding;
	return cBinaryEncoding.RandomData(m_Node);
}
std::string BitMutation::Gaussian(){

	std::cout << box_muller(0, 2.0) << std::endl;
	return "";
}
std::string BitMutation::Duplication(){
	std::string strValue = m_Node->value();


	//duplicate a random part of the string
	int nBegin = rand() % strValue.size();
	int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
	strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin

	//if there is a bits attribute, cut off the string at that length
	if(m_Node->first_attribute("bits")){
		int bits = atoi(m_Node->first_attribute("bits")->value());
		strValue = strValue.substr(0, bits);
	}

	return strValue;
}
std::string BitMutation::Deletion(){
	std::string strValue = m_Node->value();

	//delete a random part of the string
	int nBegin = rand() % strValue.size();
	int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
	strValue = strValue.erase(nBegin, nEnd-nBegin+1);

	//if there is a bits attribute, fill the rest of string with random bits
	if(m_Node->first_attribute("bits")){
		std::stringstream ss;//create a stringstream
		int bit;
		for(int i = 0; i < (nEnd-nBegin+1); i++){
			bit = rand() % 2;
			ss << bit;//add bit to the stream
		}
		strValue.append(ss.str());
	}

	return strValue;
}
std::string BitMutation::Insertion(){
	std::string strValue = m_Node->value();

	//insert random bits into the string
	int nBegin = rand() % strValue.size();
	int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;

	std::stringstream ss;//create a stringstream
	int bit;

	for(int i = 0; i < (nEnd-nBegin+1); i++){
		bit = rand() % 2;
		ss << bit;//add bit to the stream
	}

	strValue.insert(nBegin, ss.str()); // insert ss.str() at index nBegin

	//if there is a bits attribute, cut off the string at that length
	if(m_Node->first_attribute("bits")){
		int bits = atoi(m_Node->first_attribute("bits")->value());
		strValue = strValue.substr(0, bits);
	}

	return strValue;
}


/***************************************************************************************************************
 * Derived Class IntegerMutation
 ***************************************************************************************************************/
std::string IntegerMutation::BitString(){
	return "";
}
std::string IntegerMutation::FlipBits(){
	return "";
}
std::string IntegerMutation::Boundary(){
	return "";
}
std::string IntegerMutation::Uniform(){
	return "";
}
std::string IntegerMutation::Gaussian(){
	return "";
}
std::string IntegerMutation::Duplication(){
	return "";
}
std::string IntegerMutation::Deletion(){
	return "";
}
std::string IntegerMutation::Insertion(){
	return "";
}


/***************************************************************************************************************
 * Derived Class DoubleMutation
 ***************************************************************************************************************/
std::string DoubleMutation::BitString(){
	return "";
}
std::string DoubleMutation::FlipBits(){
	return "";
}
std::string DoubleMutation::Boundary(){
	return "";
}
std::string DoubleMutation::Uniform(){
	return "";
}
std::string DoubleMutation::Gaussian(){
	return "";
}
std::string DoubleMutation::Duplication(){
	return "";
}
std::string DoubleMutation::Deletion(){
	return "";
}
std::string DoubleMutation::Insertion(){
	return "";
}


/***************************************************************************************************************
 * Derived Class AlphanumMutation
 ***************************************************************************************************************/
std::string AlphanumMutation::BitString(){
	return "";
}
std::string AlphanumMutation::FlipBits(){
	return "";
}
std::string AlphanumMutation::Boundary(){
	return "";
}
std::string AlphanumMutation::Uniform(){
	return "";
}
std::string AlphanumMutation::Gaussian(){
	return "";
}
std::string AlphanumMutation::Duplication(){
	return "";
}
std::string AlphanumMutation::Deletion(){
	return "";
}
std::string AlphanumMutation::Insertion(){
	return "";
}


/***************************************************************************************************************
 * Derived Class CustomMutation
 ***************************************************************************************************************/
std::string CustomMutation::BitString(){
	return "";
}
std::string CustomMutation::FlipBits(){
	return "";
}
std::string CustomMutation::Boundary(){
	return "";
}
std::string CustomMutation::Uniform(){
	return "";
}
std::string CustomMutation::Gaussian(){
	return "";
}
std::string CustomMutation::Duplication(){
	return "";
}
std::string CustomMutation::Deletion(){
	return "";
}
std::string CustomMutation::Insertion(){
	return "";
}


/***************************************************************************************************************
 * Derived Class TreeMutation
 ***************************************************************************************************************/
std::string TreeMutation::BitString(){
	return "";
}
std::string TreeMutation::FlipBits(){
	return "";
}
std::string TreeMutation::Boundary(){
	return "";
}
std::string TreeMutation::Uniform(){
	return "";
}
std::string TreeMutation::Gaussian(){
	return "";
}
std::string TreeMutation::Duplication(){
	return "";
}
std::string TreeMutation::Deletion(){
	return "";
}
std::string TreeMutation::Insertion(){
	return "";
}

/***************************************************************************************************************
 boxmuller.c           Implements the Polar form of the Box-Muller
                         Transformation

                      (c) Copyright 1994, Everett F. Carter Jr.
                          Permission is granted by the author to use
			  this software for any application provided this
			  copyright notice is preserved.

*/

/* ranf() is uniform in 0..1 */
float ranf(){

	int nLow = 0;
	int nHigh = 10000;
	int data = (rand() % (nHigh - nLow + 1)) + nLow;

	return (float)data/nHigh;
}


float box_muller(float m, float s)	/* normal random variate generator */
{				        /* mean m, standard deviation s */
	float x1, x2, w, y1;
	static float y2;
	static int use_last = 0;

	if (use_last)		        /* use value from previous call */
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do {
			x1 = 2.0 * ranf() - 1.0;
			x2 = 2.0 * ranf() - 1.0;
			w = x1 * x1 + x2 * x2;
		} while ( w >= 1.0 );

		w = sqrt( (-2.0 * log( w ) ) / w );
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return( m + y1 * s );
}
