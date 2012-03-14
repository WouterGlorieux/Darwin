/*
 * Edges.cpp
 *
 *  Created on: 14-mrt.-2012
 *      Author: woutergl
 */

#include "Edges.h"

std::string Edges::ToString(){
	std::stringstream ss;

	for(unsigned int i = 0 ; i < m_vsEdges.size() ; i++){
		ss << "(" << m_vsEdges.at(i).nVertex1 << ";" << m_vsEdges.at(i).nVertex2 << ";" << m_vsEdges.at(i).dCost << ")";
	}
	return ss.str();
}




