/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class is for grouping tallies to get an answer as a function of particle attributes
 *  e.g. energy group, collision order, angle, type, etc.
 */

#include <cassert>
#include "EstimatorCollection.h"

/* ****************************************************************************************************** * 
 * Base Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

EstimatorCollection::EstimatorCollection(std::map< string , Bin_ptr > attributesin): attributes(attributesin) 
{
// default constructor calculates number of estimators required
  size = 1;
  for (const auto &vals : attributes) {
    // determine the total number of estimators
    // and the number needed for each attribute
    size *= vals.second->getSize();
    binSizes.push_back( vals.second->getSize() );
    for(int i = 0; i < vals.second->getSize(); ++i) {
      // push back an estimator pointer for each bin in this attribute
      Estimator tally;
      Estimator_ptr estimator = std::make_shared<Estimator>(tally);
      estimators.push_back(estimator);
    }
  }
};

void EstimatorCollection::endHist() {
  for(auto estimator : estimators) {
    estimator->endHist();
  }
};

int EstimatorCollection::getLinearIndex(Part_ptr p ) {
  vector<int> indices;
  for(auto const& attribute : attributes) {
    std::pair<int , bool> index = attribute.second->getIndex(p);
    if(index.second == true) {
      // if the particle attribute is within the binning range, append the index to the n-dimensional indices
      indices.push_back( index.first );
    }
    else { 
      // if one of the particle attributes is outisde the binning range, return -1 from the function 
      return(-1);
    }
  }
  return( Utility::linearizeIndices( indices ,  binSizes ) );
};

void EstimatorCollection::scoreTally(Part_ptr p  , double d) {
  int i =  getLinearIndex(p);
  if( i >= 0  ) { 
    // if the particle attributes are within the binning range
    // score the particle at the correct index
    estimators.at(i)->score(d);
  }
}

/* ****************************************************************************************************** * 
 * Collision Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

void CollisionEstimatorCollection::score(Part_ptr p) {
  // tallies 1 / the total cross section of the material the particle is currently in
  // A collision tally must be scored right after the collision is sampled
  // before altering any of the particle properties as a result of the collision
  scoreTally(p , 1.0 / p->getCell()->getMat()->getMacroXS(p) );
};

/* ****************************************************************************************************** * 
 * Surface Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

void SurfaceFluenceEstimatorCollection::score(Part_ptr p) {
  // tallies 1 / the cos of the angle between the particles direction
  // and the surface normal where it last crossed a surface
  
  scoreTally(p , 1.0 / (p->getDir() * p->getSurf()->getNormal()) );
};

void SurfaceCurrentEstimatorCollection::score(Part_ptr p) {
  // tallies 1 
  scoreTally(p , 1.0 ) ;
};
