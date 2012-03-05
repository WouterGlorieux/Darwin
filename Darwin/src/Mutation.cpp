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
	return m_Node->value();
}
std::string Mutation::FlipBits(){
	return m_Node->value();
}
std::string Mutation::Boundary(){
	return m_Node->value();
}
std::string Mutation::Uniform(){
	return m_Node->value();
}
std::string Mutation::Gaussian(double sigma = 1.0){
	return m_Node->value();
}
std::string Mutation::Duplication(){
	return m_Node->value();
}
std::string Mutation::Deletion(){
	return m_Node->value();
}
std::string Mutation::Insertion(){
	return m_Node->value();
}


/***************************************************************************************************************
 * Derived Class BitMutation
 ***************************************************************************************************************/

std::string BitMutation::BitString(){
	std::string strValue = m_Node->value();

	int nRandom = 0;
	if(strValue.size() > 0){
		nRandom = rand() % strValue.size();
		(strValue.at(nRandom) =='1')?strValue.at(nRandom) = '0':strValue.at(nRandom) = '1';
	}

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
/*std::string BitMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
std::string BitMutation::Duplication(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin
	}

	//if there is a bits attribute, cut off the string at that length
	if(m_Node->first_attribute("bits")){
		int bits = atoi(m_Node->first_attribute("bits")->value());
		strValue = strValue.substr(0, bits);
	}

	return strValue;
}
std::string BitMutation::Deletion(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
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
	}
	return strValue;
}
std::string BitMutation::Insertion(){
	std::string strValue = m_Node->value();

	int nBegin = 0;
	int nEnd = 0;
	if(strValue.size() > 0){
		//insert random bits into the string
		nBegin = rand() % strValue.size();
		nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
	}


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
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		int nRandom = rand() % strValue.size();
		int nNewBit = rand() % 10;

		std::stringstream ss;//create a stringstream
		ss << nNewBit;
		strValue.replace(nRandom, 1, ss.str());

		//make sure new value is not smaller than min boundary
		if(m_Node->first_attribute("min")){
			if( atoi(strValue.c_str()) < atoi(m_Node->first_attribute("min")->value()) ){
				return m_Node->value();
			}
		}

		//make sure new value is not greater than max boundary
		if(m_Node->first_attribute("max")){
			if( atoi(strValue.c_str()) > atoi(m_Node->first_attribute("max")->value()) ){
				return m_Node->value();
			}
		}

	}
	return strValue;
}
/*std::string IntegerMutation::FlipBits(){
	return "";
}*/
std::string IntegerMutation::Boundary(){

	std::string strValue = m_Node->value();

	std::stringstream ss;//create a stringstream

	if(m_Node->first_attribute("min") && m_Node->first_attribute("max")){
		//pick one of the 2 boundaries at random
		int nRandom = rand() % 2;
		(nRandom == 0) ? ss << m_Node->first_attribute("min")->value() : ss << m_Node->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_Node->first_attribute("min")){
		 ss << m_Node->first_attribute("min")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_Node->first_attribute("max")){
		ss << m_Node->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else
	{
		return strValue;
	}

}
std::string IntegerMutation::Uniform(){
	IntegerEncoding cIntegerEncoding;
	return cIntegerEncoding.RandomData(m_Node);
}
std::string IntegerMutation::Gaussian(double sigma = 1.0){
	std::string strValue = m_Node->value();

	int nValue = atoi(strValue.c_str());
	int nChange = (int)box_muller(0, sigma);
	nValue += nChange;

	//make sure new value is not smaller than min boundary
	if(m_Node->first_attribute("min")){
		if( nValue < atoi(m_Node->first_attribute("min")->value()) ){
			return m_Node->value();
		}
	}

	//make sure new value is not greater than max boundary
	if(m_Node->first_attribute("max")){
		if( nValue > atoi(m_Node->first_attribute("max")->value()) ){
			return m_Node->value();
		}
	}

	std::stringstream ss;//create a stringstream
	ss << nValue;
	return ss.str();
}
std::string IntegerMutation::Duplication(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;

		std::string strSubstring = strValue.substr(nBegin,nEnd-nBegin+1);

		//make sure there is no - in the substring
		size_t nFound = strSubstring.find('-');
		if(nFound != std::string::npos){
			strSubstring.erase((int)nFound, 1);
		}

		if(strSubstring.size() > 0){
			strValue.insert(nBegin, strSubstring); // insert substring into strValue at index nBegin
		}



		//make sure new value is not smaller than min boundary
		if(m_Node->first_attribute("min")){
			if( atoi(strValue.c_str()) < atoi(m_Node->first_attribute("min")->value()) ){
				return m_Node->value();
			}
		}

		//make sure new value is not greater than max boundary
		if(m_Node->first_attribute("max")){
			if( atoi(strValue.c_str()) > atoi(m_Node->first_attribute("max")->value()) ){
				return m_Node->value();
			}
		}
	}
	return strValue;
}
std::string IntegerMutation::Deletion(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);
	}


	//make sure new value is not smaller than min boundary
	if(m_Node->first_attribute("min")){
		if( atoi(strValue.c_str()) < atoi(m_Node->first_attribute("min")->value()) ){
			return m_Node->value();
		}
	}

	//make sure new value is not greater than max boundary
	if(m_Node->first_attribute("max")){
		if( atoi(strValue.c_str()) > atoi(m_Node->first_attribute("max")->value()) ){
			return m_Node->value();
		}
	}

	//make sure the new value is not just a -
	if(strValue == "-"){
		strValue = "";
	}

	return strValue;
}
std::string IntegerMutation::Insertion(){
	std::string strValue = m_Node->value();
	int nRandom = rand() % 10;

	int nBegin = 0;
	//check if strValue is not empty, otherwise let nBegin be at 0
	if(strValue.size() > 0){
		nBegin = rand() % strValue.size();

		//make sure the inserted character is not before a - sign
		if(strValue.at(0) == '-' && nBegin == 0){
			nBegin = 1;
		}
	}



	std::stringstream ss;//create a stringstream
	ss << nRandom;
	strValue.insert(nBegin, ss.str());

	//check if there is a min attribute
	if(m_Node->first_attribute("max")){
		int nMin = atoi(m_Node->first_attribute("min")->value());
		//check if the new value is smaller than min, if so return original value
		if(atoi(strValue.c_str()) < nMin){
			return m_Node->value();
		}
	}

	//check if there is a max attribute
	if(m_Node->first_attribute("max")){
		int nMax = atoi(m_Node->first_attribute("max")->value());
		//check if the new value is bigger than max, if so return original value
		if(atoi(strValue.c_str()) > nMax){
			return m_Node->value();
		}
	}

	return strValue;
}


