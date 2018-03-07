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


EstimatorCollection::EstimatorCollection(std::map< string , Bin_ptr > attributesin): attributes(attributesin) {
// default constructor calculates number of estimators required
  size = 1;
  for (const auto &vals : attributes) {
    size *= vals.second->getSize();
  }
};

/* ****************************************************************************************************** * 
 * Collision Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

CollisionEstimatorCollection::CollisionEstimatorCollection(std::map< string , Bin_ptr > attributesin): EstimatorCollection(attributesin) {
  for(int i = 0; i < size; ++i) {
    CollisionTally tally;
    Estimator_ptr estimator = std::make_shared<Estimator>(tally);
    estimators.push_back(estimator);
  }
};

/* ****************************************************************************************************** * 
 * Surface Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

SurfaceEstimatorCollection::SurfaceEstimatorCollection(std::map< string , Bin_ptr > attributesin): EstimatorCollection(attributesin) {
  for(int i = 0; i < size; ++i) {
    SurfaceTally tally;
    Estimator_ptr estimator = std::make_shared<Estimator>(tally);
    estimators.push_back(estimator);
  }
};

