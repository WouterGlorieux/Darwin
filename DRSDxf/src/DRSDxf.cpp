//============================================================================
// Name        : DRSDxf.cpp
// Author      : Wouter Glorieux
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "dl_dxf.h"
#include "dl_creationadapter.h"

//#include "test_creationclass.h"

using namespace std;

struct point3D
{
    double x;
    double y;
    double z;

};

int main() {

    DL_Dxf* dxf = new DL_Dxf();
    DL_Codes::version exportVersion = DL_Codes::AC1015;
    DL_WriterA* dw = dxf->out("myfile.dxf", exportVersion);
    if (dw==NULL) {
        printf("Cannot open file 'myfile.dxf' \
               for writing.");
        // abort function e.g. with return
    }
    dxf->writeHeader(*dw);
    // int variable:
    dw->dxfString(9, "$INSUNITS");
    dw->dxfInt(70, 4);
    // real (double, float) variable:
    dw->dxfString(9, "$DIMEXE");
    dw->dxfReal(40, 1.25);
    // string variable:
    dw->dxfString(9, "$TEXTSTYLE");
    dw->dxfString(7, "Standard");
    // vector variable:
    dw->dxfString(9, "$LIMMIN");
    dw->dxfReal(10, 0.0);
    dw->dxfReal(20, 0.0);
    dw->sectionEnd();
    dw->sectionTables();
    dxf->writeVPort(*dw);
    dw->tableLineTypes(25);
    dxf->writeLineType(*dw, DL_LineTypeData("BYBLOCK", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BYLAYER", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CONTINUOUS", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO02W100", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO03W100", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO04W100", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("ACAD_ISO05W100", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BORDER", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BORDER2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("BORDERX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CENTER", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CENTER2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("CENTERX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHDOTX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHED", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHED2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DASHEDX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DIVIDEX2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DOT", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DOT2", 0));
    dxf->writeLineType(*dw, DL_LineTypeData("DOTX2", 0));
    dw->tableEnd();
    int numberOfLayers = 3;
    dw->tableLayers(numberOfLayers);

    dxf->writeLayer(*dw,
                   DL_LayerData("0", 0),
                   DL_Attributes(
                       std::string(""),      // leave empty
                       DL_Codes::black,        // default color
                       100,                  // default width
                       "CONTINUOUS"));       // default line style

    dxf->writeLayer(*dw,
                   DL_LayerData("mainlayer", 0),
                   DL_Attributes(
                       std::string(""),
                       DL_Codes::red,
                       100,
                       "CONTINUOUS"));

    dxf->writeLayer(*dw,
                   DL_LayerData("anotherlayer", 0),
                   DL_Attributes(
                       std::string(""),
                       DL_Codes::black,
                       100,
                       "CONTINUOUS"));

    dw->tableEnd();
    dxf->writeStyle(*dw);
    dxf->writeView(*dw);
    dxf->writeUcs(*dw);

    dw->tableAppid(1);
    dw->tableAppidEntry(0x12);
    dw->dxfString(2, "ACAD");
    dw->dxfInt(70, 0);
    dw->tableEnd();
    dxf->writeDimStyle(*dw,
                      1,
                      1,
                      1,
                      1,
                      1);

    dxf->writeBlockRecord(*dw);
    dxf->writeBlockRecord(*dw, "myblock1");
    dxf->writeBlockRecord(*dw, "myblock2");
    dw->tableEnd();
    dw->sectionEnd();
    dw->sectionBlocks();

    dxf->writeBlock(*dw, DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    dxf->writeEndBlock(*dw, "*Model_Space");

    dxf->writeBlock(*dw, DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
    dxf->writeEndBlock(*dw, "*Paper_Space");

    dxf->writeBlock(*dw, DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
    dxf->writeEndBlock(*dw, "*Paper_Space0");

    dxf->writeBlock(*dw, DL_BlockData("myblock1", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf->writeLine(), ..
    // ...
    dxf->writeEndBlock(*dw, "myblock1");

    dxf->writeBlock(*dw, DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf->writeLine(), ..
    // ...
    dxf->writeEndBlock(*dw, "myblock2");

    dw->sectionEnd();
    dw->sectionEntities();
/*
    // write all your entities..
    dxf->writePoint(
        *dw,
        DL_PointData(10.0,
                     45.0,
                     0.0),
        DL_Attributes("mainlayer", 256, -1, "BYLAYER"));
*/
/*    dxf->writeLine(
        *dw,
        DL_LineData(-5.0,   // start point
                    30.0,
                    0.0,
                    5.0,   // end point
                    30.0,
                    0.0),
        DL_Attributes("mainlayer", 256, -1, "BYLAYER"));
*/
    std::vector<point3D> vPoints;
    point3D sPoint3D;

    sPoint3D.x = 5.0;
    sPoint3D.y = 30.0;
    sPoint3D.z = 0.0;
    vPoints.push_back(sPoint3D);





    sPoint3D.x = 12.0;
    sPoint3D.y = 1.0;
    sPoint3D.z = 0.0;
    vPoints.push_back(sPoint3D);

    sPoint3D.x = 0.0;
    sPoint3D.y = 0.0;
    sPoint3D.z = 0.0;
    vPoints.push_back(sPoint3D);

/*    sPoint3D.x = 9.0;
    sPoint3D.y = 8.0;
    sPoint3D.z = 0.0;
    vPoints.push_back(sPoint3D);
*/
    sPoint3D.x = -5.0;
    sPoint3D.y = 30.0;
    sPoint3D.z = 0.0;
    vPoints.push_back(sPoint3D);

    sPoint3D.x = 5.0;
    sPoint3D.y = 30.0;
    sPoint3D.z = 0.0;
    vPoints.push_back(sPoint3D);

    int splineDegree = 3;
    bool splineClosed = true;
    int numControlPoints = vPoints.size();
    int numKnots = numControlPoints + splineDegree + 1;

    int flags;
    if (splineClosed) {
        flags = 1;
    } else {
        flags = 8;
    }

    dxf->writeSpline(
        *dw,
        DL_SplineData(splineDegree,
            numKnots,
            numControlPoints,
            flags),
            DL_Attributes("mainlayer", 256, -1, "BYLAYER")
    );

    // write spline knots:
    int k = splineDegree + 1;
    DL_KnotData kd;
    for (int i=1; i<=numKnots; i++) {
        if (i<=k) {
            kd = DL_KnotData(0.0);
        } else if (i<=numKnots-k) {
            kd = DL_KnotData(1.0/(numKnots-2*k+1) * (i-k));
        } else {
            kd = DL_KnotData(1.0);
        }
        dxf->writeKnot(*dw, kd);
    }




    // write spline control points:
    for (int i = 0 ; i < numControlPoints ; i++) {
    	std::cout << i << std::endl;
        dxf->writeControlPoint(*dw, DL_ControlPointData(vPoints.at(i).x, vPoints.at(i).y, vPoints.at(i).z));
    }

    for (int i = 0 ; i < numControlPoints ; i++) {
        dxf->writeCircle(
                *dw,
                DL_CircleData(vPoints.at(i).x,
                		 vPoints.at(i).y,
                		 vPoints.at(i).z,
                            1.0),
                DL_Attributes("mainlayer", 256, -1, "BYLAYER")
         );

    }

    dw->sectionEnd();
    dxf->writeObjects(*dw);
    dxf->writeObjectsEnd(*dw);
    dw->dxfEOF();
    dw->close();
    delete dw;
    delete dxf;





	cout << "" << endl; // prints 
	return 0;
}
