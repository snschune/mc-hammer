/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 */
#include <cmath>
#include "Estimator.h"

/* ****************************************************************************************************************
 * 
 * Estimator Base Class
 *
 * ****************************************************************************************************************/
// functions
void Estimator::endHist() {
  // set the current history tally and square tally running sums
  histTally    += currentHistTally;
  histTallySqr += pow( currentHistTally , 2 );
  
  // set the current hist tally to 0
  currentHistTally = 0;
};

void Estimator::score(double val) {
  currentHistTally += val;
};

std::pair < double , double > Estimator::getScalarEstimator(unsigned long long nHist) {
// return the mean and std deviation in the score in each history
// of whatever is being tallied
    std::pair < double , double >  estimate;
    if (nHist > 1) {
        // find the standard deviation of the estimator
        double stdDev = sqrt( ( 1.0 / (nHist-1) ) * ( histTallySqr  - ( 1.0 / nHist ) * pow( histTally , 2 )  ) ); 
        estimate.first  = histTally / nHist;
        estimate.second = stdDev;
    }
    else {
        std::cout << "Not enough histories to calculate variance! Tallies unreliable." << std::endl;
        estimate.first  = 0.0;
        estimate.second = 0.0;
    }
    return(estimate);
};

/* ****************************************************************************************************************
 * 
 * Surface Tally
 *
 * ****************************************************************************************************************/


/* ****************************************************************************************************************
 * 
 * Surface Flux Tally
 *
 * ****************************************************************************************************************/
//functions
void SurfaceFluxTally::score( double mu ) {
     currentHistTally +=  1.0 / mu;
};

/* ****************************************************************************************************************
 * 
 * Collision Tally
 *
 * ****************************************************************************************************************/
//functions
void CollisionTally::score( double xs ) {
     currentHistTally +=  1.0 / xs;
};
