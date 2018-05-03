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
#include <cassert>

#include "Random.h"
#include "Utility.h"
#include "Point.h"
#include "Cell.h"
#include "Surface.h"
#include "Estimator.h"
#include "Source.h"

using std::vector;
using std::make_shared;

typedef std::shared_ptr< Cell >      Cell_ptr;
typedef std::shared_ptr< Material >  Mat_ptr;
typedef std::shared_ptr< surface >   Surf_ptr;
typedef std::shared_ptr< Estimator > Estimator_ptr;
typedef std::shared_ptr< Source >    Source_ptr;
typedef std::shared_ptr< Nuclide >   Nuclide_ptr;
typedef std::shared_ptr< Reaction >  Reaction_ptr;

class Geometry
{
private:
  std::vector< Cell_ptr >      cells;
  std::vector< Surf_ptr >      surfaces;
  std::vector< Mat_ptr >       materials;
  Source_ptr                   source; // do we want to turn this into a vector?

public:
  Geometry() {};
 ~Geometry() {};

  // Adders/Setters
  void addCell     ( Cell_ptr   newCell     ) { cells.push_back(newCell);         };
  void addSurface  ( Surf_ptr   newSurface  ) { surfaces.push_back(newSurface);   };
  void addMaterial ( Mat_ptr    newMaterial ) { materials.push_back(newMaterial); };
  void setSource   ( Source_ptr newSource   ) { source = newSource;               };  

  // Getters
  std::vector< Mat_ptr >  getMaterials() { return materials; };
  std::vector< Cell_ptr > getCells()     { return cells;     };
  std::vector< Surf_ptr > getSurfaces()  { return surfaces;  };
  Source_ptr              getSource()    { return source;    };

  // Functions
  //void     readXS   ( std::string filename , int nGroups, bool loud );
  Cell_ptr whereAmI ( point pos );
  Part_ptr sampleSource() { return source->sample(); };	
};

#endif