/***************************************************************************************************************
 * Derived Class DoubleMutation
 ***************************************************************************************************************/
std::string DoubleMutation::BitString(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		int nRandom = rand() % strValue.size();	//position to be replaced
		int nNewBit = rand() % 10;				//new character

		std::stringstream ss;//create a stringstream
		ss << nNewBit;

		//make sure the decimal point is not replaced
		if(strValue.at(nRandom) != '.'){
			strValue.replace(nRandom, 1, ss.str());
		}

		//make sure new value is not smaller than min boundary
		if(m_Node->first_attribute("min")){
			if( atof(strValue.c_str()) < atof(m_Node->first_attribute("min")->value()) ){
				return m_Node->value();
			}
		}

		//make sure new value is not greater than max boundary
		if(m_Node->first_attribute("max")){
			if( atof(strValue.c_str()) > atof(m_Node->first_attribute("max")->value()) ){
				return m_Node->value();
			}
		}
	}
	return strValue;
}
/*std::string DoubleMutation::FlipBits(){
	return "";
}*/
std::string DoubleMutation::Boundary(){
	std::string strValue = m_Node->value();

	std::stringstream ss;//create a stringstream

	if(m_Node->first_attribute("min") && m_Node->first_attribute("max")){
		//pick one of the 2 boundaries at random
		int nRandom = rand() % 2;
		(nRandom == 0) ? ss << m_Node->first_attribute("min")->value() : ss << m_Node->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_Node->first_attribute("min")){
		 ss << m_Node->first_attribute("min")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_Node->first_attribute("max")){
		ss << m_Node->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else
	{
		return strValue;
	}
}
std::string DoubleMutation::Uniform(){
	DoubleEncoding cDoubleEncoding;
	return cDoubleEncoding.RandomData(m_Node);
}
std::string DoubleMutation::Gaussian(double sigma = 1.0){
	std::string strValue = m_Node->value();

	double dValue = atof(strValue.c_str());
	double dChange = box_muller(0, sigma);

	dValue += dChange;

	//make sure new value is not smaller than min boundary
	if(m_Node->first_attribute("min")){
		if( dValue < atoi(m_Node->first_attribute("min")->value()) ){
			return m_Node->value();
		}
	}

	//make sure new value is not greater than max boundary
	if(m_Node->first_attribute("max")){
		if( dValue > atoi(m_Node->first_attribute("max")->value()) ){
			return m_Node->value();
		}
	}

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%f", dValue);
	ss << buffer;
	strValue = ss.str();

	//make sure new value doesn't have more decimals than allowed
	if(m_Node->first_attribute("decimals")){
		int nDecimals = atoi(m_Node->first_attribute("decimals")->value());
		size_t nFound = strValue.find('.');

		if(nFound != std::string::npos && (strValue.size()-nFound) > nDecimals){
			//if decimals is 0, make sure the new value doesn't end with a point
			if(nDecimals == 0){
				nFound--;
			}
			strValue = strValue.substr(0, nFound + nDecimals+1);
		}



	}

	return strValue;
}
std::string DoubleMutation::Duplication(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		std::string strSubstring = strValue.substr(nBegin,nEnd-nBegin+1);

		//make sure there is no decimal point in the substring
		size_t nFound = strSubstring.find('.');
		if(nFound != std::string::npos){
			strSubstring.erase((int)nFound, 1);
		}

		//make sure there is no - in the substring
		nFound = strSubstring.find('-');
		if(nFound != std::string::npos){
			strSubstring.erase((int)nFound, 1);
		}

		if(strSubstring.size() > 0){
			strValue.insert(nBegin, strSubstring); // insert substring into strValue at index nBegin
		}

		//make sure new value is not smaller than min boundary
		if(m_Node->first_attribute("min")){
			if( atof(strValue.c_str()) < atof(m_Node->first_attribute("min")->value()) ){
				return m_Node->value();
			}
		}

		//make sure new value is not greater than max boundary
		if(m_Node->first_attribute("max")){
			if( atof(strValue.c_str()) > atof(m_Node->first_attribute("max")->value()) ){
				return m_Node->value();
			}
		}

		//make sure new value doesn't have more decimals than allowed
		if(m_Node->first_attribute("decimals")){
			int nDecimals = atoi(m_Node->first_attribute("decimals")->value());
			nFound = strValue.find('.');
			if(nFound != std::string::npos && (strValue.size()-nFound) > nDecimals){
				strValue = strValue.substr(0, nFound + nDecimals+1);
			}

		}
	}
	return strValue;
}
std::string DoubleMutation::Deletion(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);
	}


	//make sure new value is not smaller than min boundary
	if(m_Node->first_attribute("min")){
		if( atof(strValue.c_str()) < atof(m_Node->first_attribute("min")->value()) ){
			return m_Node->value();
		}
	}

	//make sure new value is not greater than max boundary
	if(m_Node->first_attribute("max")){
		if( atof(strValue.c_str()) > atof(m_Node->first_attribute("max")->value()) ){
			return m_Node->value();
		}
	}

	//make sure the new value is not just a -
	if(strValue == "-"){
		strValue = "";
	}

	return strValue;
}
std::string DoubleMutation::Insertion(){
	std::string strValue = m_Node->value();
	int nRandom = rand() % 10;

	int nBegin = 0;
	//check if strValue is not empty, otherwise let nBegin be at 0
	if(strValue.size() > 0){
		nBegin = rand() % strValue.size();

		//make sure the inserted character is not before a - sign
		if(strValue.at(0) == '-' && nBegin == 0){
			nBegin = 1;
		}
	}



	std::stringstream ss;//create a stringstream
	ss << nRandom;
	strValue.insert(nBegin, ss.str());

	//check if there is a min attribute
	if(m_Node->first_attribute("max")){
		int nMin = atoi(m_Node->first_attribute("min")->value());
		//check if the new value is smaller than min, if so return original value
		if(atoi(strValue.c_str()) < nMin){
			return m_Node->value();
		}
	}

	//check if there is a max attribute
	if(m_Node->first_attribute("max")){
		int nMax = atoi(m_Node->first_attribute("max")->value());
		//check if the new value is bigger than max, if so return original value
		if(atoi(strValue.c_str()) > nMax){
			return m_Node->value();
		}
	}

	//make sure new value doesn't have more decimals than allowed
	if(m_Node->first_attribute("decimals")){
		int nDecimals = atoi(m_Node->first_attribute("decimals")->value());
		size_t nFound = strValue.find('.');
		if(nFound != std::string::npos && (strValue.size()-nFound) > nDecimals){
			strValue = strValue.substr(0, nFound + nDecimals+1);
		}

	}

	return strValue;
}


