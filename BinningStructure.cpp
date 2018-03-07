#include "BinningStructure.h"


/* ****************************************************************************************************** * 
 * Inherited binning structure for binning by energy group
 *
 * ****************************************************************************************************** */ 

int GroupBinningStructure::getSize() {
  return(size);
};

std::pair< int , bool> GroupBinningStructure::getIndex(int group) { 
// get the EstimatorCollection index for a particle in a particular energy group
  std::pair<int , bool> out;
  out.first  = 0;
  out.second = true;
  return(out);
};

/* ****************************************************************************************************** * 
 * Inherited binning structure for binning by collision order
 *
 * ****************************************************************************************************** */ 


int CollisionOrderBinningStructure::getSize() {
  return(size);
};

std::pair< int , bool> CollisionOrderBinningStructure::getIndex( int collisionOrder ) {
// get the EstimatorCollection index of a particle that has collided 'collisionOrder' times
  std::pair< int , bool > out;
  out.first  = collisionOrder - minOrder;
  out.second = true;
  if( collisionOrder > maxOrder ) {
    out.second = false;
  }
  return(out);
};

/* ****************************************************************************************************** * 
 * Inherited binning structure for binning by an arbitrary histogram
 *
 * ****************************************************************************************************** */ 

int HistogramBinningStructure::getSize() {
  return(numBins);
};

std::pair< int , bool> HistogramBinningStructure::getIndex( double value ) {
// get the EstimatorCollection index of a particle that has an attribute described by a double
// Using the binning structure specied in the inherited class constructor
  std::pair< int , bool > out;
  out.first = 0;
  out.second = false;
  for(int i = 0; i < numBins; ++i ) {
    if( value < binWidth * i ) {
      out.first = i;
      out.second = true;
      return(out);
    }
  }
  return(out);
  
};

