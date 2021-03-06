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
rapidxml::xml_node<>* ChromosomeMutation::GetGeneNode(int n){
	rapidxml::xml_node<>* node;
	node = m_Node->first_node("Gene");

	for(int i = 0; i < n ; i++){
		node = node->next_sibling("Gene");
	}

	return node;
}


std::string Mutation::BitString(){
	return m_strValue;
}
std::string Mutation::FlipBits(){
	return m_strValue;
}
std::string Mutation::Boundary(){
	return m_strValue;
}
std::string Mutation::Uniform(){
	return m_strValue;
}
std::string Mutation::Gaussian(double sigma = 1.0){
	return m_strValue;
}
std::string Mutation::Duplication(){
	return m_strValue;
}
std::string Mutation::Deletion(){
	return m_strValue;
}
std::string Mutation::Insertion(){
	return m_strValue;
}
std::string Mutation::Swap(){
	return m_strValue;
}

std::string Mutation::ValidateMutation(std::string value){
	std::string strValue = value;

	//if there is a bits attribute, cut off the string at that length
	if(m_ChromosomeNode->first_attribute("encoding")->value() == std::string("binary") && m_ChromosomeNode->first_attribute("max")){
		unsigned int bits = atoi(m_ChromosomeNode->first_attribute("max")->value());
		if(strValue.size() > bits){
			strValue = strValue.substr(0, bits);
		}
	}

	//if there is a min attribute, make sure there are at least the minimum amount of bits by adding leading zero's
	if(m_ChromosomeNode->first_attribute("encoding")->value() == std::string("binary") && m_ChromosomeNode->first_attribute("min")){
		unsigned int bits = atoi(m_ChromosomeNode->first_attribute("min")->value());
		if(strValue.size() < bits){
			std::string strLeadingZeros ((bits -strValue.size()), '0');
			strValue = strValue.insert(0, strLeadingZeros.c_str());
		}
	}

	//make sure new value is not smaller than min boundary
	if(m_ChromosomeNode->first_attribute("encoding")->value() == std::string("integer") && m_ChromosomeNode->first_attribute("min")){
		if( atoi(strValue.c_str()) < atoi(m_ChromosomeNode->first_attribute("min")->value()) ){
			strValue = m_strValue;
		}
	}

	//make sure new value is not greater than max boundary
	if(m_ChromosomeNode->first_attribute("encoding")->value() == std::string("integer") && m_ChromosomeNode->first_attribute("max")){
		if( atoi(strValue.c_str()) > atoi(m_ChromosomeNode->first_attribute("max")->value()) ){
			strValue = m_strValue;
		}
	}

	//make sure new value is not smaller than min boundary
	if((m_ChromosomeNode->first_attribute("encoding")->value() == std::string("double") || m_ChromosomeNode->first_attribute("encoding")->value() == std::string("list")) && m_ChromosomeNode->first_attribute("min")){
		if( atof(strValue.c_str()) < atof(m_ChromosomeNode->first_attribute("min")->value()) ){
			strValue = m_strValue;
		}
	}

	//make sure new value is not greater than max boundary
	if((m_ChromosomeNode->first_attribute("encoding")->value() == std::string("double") || m_ChromosomeNode->first_attribute("encoding")->value() == std::string("list")) && m_ChromosomeNode->first_attribute("max")){
		if( atof(strValue.c_str()) > atof(m_ChromosomeNode->first_attribute("max")->value()) ){
			strValue = m_strValue;
		}
	}

	//make sure new value doesn't have more decimals than allowed
	if((m_ChromosomeNode->first_attribute("encoding")->value() == std::string("double") || m_ChromosomeNode->first_attribute("encoding")->value() == std::string("list")) && m_ChromosomeNode->first_attribute("decimals")){
		int nDecimals = atoi(m_ChromosomeNode->first_attribute("decimals")->value());
		size_t nFound = strValue.find('.');
		if(nFound != std::string::npos && (strValue.size()-nFound) > nDecimals){
			strValue = strValue.substr(0, nFound + nDecimals+1);
		}
	}


	//if there is a max attribute, cut off the string at that length
	if((m_ChromosomeNode->first_attribute("encoding")->value() == std::string("alphanum") || m_ChromosomeNode->first_attribute("encoding")->value() == std::string("custom")) && m_ChromosomeNode->first_attribute("max")){
		unsigned int nChars = atoi(m_ChromosomeNode->first_attribute("max")->value());
		if(strValue.size() > nChars){
			strValue = strValue.substr(0, nChars);
		}
	}

	//if there is a min attribute, make sure there are at least the minimum amount of characters
	if((m_ChromosomeNode->first_attribute("encoding")->value() == std::string("alphanum") || m_ChromosomeNode->first_attribute("encoding")->value() == std::string("custom")) && m_ChromosomeNode->first_attribute("min")){
		unsigned int nChars = atoi(m_ChromosomeNode->first_attribute("min")->value());
		if(strValue.size() < nChars){
			int nRandomChars = nChars - strValue.size();
			std::string strRandomChars = "";
			if(m_ChromosomeNode->first_attribute("encoding")->value() == std::string("alphanum") ){
				AlphanumEncoding cEncoding;
				std::vector<char> vChars = cEncoding.GetChars();
				std::stringstream ss;//create a stringstream
				for(int j = 0; j < nRandomChars; j++){
					int i = rand() % vChars.size();
					ss << vChars[i];//add character to the stream
				}
				strRandomChars = ss.str();
			}
			else if(m_ChromosomeNode->first_attribute("encoding")->value() == std::string("custom") && m_ChromosomeNode->first_attribute("chars")){
				CustomEncoding cEncoding;
				cEncoding.SetChars(m_ChromosomeNode->first_attribute("chars")->value());
				std::vector<char> vChars = cEncoding.GetChars();
				std::stringstream ss;//create a stringstream
				for(int j = 0; j < nRandomChars; j++){
					int i = rand() % vChars.size();
					ss << vChars[i];//add character to the stream
				}
				strRandomChars = ss.str();
			}

			strValue = strValue.append(strRandomChars.c_str());
		}
	}

	//check for multiple leading zero's like 001 or -001
	if(( m_ChromosomeNode->first_attribute("encoding")->value() == std::string("integer") || m_ChromosomeNode->first_attribute("encoding")->value() == std::string("double"))){
		if(strValue.size() > 1 ){
			if(strValue.at(0) == '0' && strValue.at(1) == '0'){
				strValue.erase(0,1);
			}
		}

		if(strValue.size() > 2 ){
			if(strValue.at(0) == '-' && strValue.at(1) == '0' && strValue.at(2) == '0'){
				strValue.erase(1,1);
			}
		}
	}



	return strValue;
}
/***************************************************************************************************************
 * Derived Class BitMutation
 ***************************************************************************************************************/

