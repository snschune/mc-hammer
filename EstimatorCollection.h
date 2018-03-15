/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class is for grouping tallies to get an answer as a function of particle attributes
 *  e.g. energy group, collision order, angle, type, etc.
 *
 *
 *  To construct an EstimatorCollection, a map from attribute name to an accessor functional is required
 *  The accessor functional is 
 */

#ifndef _ESTIMATORCOLLECTION_HEADER_
#define _ESTIMATORCOLLECTION_HEADER_

#include <functional>
#include <map>
#include <memory>

#include "Utility.h"
#include "Particle.h"
#include "Estimator.h"
#include "ParticleAttributeBinningStructure.h"

using std::vector;
using std::string;

typedef std::shared_ptr<Estimator>                         Estimator_ptr;
typedef std::shared_ptr<Particle>                          Part_ptr;
typedef std::shared_ptr<ParticleAttributeBinningStructure> Bin_ptr;

/* ****************************************************************************************************** * 
 * Base Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

class EstimatorCollection {
  protected:
    int size;

    std::map < string , Bin_ptr > attributes;
    vector   < Estimator_ptr    > estimators;

  public:
    EstimatorCollection(std::map< string , Bin_ptr > attributesin);
   ~EstimatorCollection() {};

    void score(Part_ptr p);
};

/* ****************************************************************************************************** * 
 * Collision Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

class CollisionEstimatorCollection: public EstimatorCollection {
  public:
    CollisionEstimatorCollection(std::map< string , Bin_ptr > attributesin); 
   ~CollisionEstimatorCollection() {}; 
};


/* ****************************************************************************************************** * 
 * Surface Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

class SurfaceEstimatorCollection: public EstimatorCollection {
  public:
    SurfaceEstimatorCollection(std::map< string , Bin_ptr > attributesin); 
   ~SurfaceEstimatorCollection() {}; 
};

#endif
