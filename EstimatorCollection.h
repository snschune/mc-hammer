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

typedef std::shared_ptr<Estimator>                         Estimator_ptr;
typedef std::shared_ptr<Particle>                          Part_ptr;
typedef std::shared_ptr<ParticleAttributeBinningStructure> Bin_ptr;

/* ****************************************************************************************************** * 
 * Base Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

class EstimatorCollection {
  protected:
    int                            size;
    vector <int>                   binSizes;
    std::map < string , Bin_ptr >  attributes;
    vector   < Estimator_ptr    >  estimators;
    
    void score(Part_ptr , double); 

  public:
    EstimatorCollection(std::map< string , Bin_ptr > attributesin);
   ~EstimatorCollection() {};

    // find index of estimator to score
    int  getLinearIndex(Part_ptr p);

    // interface for wrappers of score() for derived EstimatorCollection classes
    virtual void scoreCollision(Part_ptr , double)     = 0;
    virtual void scoreSurfaceCurrent(Part_ptr)         = 0;
    virtual void scoreSurfaceFluence(Part_ptr , point) = 0;

    void endHist();
};

/* ****************************************************************************************************** * 
 * Collision Estimator Collection                                   
 *  Scoring function wrapped by scoreCollision
 * ****************************************************************************************************** */ 

class CollisionEstimatorCollection: public EstimatorCollection {
  public:
    CollisionEstimatorCollection(std::map< string , Bin_ptr > attributesin): EstimatorCollection(attributesin) {};
   ~CollisionEstimatorCollection() {}; 

    void scoreCollision(Part_ptr p , double xs) { score(p , 1.0 / xs); }; // tally 1 / cross section
    void scoreSurfaceCurrent(Part_ptr)  {};
    void scoreSurfaceFluence(Part_ptr , point) {};
};

/* ****************************************************************************************************** * 
 * Surface Estimator Collection                                   
 *  scoring function virtual, lower derived classes have different wrappers
 * ****************************************************************************************************** */ 

class SurfaceEstimatorCollection: public EstimatorCollection {
  public:
    SurfaceEstimatorCollection(std::map< string , Bin_ptr > attributesin): EstimatorCollection(attributesin) {}; 
   ~SurfaceEstimatorCollection() {};
};

//const std::vector< std::string >  SurfaceEstimatorCollection::validAttributes = {"Group" , "CollisionOrder"  , "Angle" };
//const std::string  SurfaceEstimatorCollection::estimatorType = "Collision";

class SurfaceFluenceEstimatorCollection : public SurfaceEstimatorCollection {
  public:
    SurfaceFluenceEstimatorCollection(std::map< string , Bin_ptr > attributesin): SurfaceEstimatorCollection(attributesin) {};
   ~SurfaceFluenceEstimatorCollection() {};

    void scoreCollision(Part_ptr , double) {};
    void scoreSurfaceCurrent(Part_ptr)     {};
    void scoreSurfaceFluence(Part_ptr p , point surfNormal); // tally 1 /  cos of angle between p direction and surfNormal
};

class SurfaceCurrentEstimatorCollection : public SurfaceEstimatorCollection {
  public:
    SurfaceCurrentEstimatorCollection(std::map< string , Bin_ptr > attributesin): SurfaceEstimatorCollection(attributesin) {};
   ~SurfaceCurrentEstimatorCollection() {};

    void scoreCollision(Part_ptr , double)     {};
    void scoreSurfaceFluence(Part_ptr , point) {};
    void scoreSurfaceCurrent(Part_ptr p)   { score(p , 1.0); }; // tally 1 particle
};

#endif
