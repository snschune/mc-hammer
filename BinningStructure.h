/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 *  This is a templated class for storing binning structures of arbitrary data types
 *
 *  Should be constructed in input for each type of particle attribute binning in the tally specification
 *  Is part of the constructor argument of EstimatorCollection
 *
 */

#ifndef _BINNINGSTRUCTURE_HEADER_
#define _BINNINGSTRUCTURE_HEADER_

#include <utility>
#include <iostream>
#include <cassert>

/* ****************************************************************************************************** * 
 * Binning Structure Interface                                    
 *
 * ****************************************************************************************************** */ 

template <typename attributeType> class BinningStructure {
  public:
    virtual std::pair< int , bool>  getIndex( attributeType val) = 0;
    virtual int getSize() = 0;
};

/* ****************************************************************************************************** * 
 * Inherited binning structure for binning by energy group
 *
 * ****************************************************************************************************** */ 

class GroupBinningStructure : public BinningStructure<int> {
  private:
    int size;
  public:
    GroupBinningStructure(int numGroups): size(numGroups) {};
   ~GroupBinningStructure();
    
    int getSize();
    virtual std::pair< int , bool > getIndex( int group );
};
 

/* ****************************************************************************************************** * 
 * Inherited binning structure for binning by collision order
 *
 * ****************************************************************************************************** */ 

class CollisionOrderBinningStructure : public BinningStructure<int> {
  private:
    int minOrder , maxOrder;
    int size;
  public:
    CollisionOrderBinningStructure(int min , int max): minOrder(min)   , maxOrder(max)   , size(maxOrder - minOrder) {};
    CollisionOrderBinningStructure(int order ):        minOrder(0)     , maxOrder(order) , size(1)                   {};
   ~CollisionOrderBinningStructure() {};
    
    int getSize();
    virtual std::pair< int , bool > getIndex( int collisionOrder );
};

/* ****************************************************************************************************** * 
 * Inherited binning structure for binning by an arbitrary histogram
 *
 * ****************************************************************************************************** */ 

class HistogramBinningStructure : public BinningStructure<double> {
  private:
    double binWidth;
    int    numBins;
  public:
    HistogramBinningStructure(double min , double max , int bins): binWidth( (max - min) / ((double) bins) ) , numBins(bins) {};
   ~HistogramBinningStructure() {};
    
    int getSize();
    virtual std::pair< int , bool> getIndex(double value);
};


#endif
