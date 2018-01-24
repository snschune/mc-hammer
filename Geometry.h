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
#include <string>

#include "Random.h"
#include "QuadSolver.h"
#include "Point.h"
#include "Cell.h"
#include "Surface.h"
#include "Estimator.h"
#include "Source.h"

using std::vector;
using std::make_shared;

typedef std::shared_ptr<Cell> Cell_ptr;
typedef std::shared_ptr<Material> Mat_ptr;
typedef std::shared_ptr<surface> Surf_ptr;
typedef std::shared_ptr<Estimator> Estimator_ptr;
typedef std::shared_ptr<Source> Source_ptr;

class Geometry
{
private:
	vector< Cell_ptr >      cells;
	vector< Surf_ptr >      surfaces;
	vector< Mat_ptr >       materials;
	Source_ptr		    source;
	void setup( std::string filename , int num_groups, bool loud );

public:
	Geometry( std::string filename , int num_groups, bool loud );
	bool        amIHere( point, Cell_ptr);
	Cell_ptr    whereAmI( point );


	void addCell( Cell_ptr );
	void addSurface( Surf_ptr );

	vector< Cell_ptr > getCells() { return(cells); };
	Part_ptr sampleSource() { return(source->sample()); };


	
};

#endif