/***************************************************************************************************************
 * Derived Class AlphanumMutation
 ***************************************************************************************************************/
std::string AlphanumMutation::BitString(){
	std::string strValue = m_Node->value();

	// make sure there is a string
	if(strValue.size() > 0 ){
		AlphanumEncoding cAlphanumEncoding;
		std::vector<char> characters = cAlphanumEncoding.GetChars();

		int nRandom = rand() % strValue.size();
		int nNewBit = rand() % characters.size();

		std::stringstream ss;//create a stringstream
		ss << characters.at(nNewBit);
		strValue.replace(nRandom, 1, ss.str());
	}

	return strValue;
}
/*std::string AlphanumMutation::FlipBits(){
	return "";
}*/
/*std::string AlphanumMutation::Boundary(){
	return "";
}*/
std::string AlphanumMutation::Uniform(){
	AlphanumEncoding cAlphanumEncoding;
	return cAlphanumEncoding.RandomData(m_Node);
}
/*std::string AlphanumMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
std::string AlphanumMutation::Duplication(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin

	}

	//if there is a maxChars attribute, cut off the string at that length
	if(m_Node->first_attribute("maxChars")){
		int chars = atoi(m_Node->first_attribute("maxChars")->value());
		strValue = strValue.substr(0, chars);
	}

	return strValue;
}
std::string AlphanumMutation::Deletion(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);

	}
	return strValue;
}
std::string AlphanumMutation::Insertion(){
	std::string strValue = m_Node->value();

	//check if there is a maxChars attribute
	if(m_Node->first_attribute("maxChars")){
		int nChars = atoi(m_Node->first_attribute("maxChars")->value());
		if((int)strValue.size() >= nChars){
			return strValue;
		}
	}

	//get a random character and insert it in strValue;
	AlphanumEncoding cAlphanumEncoding;
	std::vector<char> vCharacters = cAlphanumEncoding.GetChars();

	int nRandom = rand() % vCharacters.size();

	int nBegin = 0;
	//check if strValue is not empty, otherwise let nBegin be at 0
	if(strValue.size() > 0){
		nBegin = rand() % strValue.size();
	}

	std::stringstream ss;//create a stringstream
	ss << vCharacters.at(nRandom);
	strValue.insert(nBegin, ss.str());

	return strValue;
}


/***************************************************************************************************************
 * Derived Class CustomMutation
 ***************************************************************************************************************/
