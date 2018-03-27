/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 *  This is a class for storing binning structures of arbitrary particle attributes 
 *  
 *  It wraps the class template Utility::BinningStucture and adds interface get Particle attributes and setup the 
 *  binning structure, with each derived class being specific to a particle attribute
 *
 *  Should be constructed during input parsing for each type of particle attribute binning in the tally specification
 *
 */

#ifndef _PARTICLEATTRIBUTEBINNINGSTRUCTURE_HEADER_
#define _PARTICLEATTRIBUTEBINNINGSTRUCTURE_HEADER_

#include <utility>
#include <iostream>
#include <cassert>

#include "Particle.h"
#include "Utility.h"

typedef std::shared_ptr<Particle> Part_ptr;

class ParticleAttributeBinningStructure {
  protected:
    int size;
  public:
    ParticleAttributeBinningStructure(int sizein): size(sizein) {};
    virtual std::pair< int , bool>  getIndex( Part_ptr p) = 0; 
    int getSize() { return(size); };
};

/* Integer Particle Attributes */

class GroupBinningStructure : public ParticleAttributeBinningStructure {
  private:
    Utility::BinningStructure<int> binning;
  public:
    GroupBinningStructure(int numGroups): ParticleAttributeBinningStructure(numGroups) , binning(0 , numGroups , numGroups) {};
   ~GroupBinningStructure() {};
    
    std::pair< int , bool > getIndex( Part_ptr p );
};
 
class CollisionOrderBinningStructure : public ParticleAttributeBinningStructure {
  private:
    Utility::BinningStructure<int> binning;
  public:
    CollisionOrderBinningStructure(int min , int max): ParticleAttributeBinningStructure(max - min) , binning(min   , max   , 1 + max - min ) {};
    CollisionOrderBinningStructure(int order        ): ParticleAttributeBinningStructure( 1       ) , binning(order , order , 1             ) {};
   ~CollisionOrderBinningStructure() {};
    
    std::pair< int , bool > getIndex( Part_ptr p );
};

/* Continous Particle Attributes */

// all ParticleAttributeBinningStructures for continous attributes inherit from HistogramBinningStructure
class HistogramBinningStructure : public ParticleAttributeBinningStructure {
  protected:
    Utility::BinningStructure<double> binning;
  public:
    HistogramBinningStructure(double min , double max , int size): ParticleAttributeBinningStructure(size) , binning(min , max , size) {};
   ~HistogramBinningStructure() {};
    
    virtual std::pair< int , bool > getIndex( Part_ptr p ) = 0;
};

class AngleBinningStructure : public HistogramBinningStructure {
  // this class creates a HistogramBinningStructure in the cosine of the angle between a particles direction
  // and an arbitrary unit vector 'dir'
  private:
    point dir;
  public:
    AngleBinningStructure(double min, double max , int size , point dirin): HistogramBinningStructure(min , max , size) , dir( dirin / (dirin * dirin) ) {};

    std::pair< int , bool > getIndex( Part_ptr p );
};

#endif
