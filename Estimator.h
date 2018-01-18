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

  public:
     Estimator() {};
    ~Estimator() {};
    
    //utility
    double dist(point p1 ,point p2);
    
    // naming
    virtual std::string name() { return estimator_name; };
    virtual std::string type() { return estimator_type; };

    // estimator methods
    virtual void endHist();
    virtual void score(Part_ptr pi );
    virtual std::pair < double , double > getScalarEstimator();

};

class MeshTally : public Estimator {
  private:
      vector < vector < vector < double > > > mesh;
  public:
     MeshTally(vector<int> numBins); 
    ~MeshTally() {};

     void score(Part_ptr pi , Part_ptr pf );
};

class SurfaceTally : public Estimator {
    private:
        double   tally;
        Surf_ptr surf;
    public:
         SurfaceTally();
        ~SurfaceTally() {};
        
        void score(Part_ptr pi , Part_ptr pf );
};

class CellTally : public Estimator {
    private:
        double     tally;
        Cell_ptr   cell;
    public:
         CellTally();
        ~CellTally() {};

         void score(Part_ptr pi , Part_ptr pf);
};

class CollisionTally : public Estimator {
    private:
        double    currentHistTally;
        double    crossSection;

        vector < double >    histTally;
        vector < double >    histTallySqr;
            
    public:
        CollisionTally(double xsec): crossSection(xsec) {};
       ~CollisionTally() {};
        
        // set/gets
        double getCurrentHistTally()      { return( currentHistTally ); };
        vector <double> getHistTally()    { return( histTally        ); };
        vector <double> getHistTallySqr() { return( histTallySqr     ); };
        
        // collision tally specific estimator methods
        void score();
        void endHist();
        std::pair < double , double > getScalarEstimator();
};


#endif
