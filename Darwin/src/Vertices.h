/*
 * Vertices.h
 *
 *  Created on: 14-mrt.-2012
 *      Author: woutergl
 */

#ifndef VERTICES_H_
#define VERTICES_H_

#include "Globals.h"

class Vertices
{
private:

	std::vector<Vertex> m_vsVertices;

public:

	Vertices(std::vector<Vertex> vertices) // default constructor
    {
		m_vsVertices = vertices;
    }

    ~Vertices() // default deconstructor
    {

    }

    std::string ToString();

};


#endif /* VERTICES_H_ */