std::string CustomMutation::BitString(){
		std::string strValue = m_Node->value();

		// make sure there is a string
		if(strValue.size() > 0 ){
			CustomEncoding cCustomEncoding;
			cCustomEncoding.SetChars(m_Node->parent()->first_attribute("chars")->value());
			std::vector<char> characters = cCustomEncoding.GetChars();

			int nRandom = rand() % strValue.size();
			int nNewBit = rand() % characters.size();

			std::stringstream ss;//create a stringstream
			ss << characters.at(nNewBit);
			strValue.replace(nRandom, 1, ss.str());
		}

		return strValue;
}
/*std::string CustomMutation::FlipBits(){
	return "";
}*/
/*std::string CustomMutation::Boundary(){
	return "";
}*/
std::string CustomMutation::Uniform(){
	CustomEncoding cCustomEncoding;
	cCustomEncoding.SetChars(m_Node->parent()->first_attribute("chars")->value());
	return cCustomEncoding.RandomData(m_Node);
}
/*std::string CustomMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
std::string CustomMutation::Duplication(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin

	}

	//if there is a maxChars attribute, cut off the string at that length
	if(m_Node->first_attribute("maxChars")){
		int chars = atoi(m_Node->first_attribute("maxChars")->value());
		strValue = strValue.substr(0, chars);
	}

	return strValue;
}
std::string CustomMutation::Deletion(){
	std::string strValue = m_Node->value();

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);

	}
	return strValue;
}
std::string CustomMutation::Insertion(){
	std::string strValue = m_Node->value();

	//check if there is a maxChars attribute
	if(m_Node->first_attribute("maxChars")){
		int nChars = atoi(m_Node->first_attribute("maxChars")->value());
		if((int)strValue.size() >= nChars){
			return strValue;
		}
	}

	//get a random character and insert it in strValue;
	CustomEncoding cCustomEncoding;
	cCustomEncoding.SetChars(m_Node->parent()->first_attribute("chars")->value());
	std::vector<char> vCharacters = cCustomEncoding.GetChars();

	int nRandom = rand() % vCharacters.size();

	int nBegin = 0;
	//check if strValue is not empty, otherwise let nBegin be at 0
	if(strValue.size() > 0){
		nBegin = rand() % strValue.size();
	}

	std::stringstream ss;//create a stringstream
	ss << vCharacters.at(nRandom);
	strValue.insert(nBegin, ss.str());

	return strValue;
}


/***************************************************************************************************************
 * Derived Class TreeMutation
 ***************************************************************************************************************/
/*std::string TreeMutation::BitString(){
	return "";
}*/
/*std::string TreeMutation::FlipBits(){
	return "";
}*/
/*std::string TreeMutation::Boundary(){
	return "";
}*/
/*std::string TreeMutation::Uniform(){
	return "";
}*/
/*std::string TreeMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
/*std::string TreeMutation::Duplication(){
	return "";
}*/
/*std::string TreeMutation::Deletion(){
	return "";
}*/
/*std::string TreeMutation::Insertion(){
	return "";
}*/

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
	int nHigh = RAND_MAX;
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
