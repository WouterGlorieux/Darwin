/*
 * Genome.cpp
 *
 *  Created on: 6-feb.-2012
 *      Author: woutergl
 */

#include "Genome.h"

void Genome::newGenome(const char* pchId ){

	using namespace rapidxml;
	//xml_document<> doc;

	// xml declaration
	xml_node<>* decl = m_Genome.allocate_node(node_declaration);
	decl->append_attribute(m_Genome.allocate_attribute("version", "1.0"));
	decl->append_attribute(m_Genome.allocate_attribute("encoding", "utf-8"));
	m_Genome.append_node(decl);

	// root node
	xml_node<>* root = m_Genome.allocate_node(node_element, "Genome");

	root->append_attribute(m_Genome.allocate_attribute("type", pchId));
	m_Genome.append_node(root);
/*
	// chromosome node
	xml_node<>* chromosome = m_Genome.allocate_node(node_element, "Chromosome");
	root->append_node(chromosome);

	// gene node
	xml_node<>* gene = m_Genome.allocate_node(node_element, "Gene");
	chromosome->append_node(gene);
*/
}

void Genome::addChromosome(const char* pchId ){
	using namespace rapidxml;

    xml_node<>* rootNode = m_Genome.first_node("Genome");

	// chromosome node
	xml_node<>* chromosome = m_Genome.allocate_node(node_element, "Chromosome");
	chromosome->append_attribute(m_Genome.allocate_attribute("id", pchId));
	rootNode->append_node(chromosome);


}

void Genome::addGene(const char* pchId, const char* pchChromosomeId ){
	using namespace rapidxml;

    xml_node<>* chromosome = m_Genome.first_node("Genome");

	for (xml_node<> *child = chromosome->first_node("Chromosome"); child; child = child->next_sibling("Chromosome"))
	{

	    if(child->first_attribute("id")->value() == pchChromosomeId){
	    // gene node
		xml_node<>* gene = m_Genome.allocate_node(node_element, "Gene");
		gene->append_attribute(m_Genome.allocate_attribute("id", pchId ));
		child->append_node(gene);
		break;
	    }

	}

}

std::string Genome::GetGenomeXML(){
	using namespace rapidxml;

	std::string xml_as_string;
	// watch for name collisions here, print() is a very common function name!
	print(std::back_inserter(xml_as_string), m_Genome);
	// xml_as_string now contains the XML in string form, indented
	// (in all its angle bracket glory)

	return xml_as_string;
}

void Genome::SetGenomeXML(const std::string& input_xml){
	using namespace rapidxml;
    // (input_xml contains the above XML)

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    m_Genome.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);
}

