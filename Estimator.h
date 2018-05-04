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
    //vector < double >    histTally;
    //vector < double >    histTallySqr;
    double histTally;
    double histTallySqr;
    std::string estimatorName;

  protected:
    int collisionOrder;


    std::pair < double , double >  fluxEstimator;

  public:
    Estimator( std::string label ) : estimatorName(label) { histTally = 0.0; histTallySqr = 0.0;}; 
    ~Estimator() {};
    
    // set/gets
    virtual double getCurrentHistTally() { return( currentHistTally ); };
    virtual double getHistTally()    	   { return( histTally        ); };
    virtual double getHistTallySqr() 	   { return( histTallySqr     ); };
    virtual std::string name()           { return( estimatorName    ); };
    
    // estimator methods
    virtual void endHist();
    virtual void score(double xs);
    virtual void setCollisionOrder( int order ) { collisionOrder = order; }
    virtual int  getCollisionOrder()            { return( collisionOrder   ); }
    virtual std::pair < double , double > getScalarEstimator(unsigned long long) { return( fluxEstimator ); };

};

class MeshTally : public Estimator {
  private:
    vector < vector < vector < double > > > mesh;

  public:
    MeshTally( std::string label, vector<int> numBins ): Estimator( label ) {};
   ~MeshTally() {};

    void score(Particle& pi , Particle& pf );
};

class SurfaceTally : public Estimator {
  private:
    double   tally;
    Surf_ptr surf;

  public:
    SurfaceTally( std::string label ): Estimator( label ) {};
   ~SurfaceTally() {};
    
    void score(Particle& pi , Particle& pf );
};

class CellTally : public Estimator {
  private:
    double     tally;
    Cell_ptr   cell;

  public:
    CellTally( std::string label ): Estimator( label ) {};
   ~CellTally() {};

    void score(Particle& pi , Particle& pf);
};

class CollisionTally : public Estimator {
  private:
    double    currentHistTally;
    double    histTally;
    double    histTallySqr;
          
  public:
    CollisionTally( std::string label ): Estimator( label ) ,  currentHistTally(0.0) {histTally = 0.0; histTallySqr = 0.0; };
   ~CollisionTally() {};
      
    // set/gets
    double getCurrentHistTally()           { return( currentHistTally ); };
    double getHistTally()    		           { return( histTally        ); };
    double getHistTallySqr() 		           { return( histTallySqr     ); };
    
    // collision tally specific estimator methods
    void score(double xs);
    void endHist();
    std::pair< double , double > getScalarEstimator(unsigned long long);
};

#endif
