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
#include "Utility.h"
#include "Point.h"
#include "Cell.h"
#include "Surface.h"
#include "Estimator.h"
#include "Source.h"

using std::vector;
using std::make_shared;

typedef std::shared_ptr< Cell >           Cell_ptr;
typedef std::shared_ptr< Material >       Mat_ptr;
typedef std::shared_ptr< surface >        Surf_ptr;
typedef std::shared_ptr< Estimator >      Estimator_ptr;
typedef std::shared_ptr< Source >         Source_ptr;

class Geometry
{
private:
	std::vector< Cell_ptr >      cells;
	std::vector< Surf_ptr >      surfaces;
	std::vector< Mat_ptr >       materials;
	Source_ptr                   source; // do we want to turn this into a vector?

	void readXS( std::string filename , int num_groups, bool loud );

public:
	Geometry( std::string filename , int num_groups, int nhist, bool loud );
	~Geometry() {};

	// add/set
	void addCell      ( Cell_ptr   newCell     );
	void addSurface   ( Surf_ptr   newSurface  );
	void addMaterial  ( Mat_ptr    newMaterial );
	void setSource    ( Source_ptr newSource   );

	// get
	std::vector< Mat_ptr >  getMaterials() { return materials; };
	std::vector< Cell_ptr > getCells()     { return cells;     };
	std::vector< Surf_ptr > getSurfaces()  { return surfaces;  };
	Source_ptr              getSource()    { return source;    };

	// methods
	Cell_ptr whereAmI( point );
	Part_ptr sampleSource() { return source->sample(); };	
};

#endif

