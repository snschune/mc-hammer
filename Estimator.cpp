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
void Estimator::score(Part_ptr pi ) {};
std::pair < double , double > Estimator::getScalarEstimator() {};

double Estimator::dist(point p1 ,point p2) {
    return std::sqrt(
                std::pow(p1.x - p2.x , 2) + 
                std::pow(p1.y - p2.y , 2) + 
                std::pow(p1.z - p2.z , 2)
                    );
};


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
void CollisionTally::score( ) {
     currentHistTally +=  1.0;
};

void CollisionTally::endHist() {
    
    //get the square of the tally in this history
    double square = pow( currentHistTally , 2 );
    
    // set the current history tally and square tally to their tracking vectors
    histTally.push_back(     currentHistTally );
    histTallySqr.push_back(  square           );
    
    // set the current hist tally to 0
    currentHistTally = 0;
};

        
std::pair < double , double > CollisionTally::getScalarEstimator() {
// This function returns the mean and std deviation in the number 
// of collisions per history 

    double meanFlux;
    double sqrFlux;
    double nHist = histTally.size();

    std::pair < double , double >  fluxEstimator;
   
    // sum the tallies and square tallies over the histories
    meanFlux  = std::accumulate( histTally.begin()    , histTally.end()    , 0 ) / nHist;
    sqrFlux   = std::accumulate( histTallySqr.begin() , histTallySqr.end() , 0 );

    // find the standard deviation of the estimator
    double stdDev = pow( ( sqrFlux / nHist ) - pow( meanFlux , 2 ) ,  0.5 );

    fluxEstimator.first  = meanFlux / crossSection;
    fluxEstimator.second = stdDev;

    return(fluxEstimator); 
};


