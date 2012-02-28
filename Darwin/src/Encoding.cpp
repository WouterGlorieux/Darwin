/*
 * Encoding.cpp
 *
 *  Created on: 21-feb.-2012
 *      Author: woutergl
 */

#include "Encoding.h"

std::string Encoding::RandomData(rapidxml::xml_node<>* geneNode){

	return "base encoding";
}

std::string BinaryEncoding::RandomData(rapidxml::xml_node<>* geneNode){

	//check if there is a "bits" attribute in the geneNode
	if(geneNode->first_attribute("bits")){
		m_nbits = atoi(geneNode->first_attribute("bits")->value());
	}

	int bit ;

	std::stringstream ss;//create a stringstream
	for(int i = 0 ; i < m_nbits ; i++){
		bit = rand() % 2;
		ss << bit;//add number to the stream
	}

	return ss.str();//return a string with the contents of the stream

}


std::string IntegerEncoding::RandomData(rapidxml::xml_node<>* geneNode){

	int nLow = 0;
	int nHigh = 32767;		//default range of rand()

	//check if there is a "min" attribute in the geneNode
	if(geneNode->first_attribute("min")){
		nLow = atoi(geneNode->first_attribute("min")->value());
	}
	//check if there is a "max" attribute in the geneNode
	if(geneNode->first_attribute("max")){
		nHigh = atoi(geneNode->first_attribute("max")->value());
	}

	int data = (rand() % (nHigh - nLow + 1)) + nLow;

	std::stringstream ss;//create a stringstream
	ss << data;//add number to the stream
	return ss.str();//return a string with the contents of the stream

}

std::string DoubleEncoding::RandomData(rapidxml::xml_node<>* geneNode){

	int nLow = 0;
	int nHigh = 32767;	//default range of rand()
	int nDecimals = 2;

	//check if there is a "min" attribute in the geneNode
	if(geneNode->first_attribute("min")){
		nLow = atoi(geneNode->first_attribute("min")->value());
	}
	//check if there is a "max" attribute in the geneNode
	if(geneNode->first_attribute("max")){
		nHigh = atoi(geneNode->first_attribute("max")->value());
	}

	int data = (rand() % (nHigh - nLow + 1)) + nLow;

	std::stringstream ss;//create a stringstream
	ss << data;//add integer part to the stream

	//check if there is a "decimals" attribute in the geneNode
	if(geneNode->first_attribute("decimals")){
		nDecimals = atoi(geneNode->first_attribute("decimals")->value());
	}

	if(data < nHigh && nDecimals){
			data = (rand() % ((int)pow(10,nDecimals) - 1));
			ss  << "." << data;//add decimal part to the stream
	}

	return ss.str();//return a string with the contents of the stream

}


std::string AlphanumEncoding::RandomData(rapidxml::xml_node<>* geneNode){

	int nMaxChars = 32767;	//default maxChars
	int nChars;

	//check if there is a "maxChars" attribute in the geneNode
	if(geneNode->first_attribute("maxChars")){
		nMaxChars = atoi(geneNode->first_attribute("maxChars")->value());

	}

	nChars = rand() % nMaxChars;

	std::stringstream ss;//create a stringstream
	for(int j = 0; j < nChars; j++){
		int i = rand() % m_vChars.size();
		ss << m_vChars[i];//add character to the stream
	}

	return ss.str();//return a string with the contents of the stream

}

std::string CustomEncoding::RandomData(rapidxml::xml_node<>* geneNode){

	int nMaxChars = 32767;	//default maxChars
	int nChars;

	//check if there is a "maxChars" attribute in the geneNode
	if(geneNode->first_attribute("maxChars")){
		nMaxChars = atoi(geneNode->first_attribute("maxChars")->value());

	}

	nChars = rand() % nMaxChars;


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

std::string TreeEncoding::RandomData(rapidxml::xml_node<>* geneNode){

	int nLow = 0;
	int nHigh = 100;

	int data = (rand() % (nHigh - nLow + 1)) + nLow;

	   std::stringstream ss;//create a stringstream
	   ss << data;//add number to the stream
	   return ss.str();//return a string with the contents of the stream

}