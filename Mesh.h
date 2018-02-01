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
#include <memory>
#include <string>

//mesh class contains full vectors of all tets and vertices present

typedef std::shared_ptr<point> Point_ptr;
typedef std::shared_ptr<Tet> Tet_ptr;

class Mesh
{
private:
    std::vector < std::pair<int,Point_ptr> > verticesVector;
    std::vector < std::pair<int,Tet_ptr> >   tetVector;
    int numVertices;
    int numTets;
    void readFile( std::string fileName, bool loud );
    
    
public:
    Mesh( std::string fileName, bool loud );
    
    void addTet(std::pair<int,Tet_ptr> inTet);
    void addVertice(std::pair<int,Point_ptr> inVertice);
    int getTetID(std::pair<int,Tet_ptr> inTet);
    std::vector < std::pair<int,Point_ptr> > getVerticesVector();
    int getNumVertices();
    void setNumVertices(int inNumber);
    int getNumTets();
    void setNumTets(int inNumber);
    void printTets();
    void printVertices();
    Tet_ptr whereAmI( point pos );
    
};

#endif /* Mesh_h */
