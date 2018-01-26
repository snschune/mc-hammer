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
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

//mesh class contains full vectors of all tets and vertices present


class Mesh
{
private:
    std::vector < std::pair<int,std::shared_ptr<point>> > verticesVector;
    std::vector < std::pair<int,std::shared_ptr<Tet>> >  tetVector;
    int numVertices;
    int numTets;
    
    
public:
    Mesh();
    void addTet(std::pair<int,std::shared_ptr<Tet>> inTet);
    void addVertice(std::pair<int,std::shared_ptr<point>> inVertice);
    int getTetID(std::pair<int,std::shared_ptr<Tet>> inTet);
    std::vector < std::pair<int,std::shared_ptr<point>> > getVerticesVector();
    int getNumVertices();
    void setNumVertices(int inNumber);
    int getNumTets();
    void setNumTets(int inNumber);
    void printTets();
    void printVertices();
    void readFile();
    
};

#endif /* Mesh_h */
