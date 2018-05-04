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

class EstimatorCollection {

  protected:
    int                            size;
    vector <int>                   binSizes;
    std::map < string , Bin_ptr >  attributes;
    vector   < Estimator_ptr    >  estimators;
    
    void scoreTally(Part_ptr , double d); 

  public:
    
    // This allows EventHandler to pass in the correct multiplier
    // corresponding to the estimator type
    enum class EstimatorType {
      SurfaceCurrent ,
      SurfaceFluence , 
      TrackLength    ,
      Collision
    };

    // this holds the type 
    EstimatorType type;
    
    EstimatorType getType() { return(type); };

    EstimatorCollection(std::map< string , Bin_ptr > attributesin , EstimatorType t);
   ~EstimatorCollection() {};

    // find index of estimator to score
    // the second boolean value in the pair is true of the particle has all it's 
    // attributes within the range of binning structures for this tally
    int getLinearIndex(Part_ptr p);

    // score a tally in the correct bin, with a given multiplier
    void score(Part_ptr p, double multiplier);

    void endHist();
    
};


#endif
