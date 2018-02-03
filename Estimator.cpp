/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class can:
 *  measure the path length density of particles in a 3D mesh
 *  tally the path length density of particles in a cell
 *  tally the number of particles crossing a surface
 */

//TODO add energy dependence
//TODO add material specificity
//TODO add reaction type specificity

#include <cmath>

#include "Estimator.h"

//estimator functions
void Estimator::endHist() {};
void Estimator::score(double xs) {};
//std::pair < double , double > Estimator::getScalarEstimator() {};

//functions
void MeshTally::score(Part_ptr pi , Part_ptr pf ){

};

//functions
void SurfaceTally::score(Part_ptr pi , Part_ptr pf ) {
  bool cross = true;
  if (cross == true) {tally++;};
};


//functions
void CellTally::score(Part_ptr pi , Part_ptr pf ) {
  tally +=  dist(pi->getPos() , pf->getPos());
};


//functions
void CollisionTally::score( double xs ) {
     currentHistTally +=  1.0 / xs;
};

void CollisionTally::endHist() {
  //get the square of the tally in this history
  double square = pow( currentHistTally , 2 );
  
  // set the current history tally and square tally to their tracking vectors
  //histTally.push_back(     currentHistTally );
  //histTallySqr.push_back(  square           );
	histTally += currentHistTally;
	histTallySqr += square;
  
  // set the current hist tally to 0
  currentHistTally = 0;
};

        
std::pair < double , double > CollisionTally::getScalarEstimator(unsigned long long nHist) {
// This function returns the mean and std deviation in the number 
// of collisions per history 

    //double sumFlux;
    //double sqrSumFlux;
    //double nHist = histTally.size();
    std::pair < double , double >  fluxEstimator;
    
    if (nHist > 1) {
        // sum the tallies and square tallies over the histories
        //sumFlux      = vecSum < double > ( histTally    );
        //sqrSumFlux   = vecSum < double > ( histTallySqr );

        // find the standard deviation of the estimator
        //double stdDev = pow( ( histTallySqr - pow( histTally , 2 ) / nHist ) / (nHist - 1) , 0.5);
        double stdDev = sqrt( 1.0 / nHist * ( histTallySqr / nHist - pow(histTally/nHist, 2 ))); 
        fluxEstimator.first  = histTally / nHist;
        fluxEstimator.second = stdDev;

        return(fluxEstimator); 
    }
    else {
        std::cout << "Not enough histories to calculate variance! Tallies unreliable." << std::endl;
        
        fluxEstimator.first  = 0.0;
        fluxEstimator.second = 0.0;
        
    }
    return(fluxEstimator);
};


