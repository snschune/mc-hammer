/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class will eb able to:
 *  measure the path length density of particles in a 3D mesh
 *  tally the path length density of particles in a cell
 *  tally the number of particles crossing a surface
 *
 *  Interfaces with Transport class
 *  A vector of each type of estimator will live in Geometry
 *  Cell and collision tallies belong to Cells
 *  Surface tallies belong to surfaces
 *  Mesh tallies belong to Geometry
 */

//TODO get functions, with gettally returning an uncertainty as well
//TODO add tally as private member of estimator, and getTally() as virtual public member

//TODO add energy dependence
//TODO add material specificity
//TODO add reaction type specificity

#ifndef _ESTIMATOR_HEADER_
#define _ESTIMATOR_HEADER_

#include <iostream>
#include <memory> 
#include <stack>
#include <limits>
#include <numeric>

#include "Point.h"
#include "Particle.h"  
#include "Surface.h"
#include "Cell.h"
#include "Material.h"
#include "RxnLog.h"

using std::vector;
using std::string;

typedef std::shared_ptr<Particle>  Part_ptr; //found in Particle.h -> Material.h
typedef std::shared_ptr<Material>  Mat_ptr;
typedef std::shared_ptr<surface>   Surf_ptr;
typedef std::shared_ptr<Cell>      Cell_ptr;
typedef std::shared_ptr<rxnLog>     log_ptr;
typedef std::shared_ptr<point>    Point_ptr;

struct VectorEstimator {
    vector < double > value , uncertainty;
};

struct ScalarEstimator {
    double value , uncertainty;
};

class Estimator {
  private:
    std::string estimator_name;
    std::string estimator_type;
    // energy binning
    // material

  protected:
    double dist(point p1 , point p2);

  public:
     Estimator( string comment , string type) : estimator_name(comment) , estimator_type(type) {};
    ~Estimator() {};
    
    virtual std::string name() { return estimator_name; };
    virtual std::string type() { return estimator_type; };

    virtual void score(Part_ptr pi );
};

//TODO create mesh class, use 1D array and lookup functions

class MeshTally : public Estimator {
  private:
      vector < vector < vector < double > > > mesh;
  public:
     MeshTally(string comment, string type , vector<int> numBins); 
    ~MeshTally() {};

     void score(Part_ptr pi , Part_ptr pf );
};

class SurfaceTally : public Estimator {
    private:
        double   tally;
        Surf_ptr surf;
    public:
         SurfaceTally(string comment , string type, Surf_ptr surfi );
        ~SurfaceTally() {};
        
        void score(Part_ptr pi , Part_ptr pf );
};

class CellTally : public Estimator {
    private:
        double     tally;
        Cell_ptr   cell;
    public:
         CellTally(string comment , string type , Cell_ptr celli);
        ~CellTally() {};

         void score(Part_ptr pi , Part_ptr pf);
};

class CollisionTally : public Estimator {
    private:
        vector < double >              currentHistTally;
        vector < vector < double > >   histTally;
        vector < vector < double > >   histTallySqr;
            
        int numGroups;

        Mat_ptr        mat;
        Cell_ptr       cell;
    public:
        CollisionTally(string comment , string type, Cell_ptr celli);
       ~CollisionTally() {};

        void score( int groupi );
        void newHist();

        Mat_ptr  getMat()  { return(mat);  };
        Cell_ptr getcell() { return(cell); };

        VectorEstimator getFlux();
};


#endif
