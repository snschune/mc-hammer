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
void estimator::update(Part_ptr pi , Part_ptr pf , log_ptr rxns) {};

double estimator::dist(point p1 ,point p2) {
    return std::sqrt(
                std::pow(p1.x - p2.x , 2) + 
                std::pow(p1.y - p2.y , 2) + 
                std::pow(p1.z - p2.z , 2)
                    );
};

//constructor
meshTally::meshTally(string comment, string type,  vector<int> numBins) : estimator(comment, type) {
    vector<vector<vector<double>>> setMesh(numBins.at(0),
           vector<vector<double>>(numBins.at(1),
                   vector<double>(numBins.at(2)))
           );
    mesh = setMesh;
};

//functions
void meshTally::update(Part_ptr pi , Part_ptr pf , log_ptr rxns){

};

//constructor
surfaceTally::surfaceTally(string comment , string type , Surf_ptr surfi ) : estimator(comment , type) , surf(surfi) {};

//functions
void surfaceTally::update(Part_ptr pi , Part_ptr pf , log_ptr rxns) {
    bool cross = true;
    if (cross == true) {tally++;};
};

//constructor
cellTally::cellTally(string comment , string type, Cell_ptr celli) : estimator(comment , type) , cell(celli) {
    tally = 0.0;
};

//functions
void cellTally::update(Part_ptr pi , Part_ptr pf , log_ptr rxns) {
    tally +=  dist(pi->getPos() , pf->getPos());
};

