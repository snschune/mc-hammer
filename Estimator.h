/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 */

#ifndef _ESTIMATOR_HEADER_
#define _ESTIMATOR_HEADER_

#include <iostream>
#include <vector>
#include <memory> 

using std::vector;
using std::string;

class Estimator {
  protected:
    double currentHistTally;
    double histTally;
    double histTallySqr;

  public:
    Estimator(): currentHistTally(0.0) , histTally(0.0) , histTallySqr(0.0) {}; 
   ~Estimator() {};
    
    // set/gets
    double getCurrentHistTally()   { return( currentHistTally ); };
    double getHistTally()    	   { return( histTally        ); };
    double getHistTallySqr() 	   { return( histTallySqr     ); };
    
    // estimator methods
    void endHist();
    std::pair < double , double > getScalarEstimator(unsigned long long);
    
    // virtual estimator methods
    virtual void score( double val);

};

class SurfaceTally : public Estimator {
  public:
    SurfaceTally(): Estimator() {};
   ~SurfaceTally() {};
    
    void score();
};

class SurfaceFluxTally : public Estimator {
  public:
    SurfaceFluxTally(): Estimator() {};
   ~SurfaceFluxTally() {};
    
    void score(double mu);
};


class CollisionTally : public Estimator {
  public:
    CollisionTally(): Estimator() {};
   ~CollisionTally() {};
    
    void score(double xs);
};

#endif
