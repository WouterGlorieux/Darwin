/*
 * Vertices.cpp
 *
 *  Created on: 14-mrt.-2012
 *      Author: woutergl
 */

#include "Vertices.h"

std::string Vertices::ToString(){
	std::stringstream ss;

	for(unsigned int i = 0 ; i < m_vsVertices.size() ; i++){
		ss << "(" << m_vsVertices.at(i).nX << ";" << m_vsVertices.at(i).nY << ")";
	}
	return ss.str();
}

