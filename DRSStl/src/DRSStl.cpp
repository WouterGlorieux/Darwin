//============================================================================
// Name        : DRSStl.cpp
// Author      : Wouter Glorieux
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <process.h>

struct point3D
{
	double X;
	double Y;
	double Z;
};



struct controlPoints
{
	point3D a1, a2, a3, a4;
	point3D b1, b2, b3, b4;
	point3D c1, c2, c3, c4;
	point3D d1, d2, d3, d4;
};

struct grid
{
	int X;
	int Y;
	int Z;
};

struct cube
{
	int i;
	int j;
	int k;

	  bool operator<(const cube& rhs) const
	  {
	    if(k != rhs.k){
	    	return k < rhs.k;
	    }
	    else if(j != rhs.j){
	    	return j < rhs.j;
	    }
	    else{
	    	return i < rhs.i;
	    }

	  }

	  bool operator==(const cube& rhs) const
	  {
	    return i == rhs.i && j == rhs.j && k == rhs.k;
	  }

};

enum ORIENTATION
{
	XPOS,
	XNEG,
	YPOS,
	YNEG,
	ZPOS,
	ZNEG
};

struct segment
{
	double i;
	double j;
	double k;
	ORIENTATION orientation;
};


std::vector<segment> vsSegments;

void StringExplode(std::string str, std::string separator, std::vector<std::string>* results);


controlPoints GetControlPoints(int i, int j, int k);
std::string GetSCAD(int i, int j, int k);
void SortControlPoints();
void InitializeGrid();
void ExpandGrid();
void ShiftXY(int x, int y, double Xvalue, double Yvalue);

std::string SquareToFacets(point3D a, point3D b, point3D c, point3D d, ORIENTATION orentation );
void MakeSTL(std::vector<segment> vsSegments, std::string outputFileName);
void WriteSTL(std::string outputFileName);
std::set<cube> SelectCubes();
std::vector<segment> SelectSegments(std::set<cube> setCubes);


grid sGrid;
bool abGrid[5][5][5];
bool mode2D = false;

point3D asPoints[16][16][16];			//3d array of co�rdinates of all points
std::vector<point3D> vsPoints;      //vector with all points


bool sortByX(const point3D &a, const point3D &b)
{
    return a.X < b.X;
}

bool sortByY(const point3D &a, const point3D &b)
{
    return a.Y > b.Y;
}

bool sortByZ(const point3D &a, const point3D &b)
{
    return a.Z < b.Z;
}

