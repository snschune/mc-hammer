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
using std::make_shared;

typedef std::shared_ptr<Cell> Cell_ptr;
typedef std::shared_ptr<Material> Mat_ptr;
typedef std::shared_ptr<surface> Surf_ptr;

class Geometry
{
 private:
  vector< Cell_ptr >    cells;
  vector< Surf_ptr > surfaces;
  vector< Mat_ptr > materials;
  void setup();

 public:
	Geometry();
  bool        amIHere( point, Cell_ptr);
  Cell_ptr    whereAmI( point );
  
  
  void addCell( Cell_ptr );
  void addSurface( Surf_ptr );
  void addMaterial( Mat_ptr );
	
	
};

#endif
