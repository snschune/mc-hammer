//
//  Tet.cpp
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include <stdio.h>
#include "Tet.h"
#include <iostream>

//default cstr initializes a tet of zero size

Tet::Tet(point p)
{
  vert1 = p;
  vert2 = p;
  vert3 = p;
  vert4 = p;
}

point Tet:: getVert1()
{
  return vert1;
}

point Tet:: getVert2()
{
  return vert2;
}

point Tet:: getVert3()
{
  return vert3;
}

point Tet:: getVert4()
{
  return vert4;
}

void Tet:: setVertices(std::shared_ptr<point> p1,std::shared_ptr<point> p2,
                       std::shared_ptr<point> p3,std::shared_ptr<point> p4)
{
  vert1 = *p1;
  vert2 = *p2;
  vert3 = *p3;
  vert4 = *p4;
}

int Tet:: getID()
{
  return TetID;
}



