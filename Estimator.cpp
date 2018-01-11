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
void Estimator::score(Part_ptr pi ) {};

double Estimator::dist(point p1 ,point p2) {
    return std::sqrt(
                std::pow(p1.x - p2.x , 2) + 
                std::pow(p1.y - p2.y , 2) + 
                std::pow(p1.z - p2.z , 2)
                    );
};

//constructor
MeshTally::MeshTally(string comment, string type,  vector<int> numBins) : Estimator(comment, type) {
    vector<vector<vector<double>>> setMesh(numBins.at(0),
           vector<vector<double>>(numBins.at(1),
                   vector<double>(numBins.at(2)))
           );
    mesh = setMesh;
};

//functions
void MeshTally::score(Part_ptr pi , Part_ptr pf ){

};

//constructor
SurfaceTally::SurfaceTally(string comment , string type , Surf_ptr surfi ) : Estimator(comment , type) , surf(surfi) {};

//functions
void SurfaceTally::score(Part_ptr pi , Part_ptr pf ) {
    bool cross = true;
    if (cross == true) {tally++;};
};

//constructor
CellTally::CellTally(string comment , string type, Cell_ptr celli) : Estimator(comment , type) , cell(celli) {
    tally = 0.0;
};

//functions
void CellTally::score(Part_ptr pi , Part_ptr pf ) {
    tally +=  dist(pi->getPos() , pf->getPos());
};


//functions
void CollisionTally::score( ) {
     currentHistTally +=  1.0;
};

void CollisionTally::newHist() {
    
    //get the square of the tally in this history
    double square = pow( currentHistTally , 2 );
    
    // set the current history tally and square tally to their tracking vectors
    histTally.push_back(     currentHistTally );
    histTallySqr.push_back(  square           );
};

        
ScalarEstimator CollisionTally::getFlux() {
    
    double           flux;
    double           uncertainty;
    ScalarEstimator  fluxEstimator;
   
    
    // sum the tallies and square tallies over the histories
    flux        = std::accumulate( histTally.begin()    , histTally.end()    , 0 );
    uncertainty = std::accumulate( histTallySqr.begin() , histTallySqr.end() , 0 );

    // find the standard deviation of the estimator
    uncertainty = pow( pow(flux,2) - uncertainty  , 0.5 );

    fluxEstimator.value = flux;
    fluxEstimator.uncertainty = uncertainty;

    return(fluxEstimator);
    
};


