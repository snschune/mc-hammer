//
//  Tet.h
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#ifndef Tet_h
#define Tet_h

#include <vector>
#include <iostream>
#include <memory>
#include "Point.h"
#include "Utility.h"

//Tet Class includes 4 points which define a given tetrahedra
//Tets have ID's associated with them.


typedef std::shared_ptr<point> point_ptr;

class Tet
{
private:
    int    TetID;
    double d0; //sign of the D0 deternminant (false = negative, true = positive)
    std::vector< double > vert1;
    std::vector< double > vert2;
    std::vector< double > vert3;
    std::vector< double > vert4;
    
public:
    
    Tet(point p);
    std::vector< double > getVert1();
    std::vector< double > getVert2();
    std::vector< double > getVert3();
    std::vector< double > getVert4();
    void setVertices(std::shared_ptr<point> p1, std::shared_ptr<point> p2,
                     std::shared_ptr<point> p3, std::shared_ptr<point> p4);
    
    void addVertice(std::shared_ptr<point> inVertice);
    int getID();
    std::vector< double > pointFourVec( point p );
    bool amIHere( point p );
    
};

#endif /* Tet_h */
