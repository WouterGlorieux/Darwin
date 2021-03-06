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

	root->append_attribute(doc.allocate_attribute("generation", pchId));
	doc.append_node(root);

	Genome::Save(doc);
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

	        case ENCODING_INTEGER:
	        	strEncoding = "integer";
	            break;

	        case ENCODING_DOUBLE:
	        	strEncoding = "double";
	            break;

	        case ENCODING_ALPHANUM:
	        	strEncoding = "alphanum";
	            break;

	        case ENCODING_CUSTOM:
	        	strEncoding = "custom";
	            break;

	        case ENCODING_LIST:
	        	strEncoding = "list";
	            break;

	        default:
	            std::cout << "Unknown encoding type" << std::endl;
	            break;
	    }

	chromosome->append_attribute(doc.allocate_attribute("encoding", strEncoding.c_str()));
	rootNode->append_node(chromosome);

	Genome::Save(doc);

}

void Genome::addGene(std::string strChromosomeId ){

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
		child->append_node(gene);

		break;
	    }

	}

	Genome::Save(doc);

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

	Genome::Save(doc);

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

	Genome::Save(doc);

}

void Genome::AddVertices(std::string strChromosomeId, std::vector<Vertex> vertices){
    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	for (rapidxml::xml_node<> *chromosomeNode = rootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{
	    if(chromosomeNode->first_attribute("id")->value() == strChromosomeId){
	    // vertices node
		rapidxml::xml_node<>* verticesNode = doc.allocate_node(rapidxml::node_element, "Vertices");

		Vertices cVertices(vertices);
		char* pchRandomData = doc.allocate_string(cVertices.ToString().c_str());
		verticesNode->value(pchRandomData);

		chromosomeNode->append_node(verticesNode);

		break;
	    }

	}

	Genome::Save(doc);
}
void Genome::AddEdges(std::string strChromosomeId, std::vector<Edge> edges){
    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	for (rapidxml::xml_node<> *chromosomeNode = rootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{
	    if(chromosomeNode->first_attribute("id")->value() == strChromosomeId){
	    // edges node
		rapidxml::xml_node<>* edgesNode = doc.allocate_node(rapidxml::node_element, "Vertices");

		Edges cEdges(edges);
		char* pchRandomData = doc.allocate_string(cEdges.ToString().c_str());
		edgesNode->value(pchRandomData);

		chromosomeNode->append_node(edgesNode);

		break;
	    }

	}

	Genome::Save(doc);
}


void Genome::SetXML(std::string input_xml){
	m_strXML = input_xml;
}

int Genome::GetGeneration(){

	int nGeneration = 0;

    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

    nGeneration = rootNode->first_attribute("generation") ? atoi(rootNode->first_attribute("generation")->value()) : 1;

	return nGeneration;
}

void Genome::SetFitness(double fitness){
	std::stringstream ss;
	ss << fitness;

    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

    char* pchData = doc.allocate_string(ss.str().c_str());
    if(rootNode->first_attribute("fitness")){
    	rootNode->first_attribute("fitness")->value(pchData);
    }
    else{
    	rootNode->append_attribute(doc.allocate_attribute("fitness", pchData ));
    }

    Genome::Save(doc);

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
		else if(strEncoding == "integer"){
			//std::cout << "putting random data in integer genes" << std::endl;
			IntegerEncoding cIntegerEncoding;
			Encoding& rEncoding = cIntegerEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "double"){
			//std::cout << "putting random data in double genes" << std::endl;
			DoubleEncoding cDoubleEncoding;
			Encoding& rEncoding = cDoubleEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "alphanum"){
			//std::cout << "putting random data in alphanum genes" << std::endl;
			AlphanumEncoding cAlphanumEncoding;
			Encoding& rEncoding = cAlphanumEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "custom"){
			//std::cout << "putting random data in custom genes" << std::endl;
			CustomEncoding cCustomEncoding;
			if(child->first_attribute("chars")){
				std::string	strCharacters = child->first_attribute("chars")->value();
				cCustomEncoding.SetChars(strCharacters);
			}
			Encoding& rEncoding = cCustomEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else if(strEncoding == "list"){
			//std::cout << "putting random data in list genes" << std::endl;
			ListEncoding cListEncoding;
			Encoding& rEncoding = cListEncoding;
			FillGenes(doc, child, rEncoding);
		}
		else{
			std::cout << "unknown encoding type" << std::endl;
		}


	}

	Genome::Save(doc);

}

void Genome::FillGenes(rapidxml::xml_document<>& doc, rapidxml::xml_node<>* chromosomeNode, Encoding& encoding){
	for (rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene"))
	{
		char* pchRandomData = doc.allocate_string(encoding.RandomData(chromosomeNode).c_str());
		geneNode->value(pchRandomData);

	}


}

void Genome::Save(rapidxml::xml_document<>& doc){
	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	//set m_strXML to string value
	SetXML(xml_as_string);
}

void Genome::DoMutations(MutationChances mutationChances){
	//std::cout << "starting mutations" << std::endl;

	rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(m_strXML.begin(), m_strXML.end());
    xml_copy.push_back('\0');

    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");

	for (rapidxml::xml_node<>* chromosomeNode = rootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{
		std::string strEncoding = chromosomeNode->first_attribute("encoding")->value();

		//do chromosome mutations
		ChromosomeMutation cChromosomeMutation(chromosomeNode);
		if(strEncoding == "binary"){
			ChromosomeMutations(chromosomeNode, cChromosomeMutation, mutationChances.BinaryMutationChance);
		}
		else if(strEncoding == "integer"){
			ChromosomeMutations(chromosomeNode, cChromosomeMutation, mutationChances.IntegerMutationChance);
		}
		else if(strEncoding == "double"){
			ChromosomeMutations(chromosomeNode, cChromosomeMutation, mutationChances.DoubleMutationChance);
		}
		else if(strEncoding == "alphanum"){
			ChromosomeMutations(chromosomeNode, cChromosomeMutation, mutationChances.AlphanumMutationChance);
		}
		else if(strEncoding == "custom"){
			ChromosomeMutations(chromosomeNode, cChromosomeMutation, mutationChances.CustomMutationChance);
		}
		else if(strEncoding == "list"){
			ChromosomeMutations(chromosomeNode, cChromosomeMutation, mutationChances.ListMutationChance);
		}
		else{
			std::cout << "unknown encoding type" << std::endl;
		}

		//do gene mutations for each gene in this chromosome
		for (rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene"))
		{
			if(strEncoding == "binary"){
				BitMutation cBitMutation(geneNode->value(), chromosomeNode);
				Mutation& rMutation = cBitMutation;
				GeneMutations(doc, geneNode, rMutation, mutationChances.BinaryMutationChance);
			}
			else if(strEncoding == "integer"){
				IntegerMutation cIntegerMutation(geneNode->value(), chromosomeNode);
				Mutation& rMutation = cIntegerMutation;
				GeneMutations(doc, geneNode, rMutation, mutationChances.IntegerMutationChance);
			}
			else if(strEncoding == "double"){
				DoubleMutation cDoubleMutation(geneNode->value(), chromosomeNode);
				Mutation& rMutation = cDoubleMutation;
				GeneMutations(doc, geneNode, rMutation, mutationChances.DoubleMutationChance);
			}
			else if(strEncoding == "alphanum"){
				AlphanumMutation cAlphanumMutation(geneNode->value(), chromosomeNode);
				Mutation& rMutation =  cAlphanumMutation;
				GeneMutations(doc, geneNode, rMutation, mutationChances.AlphanumMutationChance);
			}
			else if(strEncoding == "custom"){
				CustomMutation cCustomMutation(geneNode->value(), chromosomeNode);
				Mutation& rMutation = cCustomMutation;
				GeneMutations(doc, geneNode, rMutation, mutationChances.CustomMutationChance);
			}
			else if(strEncoding == "list"){
				ListMutation cListMutation(geneNode->value(), chromosomeNode);
				Mutation& rMutation = cListMutation;
				GeneMutations(doc, geneNode, rMutation, mutationChances.ListMutationChance);
			}
			else{
				std::cout << "unknown encoding type" << std::endl;
			}
		}
	}

	Genome::Save(doc);
}

void Genome::GeneMutations(rapidxml::xml_document<>& doc, rapidxml::xml_node<>* geneNode, Mutation& mutation, MutationChance mutationChance){

		char* pchMutatedData;

		int nLow = 0;
		int nHigh = RAND_MAX;

		double dRandom;


		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dBitString){
			pchMutatedData = doc.allocate_string(mutation.BitString().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dFlipBits){
			pchMutatedData = doc.allocate_string(mutation.FlipBits().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dBoundary){
			pchMutatedData = doc.allocate_string(mutation.Boundary().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dUniform){
			pchMutatedData = doc.allocate_string(mutation.Uniform().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dGaussian){
			pchMutatedData = doc.allocate_string(mutation.Gaussian(mutationChance.dGaussianSigma).c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dDuplication){
			pchMutatedData = doc.allocate_string(mutation.Duplication().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dDeletion){
			pchMutatedData = doc.allocate_string(mutation.Deletion().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dInsertion){
			pchMutatedData = doc.allocate_string(mutation.Insertion().c_str());
			geneNode->value(pchMutatedData);
		}

		dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
		dRandom = dRandom * 100;
		if(dRandom <=  mutationChance.dSwap){
			pchMutatedData = doc.allocate_string(mutation.Swap().c_str());
			geneNode->value(pchMutatedData);
		}

}

void Genome::ChromosomeMutations(rapidxml::xml_node<>* chromosomeNode, ChromosomeMutation& mutation, MutationChance mutationChance){
	int nLow = 0;
	int nHigh = RAND_MAX;

	bool variableGenes = true;
	if(chromosomeNode->first_attribute("genes")){
		variableGenes = false;
	}

	double dRandom;
	dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
	dRandom = dRandom * 100;
	if(variableGenes && dRandom <=  mutationChance.dGeneDuplication){
		mutation.Duplication();
	}

	dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
	dRandom = dRandom * 100;
	if(variableGenes && dRandom <=  mutationChance.dGeneDeletion){
		mutation.Deletion();
	}

	dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
	dRandom = dRandom * 100;
	if(variableGenes && dRandom <=  mutationChance.dGeneInsertion){
		mutation.Insertion();
	}

	dRandom = (double)((rand() % (nHigh - nLow + 1)) + nLow)/nHigh;
	dRandom = dRandom * 100;
	if(dRandom <=  mutationChance.dGeneSwap){
		mutation.Swap();
	}
}
