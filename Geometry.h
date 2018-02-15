<<<<<<< HEAD
#ifndef Geometry_h
#define Geometry_h
=======
/*
 Author: ESGonzalez
 Date: 1/8/18
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
>>>>>>> 76f308fcb958cd825b8124323fd7cf114ecf6a95


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
<<<<<<< HEAD
#include <stack>
#include <queue>
#include <algorithm>
#include <memory> 

#include "Random.h"
#include "QuadSolver.h"
#include "Point.h"
#include "Cell.h"
#include "Surface.h"

using std::vector;

class Geometry
{
  private:
   vector< Cell > VectOfCells;
   vector<R_ptr> CellStack;
   vector<s_ptr> SurfaceStack;

  public:
    bool same_sign(int a, double b);
    int where_am_i(P_ptr a, vector<s_ptr> &SurfaceStack, vector<R_ptr> &CellStack);
    double dist2surf(P_ptr p, vector<S_ptr> SurfaceStack);
    void update_pos(P_ptr p, double dist_traveled);
    vector<s_ptr> getSurfStack(vector < s_ptr >;
    vector<R_ptr> getCellStack(vector < R_ptr >;
    void addCell(vector<s_ptr> SurfaceStack);







#endif
=======
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

typedef std::shared_ptr< Cell >      Cell_ptr;
typedef std::shared_ptr< Material >  Mat_ptr;
typedef std::shared_ptr< surface >   Surf_ptr;
typedef std::shared_ptr< Estimator > Estimator_ptr;
typedef std::shared_ptr< Source >    Source_ptr;

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
	void addCell     ( Cell_ptr   newCell     );
	void addSurface  ( Surf_ptr   newSurface  );
	void addMaterial ( Mat_ptr    newMaterial );
	void setSource   ( Source_ptr newSource   );

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

>>>>>>> 76f308fcb958cd825b8124323fd7cf114ecf6a95
