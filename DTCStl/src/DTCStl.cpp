//============================================================================
// Name        : DTCStl.cpp
// Author      : Wouter Glorieux
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <String>
#include <vector>
#include <fstream>
#include <math.h>

class data // 3 vertices of each triangle
{
public:
    float x1,y1,z1;
    float x2,y2,z2;
    float x3,y3,z3;
};

struct point3D
{
	double x;
	double y;
	double z;
};


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

double Distance(point3D targetCenter, point3D centerMass){
	double xd = centerMass.x-targetCenter.x;
	double yd = centerMass.y-targetCenter.y;
	double zd = centerMass.z-targetCenter.z;

	double distance = sqrt(xd*xd + yd*yd + zd*zd);

	return distance;
}

enum volumeMode
{
	NOVOLUME = 0,
	MINVOLUME = 1,
	MAXVOLUME = 2,
	VOLUME = 3
};

enum centerMassMode
{
	NOCENTERMASS = 0,
	MINCENTERMASS = 1,
	MAXCENTERMASS = 2

};

int main(int argc, char *argv[]) {

	std::string strFileName = "";

	volumeMode nVolumeMode = NOVOLUME;
	double dTargetVolume = 0;

	centerMassMode nCenterMassMode = NOCENTERMASS;

	point3D sTargetCenter;
	sTargetCenter.x = 0;
	sTargetCenter.y = 0;
	sTargetCenter.z = 0;


	bool bVerbose = false;
	if(argc >= 2){
		strFileName= argv[1];

		for(int i = 2; i < argc; i++){
			//std::cout << argv[i] << std::endl;
			std::string arg = argv[i];

			if(arg == std::string("-verbose")){
				bVerbose = true;
			}
			else if(arg == std::string("-minvolume")){
				nVolumeMode = MINVOLUME;
			}
			else if(arg == std::string("-maxvolume")){
				nVolumeMode = MAXVOLUME;
			}
			else if(arg.substr(0,8) ==  std::string("-volume:")){
				dTargetVolume = atof(arg.substr(8, arg.size()).c_str());
				nVolumeMode = VOLUME;
			}
			else if(arg.substr(0,9) ==  std::string("-Xcenter:")){
				sTargetCenter.x = atof(arg.substr(9, arg.size()).c_str());
				nCenterMassMode = MINCENTERMASS;
			}
			else if(arg.substr(0,9) ==  std::string("-Ycenter:")){
				sTargetCenter.y = atof(arg.substr(9, arg.size()).c_str());
				nCenterMassMode = MINCENTERMASS;
			}
			else if(arg.substr(0,9) ==  std::string("-Zcenter:")){
				sTargetCenter.z = atof(arg.substr(9, arg.size()).c_str());
				nCenterMassMode = MINCENTERMASS;
			}
			else if(arg ==  std::string("-maxcentermass")){
				nCenterMassMode = MAXCENTERMASS;
			}
		}
	}

	else{
		std::cout << "Usage: DTCStl.exe inputFilename  [-verbose] [-minvolume , -maxvolume, -volume:volume] [-Xcenter:x] [-Ycenter:y] [-Zcenter:Z] [-maxcentermass] " << std::endl;
		exit(0);
	}


	if(bVerbose && nCenterMassMode){
		std::cout << "Target center X: " << sTargetCenter.x;
		std::cout << " Y: "<< sTargetCenter.y;
		std::cout << " Z: "<< sTargetCenter.z << std::endl;
	}


    // ifstream is used for reading files
    // We'll read from a file called Sample.dat
    std::ifstream inf(strFileName.c_str());

    // If we couldn't open the input file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << strFileName << " could not be opened for reading!" << std::endl;
        exit(0);
    }


    std::vector<data> vcData;
    // While there's still stuff left to read
    while (inf)
    {
        // read stuff from the file into a string and print it
        std::string strInput;
        std::getline(inf, strInput);
        std::vector<std::string> vstrData;
        if(strInput != ""){
        	StringExplode(strInput, " ", &vstrData);

        	if(vstrData.at(0) == std::string("vertex")){
        		data cData;
        		cData.x1 = atof(vstrData.at(1).c_str());
        		cData.x2 = atof(vstrData.at(2).c_str());
        		cData.x3 = atof(vstrData.at(3).c_str());
        		vstrData.clear();

        		std::getline(inf, strInput);
        		StringExplode(strInput, " ", &vstrData);
        		cData.y1 = atof(vstrData.at(1).c_str());
        		cData.y2 = atof(vstrData.at(2).c_str());
        		cData.y3 = atof(vstrData.at(3).c_str());
        		vstrData.clear();

        		std::getline(inf, strInput);
        		StringExplode(strInput, " ", &vstrData);
        		cData.z1 = atof(vstrData.at(1).c_str());
        		cData.z2 = atof(vstrData.at(2).c_str());
        		cData.z3 = atof(vstrData.at(3).c_str());
        		vstrData.clear();

        		vcData.push_back(cData);

        	}


        }
    }

    inf.close();

    int numTriangles = vcData.size(); // pull in the STL file and determine number of triangles
    data* triangles = new data[numTriangles];


    // fill the triangles array with the data in the STL file
    for(unsigned int i=0; i < vcData.size(); i++){
    	triangles[i] = vcData.at(i);
    }


    double totalVolume = 0, currentVolume;
    double xCenter = 0, yCenter = 0, zCenter = 0;

    for (int i = 0; i < numTriangles; i++)
    {
        totalVolume += currentVolume = (triangles[i].x1*triangles[i].y2*triangles[i].z3 - triangles[i].x1*triangles[i].y3*triangles[i].z2 - triangles[i].x2*triangles[i].y1*triangles[i].z3 + triangles[i].x2*triangles[i].y3*triangles[i].z1 + triangles[i].x3*triangles[i].y1*triangles[i].z2 - triangles[i].x3*triangles[i].y2*triangles[i].z1) / 6;
        xCenter += ((triangles[i].x1 + triangles[i].x2 + triangles[i].x3) / 4) * currentVolume;
        yCenter += ((triangles[i].y1 + triangles[i].y2 + triangles[i].y3) / 4) * currentVolume;
        zCenter += ((triangles[i].z1 + triangles[i].z2 + triangles[i].z3) / 4) * currentVolume;
    }

    if(bVerbose){
    	std::cout << "Total Volume = " << totalVolume << std::endl;
    	std::cout << "X center = " << xCenter/totalVolume << std::endl;
    	std::cout << "Y center = " << yCenter/totalVolume << std::endl;
    	std::cout << "Z center = " << zCenter/totalVolume << std::endl;
    }


    point3D sCenterMass;
    sCenterMass.x = xCenter/totalVolume;
    sCenterMass.y = yCenter/totalVolume;
    sCenterMass.z = zCenter/totalVolume;




    delete[] triangles;


    int nScore = 0;

    double centerMassScore = 0;

    switch (nCenterMassMode)
    {

    	case 0:
    		centerMassScore = 0;
    		break;
        case 1:
        	centerMassScore = (1/Distance(sTargetCenter, sCenterMass))*10000;
            break;
        case 2:
        	centerMassScore = Distance(sTargetCenter, sCenterMass);
            break;

        default:
            std::cout << "Unknown center mass mode";
            centerMassScore = 0;
            break;
    }

    double volumeScore = 0;
    double dDeltaVolume = 0;

    switch (nVolumeMode)
    {

    	case 0:
    		volumeScore = 0;
    		break;
        case 1:
        	volumeScore = (1/totalVolume)*10000;
            break;
        case 2:
        	volumeScore = totalVolume;
            break;
        case 3:
        	dDeltaVolume = (totalVolume - dTargetVolume) >=0 ? (totalVolume - dTargetVolume) : (totalVolume - dTargetVolume)*-1;
        	//std::cout << dDeltaVolume  << " "<<  totalVolume << " " << dTargetVolume << std::endl;
        	if(dDeltaVolume <= 0.1){
        		dDeltaVolume = 0.1;
        	}
        	volumeScore = (1/dDeltaVolume)*10000;
            break;

        default:
            std::cout << "Unknown volume mode";
            volumeScore = 0;
            break;
    }


    nScore = (int) (centerMassScore + volumeScore);

    if(bVerbose){
    	std::cout << std::endl;
    	std::cout << "center mass score: " << centerMassScore << std::endl;
    	std::cout << "volume score : " << volumeScore << std::endl;
    	std::cout << "\n\tTOTAL SCORE: " << nScore << std::endl;
    }


	return nScore;
}
