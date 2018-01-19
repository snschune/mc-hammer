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
#include "Point.h"

//Tet Class includes 4 points which define a given tetrahedra
//Tets have ID's associated with them.


typedef std::shared_ptr<point> point_ptr;

class Tet
{
  private:
    int TetID;
    point vert1;
    point vert2;
    point vert3;
    point vert4;
  
 
  public:
  
    Tet(point p);
    point getVert1();
    point getVert2();
    point getVert3();
    point getVert4();
    void setVertices(std::shared_ptr<point> p1,std::shared_ptr<point> p2,
                     std::shared_ptr<point> p3,std::shared_ptr<point> p4);
  
    void addVertice(std::shared_ptr<point> inVertice);
    int getID();
  
};

#endif /* Tet_h */
