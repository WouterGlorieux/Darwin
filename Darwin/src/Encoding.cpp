/*
 * Encoding.cpp
 *
 *  Created on: 21-feb.-2012
 *      Author: woutergl
 */

#include "Encoding.h"

std::string Encoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	return "base encoding";
}

std::string BinaryEncoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	int nMin = 0;
	int nMax = 0;

	//check if there is a "min" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("min")){
		nMin = atoi(chromosomeNode->first_attribute("min")->value());
	}

	//check if there is a "max" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("max")){
		nMax = atoi(chromosomeNode->first_attribute("max")->value());
	}


	m_nbits = (rand() % (nMax - nMin + 1)) + nMin;

	int bit;
	std::stringstream ss;//create a stringstream
	for(int i = 0 ; i < m_nbits ; i++){
		bit = rand() % 2;
		ss << bit;//add number to the stream
	}


	return ss.str();//return a string with the contents of the stream

}


std::string IntegerEncoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	int nLow = 0;
	int nHigh = RAND_MAX;		//default range of rand()

	//check if there is a "min" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("min")){
		nLow = atoi(chromosomeNode->first_attribute("min")->value());
	}
	//check if there is a "max" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("max")){
		nHigh = atoi(chromosomeNode->first_attribute("max")->value());
	}

	int data = (rand() % (nHigh - nLow + 1)) + nLow;

	std::stringstream ss;//create a stringstream
	ss << data;//add number to the stream
	return ss.str();//return a string with the contents of the stream

}

std::string DoubleEncoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	int nLow = 0;
	int nHigh = RAND_MAX;	//default range of rand()
	int nDecimals = 2;

	//check if there is a "min" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("min")){
		nLow = atoi(chromosomeNode->first_attribute("min")->value());
	}
	//check if there is a "max" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("max")){
		nHigh = atoi(chromosomeNode->first_attribute("max")->value());
	}

	int data = (rand() % (nHigh - nLow + 1)) + nLow;

	std::stringstream ss;//create a stringstream
	ss << data;//add integer part to the stream

	//check if there is a "decimals" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("decimals")){
		nDecimals = atoi(chromosomeNode->first_attribute("decimals")->value());
	}

	if(data < nHigh && nDecimals){
			data = (rand() % ((int)pow(10,nDecimals) - 1));
			ss  << "." << data;//add decimal part to the stream
	}

	return ss.str();//return a string with the contents of the stream

}


std::string AlphanumEncoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	int nMin = 0;
	int nMax = 0;

	int nChars;

	//check if there is a "max" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("max")){
		nMax = atoi(chromosomeNode->first_attribute("max")->value());

	}
	//check if there is a "min" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("min")){
		nMin = atoi(chromosomeNode->first_attribute("min")->value());

	}

	nChars = (rand() % (nMax - nMin + 1)) + nMin;

	std::stringstream ss;//create a stringstream
	for(int j = 0; j < nChars; j++){
		int i = rand() % m_vChars.size();
		ss << m_vChars[i];//add character to the stream
	}

	return ss.str();//return a string with the contents of the stream

}

std::string CustomEncoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	int nMin = 0;
	int nMax = 0;

	int nChars;

	//check if there is a "max" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("max")){
		nMax = atoi(chromosomeNode->first_attribute("max")->value());

	}
	//check if there is a "min" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("min")){
		nMin = atoi(chromosomeNode->first_attribute("min")->value());

	}

	nChars = (rand() % (nMax - nMin + 1)) + nMin;

	std::stringstream ss;//create a stringstream
	for(int j = 0; j < nChars; j++){
		int i = rand() % m_vChars.size();
		ss << m_vChars[i];//add character to the stream
	}

	return ss.str();//return a string with the contents of the stream

}

void CustomEncoding::SetChars(std::string characters){
	m_vChars.clear();
	std::copy ( characters.begin(), characters.end(), std::back_inserter ( m_vChars ) );
}

std::string ListEncoding::RandomData(rapidxml::xml_node<>* chromosomeNode){

	int nElements = 0;

	//check if there is a "elements" attribute in the chromosomeNode
	if(chromosomeNode->first_attribute("elements")){
		nElements = atoi(chromosomeNode->first_attribute("elements")->value());

	}

	std::stringstream ss;//create a stringstream
	for(int i = 0; i < nElements; i++){
		DoubleEncoding cDoubleEncoding;

		std::string data = "";
		data = cDoubleEncoding.RandomData(chromosomeNode);
		ss << data;		//add number to the stream
		if(i < nElements-1){
			ss << "|";   	//add separator to the stream
		}
	}



   return ss.str();//return a string with the contents of the stream

}
