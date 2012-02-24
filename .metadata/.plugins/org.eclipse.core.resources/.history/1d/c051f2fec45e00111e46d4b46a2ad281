/*
 * Genome.cpp
 *
 *  Created on: 6-feb.-2012
 *      Author: woutergl
 */

#include "Genome.h"

void Genome::newGenome(const char* pchId ){

	rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&m_strXML[0]);

	// xml declaration
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	// root node
	rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "Genome");

	root->append_attribute(doc.allocate_attribute("type", pchId));
	doc.append_node(root);

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);


}

void Genome::addChromosome(const char* pchId, EncodingType encoding ){

	rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&m_strXML[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	// chromosome node
    rapidxml::xml_node<>* chromosome = doc.allocate_node(rapidxml::node_element, "Chromosome");
	chromosome->append_attribute(doc.allocate_attribute("id", pchId));

	std::string strEncoding;
	switch (encoding)
	    {
	        case ENCODING_BINARY:
	        	strEncoding = "binary";
	            break;
	        case ENCODING_VALUE:
	        	strEncoding = "value";
	            break;
	        case ENCODING_TREE:
	        	strEncoding = "tree";
	            break;
	        case ENCODING_INTEGER:
	        	strEncoding = "integer";
	            break;
	        case ENCODING_ALPHANUM:
	        	strEncoding = "alphanum";
	            break;

	        default:
	            std::cout << "Unknown encoding type" << std::endl;
	            break;
	    }

	chromosome->append_attribute(doc.allocate_attribute("encoding", strEncoding.c_str()));
	rootNode->append_node(chromosome);

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);

}

void Genome::addGene(const char* pchId, std::string strChromosomeId ){

    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	for (rapidxml::xml_node<> *child = rootNode->first_node("Chromosome"); child; child = child->next_sibling("Chromosome"))
	{
	    if(child->first_attribute("id")->value() == strChromosomeId){
	    // gene node
		rapidxml::xml_node<>* gene = doc.allocate_node(rapidxml::node_element, "Gene");
		gene->append_attribute(doc.allocate_attribute("id", pchId ));
		child->append_node(gene);

		break;
	    }

	}

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);


}

void Genome::addChromosomeAttribute(std::string strChromosomeId, std::string strName, std::string strValue){

    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	for (rapidxml::xml_node<>* chromosomeNode = rootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{
	    if(chromosomeNode->first_attribute("id")->value() == strChromosomeId){
	    	char* pchName = doc.allocate_string(strName.c_str());
	    	char* pchValue = doc.allocate_string(strValue.c_str());
	    	chromosomeNode->append_attribute(doc.allocate_attribute(pchName, pchValue ));
	    	break;
	    }

	}

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);

}
void Genome::addGeneAttribute(std::string strChromosomeId, std::string strGeneId, std::string strName, std::string strValue){
    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	for (rapidxml::xml_node<>* chromosomeNode = rootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{
	    if(chromosomeNode->first_attribute("id")->value() == strChromosomeId){
	    	for (rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene"))
	    	{
	    		if(geneNode->first_attribute("id")->value() == strGeneId){
	    			char* pchName = doc.allocate_string(strName.c_str());
	    			char* pchValue = doc.allocate_string(strValue.c_str());
	    			geneNode->append_attribute(doc.allocate_attribute(pchName, pchValue ));
	    			break;
	    		}
	    	}
	    	break;
	    }
	}

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);

}


void Genome::SetXML(std::string input_xml){
	m_strXML = input_xml;
}


void Genome::FillWithRandomData(){
    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

    std::string strRandomData;


	for (rapidxml::xml_node<>* child = rootNode->first_node("Chromosome"); child; child = child->next_sibling("Chromosome"))
	{
		std::string strEncoding = child->first_attribute("encoding")->value();
		if(strEncoding == "binary"){
			//std::cout << "putting random data in binary genes" << std::endl;
			BinaryEncoding cBinaryEncoding;
			Encoding& rEncoding = cBinaryEncoding;
			FillGenes(doc, child, rEncoding);


		}
		else if(strEncoding == "value"){
			//std::cout << "putting random data in value genes" << std::endl;
			ValueEncoding cValueEncoding;
			Encoding& rEncoding = cValueEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "integer"){
			//std::cout << "putting random data in value genes" << std::endl;
			IntegerEncoding cIntegerEncoding;
			Encoding& rEncoding = cIntegerEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "tree"){
			//std::cout << "putting random data in tree genes" << std::endl;
			TreeEncoding cTreeEncoding;
			Encoding& rEncoding = cTreeEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "alphanum"){
			//std::cout << "putting random data in tree genes" << std::endl;
			AlphanumEncoding cAlphanumEncoding;
			Encoding& rEncoding = cAlphanumEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else{
			std::cout << "unknown encoding type" << std::endl;
		}


	}

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);

}

void Genome::FillGenes(rapidxml::xml_document<>& doc, rapidxml::xml_node<>* chromosomeNode, Encoding& encoding){
	for (rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene"))
	{
		char* pchRandomData = doc.allocate_string(encoding.RandomData(geneNode).c_str());
		geneNode->value(pchRandomData);

	}

}