std::string BitMutation::BitString(){
	std::string strValue = m_strValue;

	int nRandom = 0;
	if(strValue.size() > 0){
		nRandom = rand() % strValue.size();
		(strValue.at(nRandom) =='1')?strValue.at(nRandom) = '0':strValue.at(nRandom) = '1';
	}

	return strValue;
}
std::string BitMutation::FlipBits(){
	std::string strValue = m_strValue;

	for(unsigned int i = 0; i < strValue.size(); i++){
		(strValue.at(i) =='1')?strValue.at(i) = '0':strValue.at(i) = '1';
	}

	return strValue;
}
std::string BitMutation::Boundary(){

	std::string strValue = m_strValue;
	std::stringstream ss;//create a stringstream

	int bit = rand() % 2;

	for(unsigned int i = 0; i < strValue.size(); i++){
		ss << bit;//add bit to the stream
	}

	return ss.str();//return a string with the contents of the stream
}
std::string BitMutation::Uniform(){
	BinaryEncoding cBinaryEncoding;
	return cBinaryEncoding.RandomData(m_ChromosomeNode);
}
/*std::string BitMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
std::string BitMutation::Duplication(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin
	}

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string BitMutation::Deletion(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);

	}

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string BitMutation::Insertion(){
	std::string strValue = m_strValue;

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

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string BitMutation::Swap(){
	std::string strValue = m_strValue;

	int nRandom1 = 0;
	int nRandom2 = 0;
	if(strValue.size() > 0){
		nRandom1 = rand() % strValue.size();
		nRandom2 = rand() % strValue.size();
		char chTmp = strValue.at(nRandom1);
		strValue.at(nRandom1) = strValue.at(nRandom2);
		strValue.at(nRandom2) = chTmp;
	}

	return strValue;
}




/***************************************************************************************************************
 * Derived Class IntegerMutation
 ***************************************************************************************************************/
