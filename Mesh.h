//
//  Mesh.h
//  Reader
//
//  Created by Rob Fonti on 1/18/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include "Tet.h"
#include "Point.h"
#include "Utility.h"
#include "XMLTag.h"
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>

//mesh class contains full vectors of all tets and vertices present

typedef std::shared_ptr<point> Point_ptr;
typedef std::shared_ptr<Tet> Tet_ptr;
typedef std::shared_ptr<Estimator>  Estimator_ptr;
typedef std::shared_ptr<Constants> Constants_ptr;

class Mesh
{
private:
    std::vector < std::pair<int,Point_ptr> > verticesVector;
    std::vector < Tet_ptr >   tetVector;
    std::vector < Tet_ptr > tetHist;
    std::vector< double > connectivity; // need this vector for VTK output
    std::vector< std::vector< double > > cellDataVec; // need this vector for VTK output
    int histCounter;
    int numVertices;
    int numTets;
    void readFile( std::string fileName, bool loud );
    std::string outFilename;
    std::string vtkFilename;
    Constants_ptr constants;
    
    
public:
    Mesh( std::string fileName, bool loud, Constants_ptr constantsin );
    
    void addTet(Tet_ptr inTet);
    void addVertice(std::pair<int,Point_ptr> inVertice);
    int getTetID(Tet_ptr inTet);
    std::vector < std::pair<int,Point_ptr> > getVerticesVector();
    //getThisTetVerticies();
    int  getNumVertices();
    void setNumVertices(int inNumber);
    int  getNumTets();
    void setNumTets(int inNumber);
    void printTets();
    void printVertices();
    Tet_ptr whereAmI( point pos );
    std::vector< Tet_ptr > getTets() { return tetVector; };

    // estimator interface
    void scoreTally( Particle& p , double xs );
    void endTallyHist();
    void printMeshTallies();

    // VTK (xml) interface
    void writeToVTK();
    void setVTKFilename( std::string filename ) { vtkFilename = filename; };
    void setOutFilename( std::string filename ) { outFilename = filename; };
    
};

#endif /* Mesh_h */
