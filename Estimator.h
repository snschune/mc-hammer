/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 */

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
#include "Constants.h"
#include "Utility.h"

using std::vector;
using std::string;

typedef std::shared_ptr<Particle>  Part_ptr; 
typedef std::shared_ptr<Material>  Mat_ptr;
typedef std::shared_ptr<surface>   Surf_ptr;
typedef std::shared_ptr<Cell>      Cell_ptr;
typedef std::shared_ptr<point>     Point_ptr;

class Estimator {
  private:
    double               currentHistTally;
    vector < double >    histTally;
    vector < double >    histTallySqr;
    std::pair < double , double >  fluxEstimator;

  public:
     Estimator() {};
    ~Estimator() {};
    
    // set/gets
    virtual double getCurrentHistTally()      { return( currentHistTally ); };
    virtual vector <double> getHistTally()    { return( histTally        ); };
    virtual vector <double> getHistTallySqr() { return( histTallySqr     ); };
    
    // estimator methods
    virtual void endHist();
    virtual void score(double xs);
    virtual std::pair < double , double > getScalarEstimator() { return( fluxEstimator ); };

};

class MeshTally : public Estimator {
  private:
    vector < vector < vector < double > > > mesh;

  public:
    MeshTally(vector<int> numBins): Estimator() {};
   ~MeshTally() {};

    void score(Part_ptr pi , Part_ptr pf );
};

class SurfaceTally : public Estimator {
  private:
    double   tally;
    Surf_ptr surf;

  public:
    SurfaceTally(): Estimator() {};
   ~SurfaceTally() {};
    
    void score(Part_ptr pi , Part_ptr pf );
};

class CellTally : public Estimator {
  private:
    double     tally;
    Cell_ptr   cell;

  public:
    CellTally(): Estimator() {};
   ~CellTally() {};

    void score(Part_ptr pi , Part_ptr pf);
};

class CollisionTally : public Estimator {
  private:
    double              currentHistTally;
    vector< double >    histTally;
    vector< double >    histTallySqr;
          
  public:
    CollisionTally(): Estimator() ,  currentHistTally(0.0) {};
   ~CollisionTally() {};
      
    // set/gets
    double getCurrentHistTally()       { return( currentHistTally ); };
    vector< double > getHistTally()    { return( histTally        ); };
    vector< double > getHistTallySqr() { return( histTallySqr     ); };
    
    // collision tally specific estimator methods
    void score(double xs);
    void endHist();
    std::pair< double , double > getScalarEstimator();
};

#endif