std::string IntegerMutation::BitString(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		int nRandom = rand() % strValue.size();
		int nNewBit = rand() % 10;

		std::stringstream ss;//create a stringstream
		ss << nNewBit;
		if(strValue.at(nRandom) != '-')		//do not modify a minus sign if there is one
			strValue.replace(nRandom, 1, ss.str());
	}

	std::stringstream ss;
	ss << atoi(strValue.c_str());

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
/*std::string IntegerMutation::FlipBits(){
	return "";
}*/
std::string IntegerMutation::Boundary(){

	std::string strValue = m_strValue;

	std::stringstream ss;//create a stringstream

	if(m_ChromosomeNode->first_attribute("min") && m_ChromosomeNode->first_attribute("max")){
		//pick one of the 2 boundaries at random
		int nRandom = rand() % 2;
		(nRandom == 0) ? ss << m_ChromosomeNode->first_attribute("min")->value() : ss << m_ChromosomeNode->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_ChromosomeNode->first_attribute("min")){
		 ss << m_ChromosomeNode->first_attribute("min")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_ChromosomeNode->first_attribute("max")){
		ss << m_ChromosomeNode->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else
	{
		return strValue;
	}

}
std::string IntegerMutation::Uniform(){
	IntegerEncoding cIntegerEncoding;
	return cIntegerEncoding.RandomData(m_ChromosomeNode);
}
std::string IntegerMutation::Gaussian(double sigma = 1.0){
	std::string strValue = m_strValue;

	int nValue = atoi(strValue.c_str());
	int nChange = (int)box_muller(0, sigma);
	nValue += nChange;

	std::stringstream ss;//create a stringstream
	ss << nValue;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string IntegerMutation::Duplication(){
	std::string strValue = m_strValue;

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

		//make sure the duplicated characters are not before a - sign
		if(strValue.at(0) == '-' && nBegin == 0){
			nBegin = 1;
		}

		if(strSubstring.size() > 0){
			strValue.insert(nBegin, strSubstring); // insert substring into strValue at index nBegin
		}
	}


	std::stringstream ss;
	ss << atoi(strValue.c_str());

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string IntegerMutation::Deletion(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);
	}


	//make sure new value is not smaller than min boundary
	if(m_ChromosomeNode->first_attribute("min")){
		if( atoi(strValue.c_str()) < atoi(m_ChromosomeNode->first_attribute("min")->value()) ){
			return m_strValue;
		}
	}

	//make sure new value is not greater than max boundary
	if(m_ChromosomeNode->first_attribute("max")){
		if( atoi(strValue.c_str()) > atoi(m_ChromosomeNode->first_attribute("max")->value()) ){
			return m_strValue;
		}
	}

	//make sure the new value is not just a -
	if(strValue == "-"){
		strValue = "";
	}

	std::stringstream ss;
	ss << atoi(strValue.c_str());

	return ss.str();
}
std::string IntegerMutation::Insertion(){
	std::string strValue = m_strValue;
	int nRandom = rand() % 10;

	int nBegin = 0;
	//check if strValue is not empty, otherwise let nBegin be at 0
	if(strValue.size() > 0){
		nBegin = rand() % strValue.size();

		//make sure the inserted character is not before a - sign
		if(strValue.at(0) == '-' && nBegin == 0){
			nBegin = 1;
		}


		std::stringstream ss;//create a stringstream

		if(!(nRandom == 0 && ((strValue.at(0) == '-' && nBegin == 1) || nBegin == 0))){
			ss << nRandom;
			strValue.insert(nBegin, ss.str());
		}
	}

	std::stringstream ss;
	ss << atoi(strValue.c_str());

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string IntegerMutation::Swap(){
	std::string strValue = m_strValue;

	int nRandom1 = 0;
	int nRandom2 = 0;
	if(strValue.size() > 0){
		nRandom1 = rand() % strValue.size();
		nRandom2 = rand() % strValue.size();

		if(strValue.at(nRandom1) != '-' && strValue.at(nRandom2) != '-' ){
			char chTmp = strValue.at(nRandom1);
			strValue.at(nRandom1) = strValue.at(nRandom2);
			strValue.at(nRandom2) = chTmp;
		}

	}

	std::stringstream ss;
	ss << atoi(strValue.c_str());

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}

/***************************************************************************************************************
 * Derived Class DoubleMutation
 ***************************************************************************************************************/
std::string DoubleMutation::BitString(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		int nRandom = rand() % strValue.size();	//position to be replaced
		int nNewBit = rand() % 10;				//new character

		std::stringstream ss;//create a stringstream
		ss << nNewBit;

		//make sure the decimal point or minus sign is not replaced
		if(strValue.at(nRandom) != '.' && strValue.at(nRandom) != '-'){
			strValue.replace(nRandom, 1, ss.str());
		}
	}

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%s", strValue.c_str());
	ss << buffer;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
/*std::string DoubleMutation::FlipBits(){
	return "";
}*/
std::string DoubleMutation::Boundary(){
	std::string strValue = m_strValue;

	std::stringstream ss;//create a stringstream

	if(m_ChromosomeNode->first_attribute("min") && m_ChromosomeNode->first_attribute("max")){
		//pick one of the 2 boundaries at random
		int nRandom = rand() % 2;
		(nRandom == 0) ? ss << m_ChromosomeNode->first_attribute("min")->value() : ss << m_ChromosomeNode->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_ChromosomeNode->first_attribute("min")){
		 ss << m_ChromosomeNode->first_attribute("min")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else if(m_ChromosomeNode->first_attribute("max")){
		ss << m_ChromosomeNode->first_attribute("max")->value();
		return ss.str();//return a string with the contents of the stream
	}
	else
	{
		return strValue;
	}
}
std::string DoubleMutation::Uniform(){
	DoubleEncoding cDoubleEncoding;
	return cDoubleEncoding.RandomData(m_ChromosomeNode);
}
std::string DoubleMutation::Gaussian(double sigma = 1.0){
	std::string strValue = m_strValue;

	double dValue = atof(strValue.c_str());
	double dChange = box_muller(0, sigma);

	dValue += dChange;

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%f", dValue);
	ss << buffer;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string DoubleMutation::Duplication(){
	std::string strValue = m_strValue;

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

		//make sure the duplicated characters are not before a - sign
		if(strValue.at(0) == '-' && nBegin == 0){
			nBegin = 1;
		}

		if(strSubstring.size() > 0){
			strValue.insert(nBegin, strSubstring); // insert substring into strValue at index nBegin
		}

	}
	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%s", strValue.c_str());
	ss << buffer;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string DoubleMutation::Deletion(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);
	}

	//make sure the new value is not just a - or empty
	if(strValue == "-" || strValue == ""){
		strValue = "0";
	}

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%s", strValue.c_str());
	ss << buffer;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string DoubleMutation::Insertion(){
	std::string strValue = m_strValue;
	int nRandom = rand() % 10;

	int nBegin = 0;
	//check if strValue is not empty, otherwise let nBegin be at 0
	if(strValue.size() > 0){
		nBegin = rand() % strValue.size();

		//make sure the inserted character is not before a - sign
		if(strValue.at(0) == '-' && nBegin == 0){
			nBegin = 1;
		}

		std::stringstream ss;//create a stringstream

		if(!(nRandom == 0 && ((strValue.at(0) == '-' && nBegin == 1) || nBegin == 0))){
			ss << nRandom;
			strValue.insert(nBegin, ss.str());
		}
	}

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%s", strValue.c_str());
	ss << buffer;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}
std::string DoubleMutation::Swap(){
	std::string strValue = m_strValue;

	int nRandom1 = 0;
	int nRandom2 = 0;
	if(strValue.size() > 0){
		nRandom1 = rand() % strValue.size();
		nRandom2 = rand() % strValue.size();

		if(strValue.at(nRandom1) != '-' && strValue.at(nRandom2) != '-'){
			char chTmp = strValue.at(nRandom1);
			strValue.at(nRandom1) = strValue.at(nRandom2);
			strValue.at(nRandom2) = chTmp;
		}

	}

	std::stringstream ss;//create a stringstream
	char buffer[256]; //use sprintf to make sure no decimals are lost
	std::sprintf(buffer, "%s", strValue.c_str());
	ss << buffer;

	strValue = Mutation::ValidateMutation(ss.str());

	return strValue;
}

/***************************************************************************************************************
 * Derived Class AlphanumMutation
 ***************************************************************************************************************/
std::string AlphanumMutation::BitString(){
	std::string strValue = m_strValue;

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
	return cAlphanumEncoding.RandomData(m_ChromosomeNode);
}
/*std::string AlphanumMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
std::string AlphanumMutation::Duplication(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin

	}

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string AlphanumMutation::Deletion(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);

	}

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string AlphanumMutation::Insertion(){
	std::string strValue = m_strValue;

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

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string AlphanumMutation::Swap(){
	std::string strValue = m_strValue;

	int nRandom1 = 0;
	int nRandom2 = 0;
	if(strValue.size() > 0){
		nRandom1 = rand() % strValue.size();
		nRandom2 = rand() % strValue.size();

		if(strValue.at(nRandom1) != '-' && strValue.at(nRandom2) != '-' ){
			char chTmp = strValue.at(nRandom1);
			strValue.at(nRandom1) = strValue.at(nRandom2);
			strValue.at(nRandom2) = chTmp;
		}

	}

	return strValue;
}

/***************************************************************************************************************
 * Derived Class CustomMutation
 ***************************************************************************************************************/
std::string CustomMutation::BitString(){
		std::string strValue = m_strValue;

		// make sure there is a string
		if(strValue.size() > 0 ){
			CustomEncoding cCustomEncoding;
			cCustomEncoding.SetChars(m_ChromosomeNode->first_attribute("chars")->value());
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
	cCustomEncoding.SetChars(m_ChromosomeNode->first_attribute("chars")->value());
	return cCustomEncoding.RandomData(m_ChromosomeNode);
}
/*std::string CustomMutation::Gaussian(double sigma = 1.0){
	return "";
}*/
std::string CustomMutation::Duplication(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//duplicate a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue.insert(nBegin, strValue, nBegin, nEnd-nBegin+1); // insert substring of strValue from index [nBegin,nEnd) into strValue at index nBegin
	}

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string CustomMutation::Deletion(){
	std::string strValue = m_strValue;

	if(strValue.size() > 0){
		//delete a random part of the string
		int nBegin = rand() % strValue.size();
		int nEnd = (rand() % (strValue.size()-1 - nBegin + 1)) + nBegin;
		strValue = strValue.erase(nBegin, nEnd-nBegin+1);

	}

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string CustomMutation::Insertion(){
	std::string strValue = m_strValue;

	//get a random character and insert it in strValue;
	CustomEncoding cCustomEncoding;
	cCustomEncoding.SetChars(m_ChromosomeNode->first_attribute("chars")->value());
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

	strValue = Mutation::ValidateMutation(strValue);

	return strValue;
}
std::string CustomMutation::Swap(){
	std::string strValue = m_strValue;

	int nRandom1 = 0;
	int nRandom2 = 0;
	if(strValue.size() > 0){
		nRandom1 = rand() % strValue.size();
		nRandom2 = rand() % strValue.size();

		if(strValue.at(nRandom1) != '-' && strValue.at(nRandom2) != '-' ){
			char chTmp = strValue.at(nRandom1);
			strValue.at(nRandom1) = strValue.at(nRandom2);
			strValue.at(nRandom2) = chTmp;
		}

	}

	return strValue;
}

/***************************************************************************************************************
 * Derived Class ListMutation
 ***************************************************************************************************************/
void StringExplode(std::string str, std::string separator, std::vector<std::string>* results){
    std::size_t found;
    found = str.find_first_of(separator);
    while(found != std::string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}


std::string ListMutation::BitString(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.BitString();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
/*std::string ListMutation::FlipBits(){
	return "";
}*/
std::string ListMutation::Boundary(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Boundary();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
std::string ListMutation::Uniform(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Uniform();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
std::string ListMutation::Gaussian(double sigma = 1.0){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Gaussian(sigma);
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
std::string ListMutation::Duplication(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Duplication();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
std::string ListMutation::Deletion(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Deletion();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
std::string ListMutation::Insertion(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Insertion();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}
std::string ListMutation::Swap(){
	std::vector<std::string> vstrData;
	StringExplode(m_strValue, "|", &vstrData);
	// vector vstrData now contains each double!

	unsigned int nSelectedElement = 0;  //the index of the element to be mutated
	if(vstrData.size() > 0){
		nSelectedElement = rand() % vstrData.size();
	}

	std::string strData = "";
	std::stringstream ss;//create a stringstream
	for(unsigned int i = 0; i < vstrData.size(); i++){
		strData = vstrData.at(i);
		if(i == nSelectedElement){
			DoubleMutation cDoubleMutation(strData, m_ChromosomeNode);
			strData = cDoubleMutation.Swap();
		}
		ss << strData;		//add number to the stream
		if(i < vstrData.size()-1){
			ss << "|";   	//add separator to the stream
		}
	}

   return ss.str();//return a string with the contents of the stream
}


/***************************************************************************************************************
 * Derived Class ChromosomeMutation
 ***************************************************************************************************************/

void ChromosomeMutation::Duplication(){
	int nGenes = 0;
	//count genes
	for (rapidxml::xml_node<>* geneNode = m_Node->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene")){
		nGenes++;
	}

	//if there are genes, duplicate at random one or more genes
	if(nGenes){
		int nBegin = rand() % nGenes;
		int nEnd = (rand() % (nGenes-1 - nBegin + 1)) + nBegin;
		rapidxml::xml_node<>* geneNode;
		rapidxml::xml_node<>* clonedNode;

		int j = 0;
		for(int i = nBegin; i <= nEnd; i++){
			geneNode = ChromosomeMutation::GetGeneNode(i);
			clonedNode = m_Node->document()->clone_node(geneNode);

			geneNode = ChromosomeMutation::GetGeneNode(nEnd+j+1);
			m_Node->insert_node(geneNode, clonedNode);
			j++;
		}
	}


}
void ChromosomeMutation::Deletion(){
	int nGenes = 0;
	//count genes
	for (rapidxml::xml_node<>* geneNode = m_Node->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene")){
		nGenes++;
	}

	//if there are genes, delete at random one or more genes
	if(nGenes){
		int nBegin = rand() % nGenes;
		int nEnd = (rand() % (nGenes-1 - nBegin + 1)) + nBegin;
		rapidxml::xml_node<>* geneNode;

		for(int i = nBegin; i <= nEnd; i++){
			geneNode = ChromosomeMutation::GetGeneNode(nBegin);
			m_Node->remove_node(geneNode);

		}
	}


}
void ChromosomeMutation::Insertion(){
	int nGenes = 0;
	//count genes
	for (rapidxml::xml_node<>* geneNode = m_Node->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene")){
		nGenes++;
	}

		int nRandom1 = rand() % (nGenes+1);

		rapidxml::xml_node<>* geneNode;
		rapidxml::xml_node<>* newNode;

		geneNode = ChromosomeMutation::GetGeneNode(nRandom1);
		newNode = m_Node->document()->allocate_node(rapidxml::node_element, "Gene");

		char* pchRandomData = 0;


		std::string strEncoding = m_Node->first_attribute("encoding")->value();

		if(strEncoding == "binary"){
			BinaryEncoding cBinaryEncoding;
			Encoding& rEncoding = cBinaryEncoding;
			pchRandomData = m_Node->document()->allocate_string(rEncoding.RandomData(m_Node).c_str());
		}
		else if(strEncoding == "integer"){
			IntegerEncoding cIntegerEncoding;
			Encoding& rEncoding = cIntegerEncoding;
			pchRandomData = m_Node->document()->allocate_string(rEncoding.RandomData(m_Node).c_str());
		}
		else if(strEncoding == "double"){
			DoubleEncoding cDoubleEncoding;
			Encoding& rEncoding = cDoubleEncoding;
			pchRandomData = m_Node->document()->allocate_string(rEncoding.RandomData(m_Node).c_str());
		}
		else if(strEncoding == "alphanum"){
			AlphanumEncoding cAlphanumEncoding;
			Encoding& rEncoding = cAlphanumEncoding;
			pchRandomData = m_Node->document()->allocate_string(rEncoding.RandomData(m_Node).c_str());
		}
		else if(strEncoding == "custom"){
			CustomEncoding cCustomEncoding;
			if(m_Node->first_attribute("chars")){
				std::string	strCharacters = m_Node->first_attribute("chars")->value();
				cCustomEncoding.SetChars(strCharacters);
			}
			Encoding& rEncoding = cCustomEncoding;
			pchRandomData = m_Node->document()->allocate_string(rEncoding.RandomData(m_Node).c_str());
		}
		else if(strEncoding == "list"){
			ListEncoding cListEncoding;
			Encoding& rEncoding = cListEncoding;
			pchRandomData = m_Node->document()->allocate_string(rEncoding.RandomData(m_Node).c_str());
		}
		else{
			std::cout << "unknown encoding type" << std::endl;
		}

		newNode->value(pchRandomData);
		m_Node->insert_node(geneNode, newNode);



}
void ChromosomeMutation::Swap(){
	int nGenes = 0;
	//count genes
	for (rapidxml::xml_node<>* geneNode = m_Node->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene")){
		nGenes++;
	}

	//if there are genes, swap at random 2 genes
	if(nGenes){
		int nRandom1 = rand() % nGenes;
		int nRandom2 = (rand() % (nGenes-1 - nRandom1 + 1)) + nRandom1;

		rapidxml::xml_node<>* geneNode;
		rapidxml::xml_node<>* clonedNode;

		//copy the second node just after the first node
		geneNode = ChromosomeMutation::GetGeneNode(nRandom2);
		clonedNode = m_Node->document()->clone_node(geneNode);
		geneNode = ChromosomeMutation::GetGeneNode(nRandom1+1);
		m_Node->insert_node(geneNode, clonedNode);

		//copy the first node just after the second node
		geneNode = ChromosomeMutation::GetGeneNode(nRandom1);
		clonedNode = m_Node->document()->clone_node(geneNode);
		geneNode = ChromosomeMutation::GetGeneNode(nRandom2+2);
		m_Node->insert_node(geneNode, clonedNode);

		//remove the original first and second node;
		geneNode = ChromosomeMutation::GetGeneNode(nRandom1);
		m_Node->remove_node(geneNode);
		geneNode = ChromosomeMutation::GetGeneNode(nRandom2);
		m_Node->remove_node(geneNode);


	}


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
