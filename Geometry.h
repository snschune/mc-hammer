/*
 Author: ESGonzalez
 Date: 1/8/18
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <memory>
#include <utility>

#include "Random.h"
#include "QuadSolver.h"
#include "Point.h"
#include "Cell.h"
#include "Surface.h"

using std::vector;

typedef std::shared_ptr<Cell> Cell_ptr;

class Geometry
{
 private:
  vector< Cell >    cells;
  vector< surface > surfaces;
  vector< Material > materials;
    
 public:
  bool        amIHere( point, Cell );
  Cell_ptr    whereAmI( point );
    
  void addCell( Cell );
  void addSurface( surface );
  void addMaterial( Material );
};

#endif