int main(int argc, char *argv[]) {
	std::string strFileName = "";
	std::string strOutputFileName = "";


	double dXmultiplier = 0.01;
	double dYmultiplier = 0.01;
	double dZmultiplier = 0.0001;


	if(argc == 3){
		strFileName= argv[1];
		strOutputFileName= argv[2];
	}
	else{
		std::cout << "Usage: DRSStl.exe inputFilename outputFilename" << std::endl;
		std::exit(1);
	}



	//std::cout << "loading file: " << strFileName << std::endl;
	std::ifstream t(strFileName.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::string input_xml = buffer.str() ;
	//std::ofstream output(strOutputFileName.c_str());

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    // only use xml_copy from here on!
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
    rapidxml::xml_node<>* rootNode = doc.first_node("Genome");


 //   sGrid.X = atoi(rootNode->first_attribute("gridX")->value());
 //   sGrid.Y = atoi(rootNode->first_attribute("gridY")->value());
 //   sGrid.Z = atoi(rootNode->first_attribute("gridZ")->value());

    sGrid.X = 5;
    sGrid.Y = 5;
    sGrid.Z = 5;




    int k = 0;
	for (rapidxml::xml_node<>* chromosomeNode = rootNode->first_node("Chromosome"); chromosomeNode; chromosomeNode = chromosomeNode->next_sibling("Chromosome"))
	{

		if(chromosomeNode->first_attribute("id")->value() == std::string("grid")){

			int j = 0;
			for (rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene"))
			{

				std::string strData = geneNode->value();
				for(unsigned int i = 0; i < strData.size(); i++){
					abGrid[i][j][k] = strData.at(i) == '1'? true : false ;
					//std::cout << i << "-" << j << "-" << k << ": " << abGrid[i][j][k] << std::endl;
 				}
				j++;
			}
			k++;
		}
		else{
			for (rapidxml::xml_node<>* geneNode = chromosomeNode->first_node("Gene"); geneNode; geneNode = geneNode->next_sibling("Gene"))
			{
				std::vector<std::string> vstrData;
				StringExplode(geneNode->value(), "|", &vstrData);
				point3D sPoint3D;
				sPoint3D.X = atof(vstrData.at(0).c_str()) * dXmultiplier;
				sPoint3D.Y = atof(vstrData.at(1).c_str()) * dYmultiplier;
				if(!mode2D){
					sPoint3D.Z = atof(vstrData.at(2).c_str()) * dZmultiplier;
				}
				else{
					sPoint3D.Z = 0;
				}

				//sPoint3D.X = 10.0;
				//sPoint3D.Y = 5.0;

				//std::cout << i << " " << j << std::endl;
				vsPoints.push_back(sPoint3D);

			}
		}
	}

	abGrid[0][0][0] = true;


    std::set<cube> setCubes = SelectCubes();
    std::vector<segment> vsSegments = SelectSegments(setCubes);



	//SortControlPoints();
	//ExpandGrid();

	InitializeGrid();

	MakeSTL(vsSegments, strOutputFileName);
	//WriteSTL(strOutputFileName);


	//std::cout << "done" << std::endl;
	return 0;
}


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



controlPoints GetControlPoints(int i, int j, int k){
	controlPoints sControlPoints;

	sControlPoints.a1 = asPoints[i][j][k];
	sControlPoints.a2 = asPoints[i+1][j][k];
	sControlPoints.a3 = asPoints[i+2][j][k];
	sControlPoints.a4 = asPoints[i+3][j][k];

	sControlPoints.b1 = asPoints[i][j+1][k];
	sControlPoints.b2 = asPoints[i+1][j+1][k];
	sControlPoints.b3 = asPoints[i+2][j+1][k];
	sControlPoints.b4 = asPoints[i+3][j+1][k];

	sControlPoints.c1 = asPoints[i][j+2][k];
	sControlPoints.c2 = asPoints[i+1][j+2][k];
	sControlPoints.c3 = asPoints[i+2][j+2][k];
	sControlPoints.c4 = asPoints[i+3][j+2][k];

	sControlPoints.d1 = asPoints[i][j+3][k];
	sControlPoints.d2 = asPoints[i+1][j+3][k];
	sControlPoints.d3 = asPoints[i+2][j+3][k];
	sControlPoints.d4 = asPoints[i+3][j+3][k];


	return sControlPoints;
}

std::string GetSCAD(int i, int j, int k=0){


	controlPoints sControlPoints;
	sControlPoints = GetControlPoints(i,j,k);


	std::stringstream ss;

	ss << "[[" << sControlPoints.a1.X << "," << sControlPoints.a1.Y << "," << sControlPoints.a1.Z << "], ["
			<< sControlPoints.a2.X <<"," << sControlPoints.a2.Y <<"," << sControlPoints.a2.Z << "], ["
			<< sControlPoints.a3.X << "," << sControlPoints.a3.Y << "," << sControlPoints.a3.Z << "], ["
			<< sControlPoints.a4.X << "," << sControlPoints.a4.Y << "," << sControlPoints.a4.Z << "]]";

	std::string gcp1 = ss.str();
	ss.str("");

	ss << "[[" << sControlPoints.b1.X << "," << sControlPoints.b1.Y << "," << sControlPoints.b1.Z << "], ["
			<< sControlPoints.b2.X <<"," << sControlPoints.b2.Y <<"," << sControlPoints.b2.Z << "], ["
			<< sControlPoints.b3.X << "," << sControlPoints.b3.Y << "," << sControlPoints.b3.Z << "], ["
			<< sControlPoints.b4.X << "," << sControlPoints.b4.Y << "," << sControlPoints.b4.Z << "]]";

	std::string gcp2 = ss.str();
	ss.str("");

	ss << "[[" << sControlPoints.c1.X << "," << sControlPoints.c1.Y << "," << sControlPoints.c1.Z << "], ["
			<< sControlPoints.c2.X <<"," << sControlPoints.c2.Y <<"," << sControlPoints.c2.Z << "], ["
			<< sControlPoints.c3.X << "," << sControlPoints.c3.Y << "," << sControlPoints.c3.Z << "], ["
			<< sControlPoints.c4.X << "," << sControlPoints.c4.Y << "," << sControlPoints.c4.Z << "]]";

	std::string gcp3 = ss.str();
	ss.str("");

	ss << "[[" << sControlPoints.d1.X << "," << sControlPoints.d1.Y << "," << sControlPoints.d1.Z << "], ["
			<< sControlPoints.d2.X <<"," << sControlPoints.d2.Y <<"," << sControlPoints.d2.Z << "], ["
			<< sControlPoints.d3.X << "," << sControlPoints.d3.Y << "," << sControlPoints.d3.Z << "], ["
			<< sControlPoints.d4.X << "," << sControlPoints.d4.Y << "," << sControlPoints.d4.Z << "]]";

	std::string gcp4 = ss.str();
	ss.str("");


/*	ss << "DisplayBezSurface([" << gcp1 <<  ", "
									<< gcp2 <<  ", "
									<< gcp3 << ", "
									<< gcp4
									<< "], steps=5, thickness=10);" << std::endl;
*/
/*	ss << "DisplayBezControlFrame([" << gcp1 <<  ", "
									<< gcp2 <<  ", "
									<< gcp3 << ", "
									<< gcp4
									<< "], $fn=3);" << std::endl;
*/



	//std::cout << ss.str() << std::endl;
	return ss.str();
}

void SortControlPoints(){

	std::sort(vsPoints.begin(), vsPoints.end(), sortByX);

	for(int i=sGrid.X*3; i >= 0; i--){
		std::sort(vsPoints.end()-((sGrid.Y*3+1)*(sGrid.Z*3+1)), vsPoints.end(), sortByY);
		for (int j = sGrid.Y*3 ; j >= 0; j--){
			std::sort(vsPoints.end()-(sGrid.Z*3+1), vsPoints.end(), sortByZ);
			for (int k = sGrid.Z*3 ; k >= 0; k--){
				asPoints[i][j][k] = vsPoints.at(vsPoints.size()-1);
					vsPoints.pop_back();
			}

		}
	}


}
void InitializeGrid(){
	for(int i=0; i <= sGrid.X*3; i++){
		for (int j = 0 ; j <= sGrid.Y*3 ; j++){
			for (int k = 0 ; k <= sGrid.Z*3; k++){
				point3D sPoint3D;
				sPoint3D.X = i*1;
				sPoint3D.Y = j*1;
				sPoint3D.Z = k*1;
				asPoints[i][j][k] = sPoint3D;
				//std::cout << "translate([" << sPoint3D.X << "," << sPoint3D.Y << "," << sPoint3D.Z << "]) sphere(1);" << std::endl;
			}

		}
	}


	for(int i=0; i < sGrid.X; i++){
		for (int j = 0 ; j < sGrid.Y ; j++){
			for (int k = 0 ; k <= sGrid.Z; k++){
				//std::cout <<  GetSCAD(i*3,j*3,k*3) << std::endl << std::endl;

			}

		}
	}


}

std::string SquareToFacets(point3D a, point3D b, point3D c, point3D d, ORIENTATION orientation ){
	std::stringstream ss;

	std::string strFacet = "";
	switch (orientation)
	    {
	        case XPOS:
	        	strFacet = "1 0 0";
	            break;

	        case XNEG:
	        	strFacet = "-1 0 0";
	            break;

	        case YPOS:
	        	strFacet = "0 1 0";
	            break;

	        case YNEG:
	        	strFacet = "0 -1 0";
	            break;

	        case ZPOS:
	        	strFacet = "0 0 1";
	            break;

	        case ZNEG:
	        	strFacet = "0 0 -1";
	            break;

	        default:
	            std::cout << "Unknown orientation" << std::endl;
	            break;
	    }



	ss << "facet normal " << strFacet << std::endl;
	ss << "outer loop" << std::endl;
	if(orientation == XPOS || orientation == YNEG || orientation == ZPOS){
		ss << "vertex " << b.X << " " << b.Y << " " << b.Z << std::endl;
		ss << "vertex " << a.X << " " << a.Y << " " << a.Z << std::endl;
		ss << "vertex " << c.X << " " << c.Y << " " << c.Z << std::endl;
	}
	else if(orientation == XNEG || orientation == YPOS || orientation == ZNEG){
		ss << "vertex " << a.X << " " << a.Y << " " << a.Z << std::endl;
		ss << "vertex " << b.X << " " << b.Y << " " << b.Z << std::endl;
		ss << "vertex " << c.X << " " << c.Y << " " << c.Z << std::endl;
	}
	ss << "endloop" << std::endl;
	ss << "endfacet" << std::endl;

	ss << "facet normal " << strFacet << std::endl;
	ss << "outer loop" << std::endl;
	if(orientation == XPOS || orientation == YNEG || orientation == ZPOS){
		ss << "vertex " << b.X << " " << b.Y << " " << b.Z << std::endl;
		ss << "vertex " << c.X << " " << c.Y << " " << c.Z << std::endl;
		ss << "vertex " << d.X << " " << d.Y << " " << d.Z << std::endl;
	}
	else if(orientation == XNEG || orientation == YPOS || orientation == ZNEG){
		ss << "vertex " << b.X << " " << b.Y << " " << b.Z << std::endl;
		ss << "vertex " << d.X << " " << d.Y << " " << d.Z << std::endl;
		ss << "vertex " << c.X << " " << c.Y << " " << c.Z << std::endl;
	}
	ss << "endloop" << std::endl;
	ss << "endfacet" << std::endl;

	return ss.str();
}


void ExpandGrid(){

	for(unsigned int i = 0; i < vsPoints.size(); i++){
		int x = (int) i/16;
		int y =  i % 16;

		ShiftXY(x, y, vsPoints.at(i).X, vsPoints.at(i).X);

	}
}

void ShiftXY(int x, int y, double Xvalue, double Yvalue){

	int k=1;

	for(int i = x; i < sGrid.X; i++){
		//for(int j = 0; j < sGrid.Y; j++){
			asPoints[i][y][k].X += Xvalue;
		//}

	}

	for(int j = y; j < sGrid.Y; j++){
		//for(int i = 0; i < sGrid.X; i++){
			asPoints[x][j][k].Y += Yvalue;
		//}

	}
}

void MakeSTL(std::vector<segment> vsSegments, std::string outputFileName){
	std::ofstream output(outputFileName.c_str());
	output << "solid mystl" << std::endl;


    for(unsigned int l = 0; l < vsSegments.size(); l++ ){
    	//std::cout << vsSegments.at(l).i << "-" << vsSegments.at(l).j << "-" << vsSegments.at(l).k << " " << vsSegments.at(l).orientation << std::endl;

    	int i, j, k;
    	i = vsSegments.at(l).i;
    	j = vsSegments.at(l).j;
    	k = vsSegments.at(l).k;

    	switch (vsSegments.at(l).orientation)
    	    {
    	        case XPOS:
    	        	output << SquareToFacets(asPoints[i+1][j+1][k+1], asPoints[i+1][j+1][k], asPoints[i+1][j][k+1], asPoints[i+1][j][k], XPOS);
    	            break;

    	        case XNEG:
    	        	output << SquareToFacets(asPoints[i][j+1][k+1], asPoints[i][j+1][k], asPoints[i][j][k+1], asPoints[i][j][k], XNEG);
    	            break;

    	        case YPOS:
    	        	output << SquareToFacets(asPoints[i][j+1][k+1], asPoints[i+1][j+1][k+1], asPoints[i][j+1][k], asPoints[i+1][j+1][k], YPOS);
    	            break;

    	        case YNEG:
    	        	output << SquareToFacets(asPoints[i][j][k+1], asPoints[i+1][j][k+1], asPoints[i][j][k], asPoints[i+1][j][k], YNEG);
    	            break;

    	        case ZPOS:
    	        	output << SquareToFacets(asPoints[i][j+1][k+1], asPoints[i+1][j+1][k+1], asPoints[i][j][k+1], asPoints[i+1][j][k+1], ZPOS);
    	            break;

    	        case ZNEG:
    	        	output << SquareToFacets(asPoints[i][j+1][k], asPoints[i+1][j+1][k], asPoints[i][j][k], asPoints[i+1][j][k], ZNEG);
    	            break;

    	        default:
    	            std::cout << "Unknown orientation" << std::endl;
    	            break;
    	    }



    }


	output << "endsolid mystl" << std::endl;
	output.close();

	//std::cout << "writing " << outputFileName << std::endl;

}

void WriteSTL(std::string outputFileName){
	std::string strTempSCADfile = "temp.scad";
	std::ofstream output(strTempSCADfile.c_str());
	output << "include <bezierSurface.scad>" << std::endl;


	for(int k = 0; k < sGrid.Z ; k++ ){
		for(int j = 0; j < sGrid.Y ; j++ ){
			for(int i = 0; i < sGrid.X ; i++ ){
				if(abGrid[i][j][k] == true){
				output << GetSCAD(i,j,k) << std::endl << std::endl;
				}
			}

		}
	}

	output.close();


	std::cout << "Writing stl: " << outputFileName << std::endl;
	spawnl(P_WAIT, "c:\\Darwin\\RosettaStones\\STL\\openscad.exe", "openscad.exe", "-o", outputFileName.c_str(), "temp.scad" , NULL);


}


std::set<cube> SelectCubes(){
	cube sCube;
	std::set<cube> setCubes;


	sCube.i = 0;
	sCube.j = 0;
	sCube.k = 0;
	setCubes.insert(sCube);

	bool bCubesAdded = true;

	std::set<cube>::iterator it;
	while(bCubesAdded){
		//std::cout << setCubes.size() << std::endl;
		unsigned int nCubes = setCubes.size();
		bCubesAdded = false;
		for( it = setCubes.begin(); it != setCubes.end(); it++ ) {
			if(it->i+1 < sGrid.X && abGrid[it->i+1][it->j][it->k] == true){
				sCube.i = it->i+1;
				sCube.j = it->j;
				sCube.k = it->k;
				setCubes.insert(sCube);
			}

			if(it->j+1 < sGrid.Y && abGrid[it->i][it->j+1][it->k] == true){
				sCube.i = it->i;
				sCube.j = it->j+1;
				sCube.k = it->k;
				setCubes.insert(sCube);
			}

			if(it->k+1 < sGrid.Z && abGrid[it->i][it->j][it->k+1] == true){
				sCube.i = it->i;
				sCube.j = it->j;
				sCube.k = it->k+1;
				setCubes.insert(sCube);
			}

			if(it->i-1 >= 0 && abGrid[it->i-1][it->j][it->k] == true){
				sCube.i = it->i-1;
				sCube.j = it->j;
				sCube.k = it->k;
				setCubes.insert(sCube);
			}

			if(it->j-1 >= 0 && abGrid[it->i][it->j-1][it->k] == true){
				sCube.i = it->i;
				sCube.j = it->j-1;
				sCube.k = it->k;
				setCubes.insert(sCube);
			}

			if(it->k-1 >= 0 && abGrid[it->i][it->j][it->k-1] == true){
				sCube.i = it->i;
				sCube.j = it->j;
				sCube.k = it->k-1;
				setCubes.insert(sCube);
			}
		}


		if(nCubes < setCubes.size()){
			bCubesAdded = true;
		}
	}

	return setCubes;
}


std::vector<segment> SelectSegments(std::set<cube> setCubes){
	std::vector<segment> vsSegments;
	std::set<cube>::iterator it;
	std::set<cube>::const_iterator cit;

	for( it = setCubes.begin(); it != setCubes.end(); it++ ) {
		//std::cout << it->i << "-" << it->j << "-" << it->k << std::endl;

		segment sSegment;
		sSegment.i = it->i;
		sSegment.j = it->j;
		sSegment.k = it->k;

		cube adjCube;
		adjCube.i = it->i+1;
		adjCube.j = it->j;
		adjCube.k = it->k;

		cit = setCubes.find(adjCube) ;
		if(cit == setCubes.end()){
			sSegment.orientation = XPOS;
			vsSegments.push_back(sSegment);
		}

		adjCube.i = it->i;
		adjCube.j = it->j+1;
		adjCube.k = it->k;

		cit = setCubes.find(adjCube) ;
		if(cit == setCubes.end()){
			sSegment.orientation = YPOS;
			vsSegments.push_back(sSegment);
		}

		adjCube.i = it->i;
		adjCube.j = it->j;
		adjCube.k = it->k+1;

		cit = setCubes.find(adjCube) ;
		if(cit == setCubes.end()){
			sSegment.orientation = ZPOS;
			vsSegments.push_back(sSegment);
		}

		adjCube.i = it->i-1;
		adjCube.j = it->j;
		adjCube.k = it->k;

		cit = setCubes.find(adjCube) ;
		if(cit == setCubes.end()){
			sSegment.orientation = XNEG;
			vsSegments.push_back(sSegment);
		}

		adjCube.i = it->i;
		adjCube.j = it->j-1;
		adjCube.k = it->k;

		cit = setCubes.find(adjCube) ;
		if(cit == setCubes.end()){
			sSegment.orientation = YNEG;
			vsSegments.push_back(sSegment);
		}

		adjCube.i = it->i;
		adjCube.j = it->j;
		adjCube.k = it->k-1;

		cit = setCubes.find(adjCube) ;
		if(cit == setCubes.end()){
			sSegment.orientation = ZNEG;
			vsSegments.push_back(sSegment);
		}

	}

	return vsSegments;

}

