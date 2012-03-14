/*
 * Edges.h
 *
 *  Created on: 14-mrt.-2012
 *      Author: woutergl
 */

#ifndef EDGES_H_
#define EDGES_H_

#include "Globals.h"

class Edges
{
private:

	std::vector<Edge> m_vsEdges;

public:

	Edges(std::vector<Edge> edges) // default constructor
    {
		m_vsEdges = edges;
    }

    ~Edges() // default deconstructor
    {

    }

    std::string ToString();

};



#endif /* EDGES_H_ */
