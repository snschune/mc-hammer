/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class is for grouping tallies to get an answer as a function of particle attributes
 *  e.g. energy group, collision order, angle, type, etc.
 *
 * The first level of child classes derived from EstimatorCollection cannot be cast as EstimatorCollections
 *
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

typedef std::shared_ptr<surface>                           Surf_ptr;
typedef std::shared_ptr<Cell>                              Cell_ptr;
typedef std::shared_ptr<Estimator>                         Estimator_ptr;
typedef std::shared_ptr<Particle>                          Part_ptr;
typedef std::shared_ptr<ParticleAttributeBinningStructure> Bin_ptr;

/* ****************************************************************************************************** * 
 * Base Estimator Collection                                   
 * ****************************************************************************************************** */ 

class EstimatorCollection {
  protected:
    int                            size;
    vector <int>                   binSizes;
    std::map < string , Bin_ptr >  attributes;
    vector   < Estimator_ptr    >  estimators;
    
    void scoreTally(Part_ptr , double d); 

  public:
    EstimatorCollection(std::map< string , Bin_ptr > attributesin);
   ~EstimatorCollection() {};

    // find index of estimator to score
    // the second boolean value in the pair is true of the particle has all it's 
    // attributes within the range of binning structures for this tally
    int getLinearIndex(Part_ptr p);

    // interface for wrapper of scoreTally() for derived EstimatorCollection classes
    virtual void score(Part_ptr)  = 0;

    void endHist();
};

/* ****************************************************************************************************** * 
 * Collision Estimator Collection                                   
 * ****************************************************************************************************** */ 

class CollisionEstimatorCollection: public EstimatorCollection {
  public:
    CollisionEstimatorCollection(std::map< string , Bin_ptr > attributesin): EstimatorCollection(attributesin) {};
   ~CollisionEstimatorCollection() {}; 

    void score(Part_ptr p );
};

/* ****************************************************************************************************** * 
 * Surface Estimator Collection
 *  * scoring function virtual to allow for multiple inherited types for scoring on surfaces
 * ****************************************************************************************************** */ 

class SurfaceEstimatorCollection: public EstimatorCollection {
  public:
    SurfaceEstimatorCollection(std::map< string , Bin_ptr > attributesin): EstimatorCollection(attributesin) {}; 
   ~SurfaceEstimatorCollection() {};
};

class SurfaceFluenceEstimatorCollection : public SurfaceEstimatorCollection {
  public:
    SurfaceFluenceEstimatorCollection(std::map< string , Bin_ptr > attributesin): SurfaceEstimatorCollection(attributesin) {};
   ~SurfaceFluenceEstimatorCollection() {};

    void score(Part_ptr p);
};

class SurfaceCurrentEstimatorCollection : public SurfaceEstimatorCollection {
  public:
    SurfaceCurrentEstimatorCollection(std::map< string , Bin_ptr > attributesin): SurfaceEstimatorCollection(attributesin) {};
   ~SurfaceCurrentEstimatorCollection() {};
    
   void score(Part_ptr p);
};

#endif
