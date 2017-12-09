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


//constructor
CollisionTally::CollisionTally(string comment , string type, Cell_ptr celli) : Estimator(comment , type) , cell(celli) {
    numGroups = 8; //TODO no

    currentHistTally.resize(numGroups);
    histTally.resize(numGroups);
    histTallySqr.resize(numGroups);
};

//functions
void CollisionTally::score(int groupi ) {
     currentHistTally.at(groupi-1)  +=  1.0;
};

void CollisionTally::newHist() {
    
    vector <double> squares;
    
    // for each group, get the square of the tally in this history
    for (int group = 1; group < numGroups;  ++group) {
        squares.push_back(pow(currentHistTally.at(group-1),2));
    }

    // for each group, append the current history tally and square tally to their tracking vectors
    for (int group = 1; group < numGroups;  ++group) {
        histTally.at(group-1).push_back( currentHistTally.at(group-1) );
        histTallySqr.at(group-1).push_back( squares.at(group-1)       );
    }
};

        
VectorEstimator CollisionTally::getFlux() {
    
    vector <double> flux(numGroups);
    vector <double> unce(numGroups);
   
    
    // for each group sum the tallies and square tallies over the histories
    for (int group = 1; group < numGroups;  ++group) {
        flux.at(group-1) = std::accumulate(histTally.at(group-1).begin(), histTally.at(group-1).end(), 0);
        unce.at(group-1) = std::accumulate(histTallySqr.at(group-1).begin(), histTallySqr.at(group-1).end(), 0);
    }

    // for each group find the uncertainty
    for (int group = 1; group < numGroups;  ++group) {
        unce.at(group-1) = pow(flux.at(group-1),2) - unce.at(group-1);
    }
    
    VectorEstimator fluxEstimator;

    fluxEstimator.value = flux;
    fluxEstimator.uncertainty = unce;

    return(fluxEstimator);
    
};


