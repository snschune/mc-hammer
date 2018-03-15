/*
 Author: ESGonzalez, Kyle Beyer, Evan Leppink, Blake Rucinski
 Date: 1/26/18
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <limits>

#include "Point.h"

using std::vector;

namespace Utility {

/* ****************************************************************************************************** * 
 * This namespace collects all of the functions and abstract classes that are widely used in MC-Hammer
 *  There is 1 class:
 *    - Binning Structure
 *  and 3 function groups:
 *    - Matrix Operations
 *    - Generic Vector Operations
 *    - Miscellaneous
 *
 * ****************************************************************************************************** */ 

/* ****************************************************************************************************** * 
 * Binning Structure
 *  A class template dealing with binning over an attribute of varying data types
 *    - Constructed with a min, max, and integer size
 *    - getIndex is constant lookup time, 
 *        - returns < n , true >, where n is the index where 'value' falls in the binning structure 
 *          if 'value' is in [min , max]
 *        - returns < 0 , false > otherwise
 *    - attributeType should typically be either an int, float or double; must be castable both to/from int
 *    - attributeType must have comparator operators >= and <= overloaded
 *
 * ****************************************************************************************************** */ 

  template <typename attributeType> class BinningStructure {
    private:
      int size;
      attributeType min , max , binWidth;
    public:
      BinningStructure(attributeType minin , attributeType maxin , int sizein): min(minin) , max(maxin) , size(sizein) , binWidth( (max - min) / (static_cast<attributeType>( size )) )  {};
     ~BinningStructure() {};

      int getSize() { return(size); };
      
      std::pair<int , bool> getIndex(attributeType value)
      {
        std::pair <int , bool> out;
        if (value <= max and value >= min) {
          out.first  = static_cast<int>(value / binWidth);
          out.second = true;
        }
        else{
          out.first  = 0;
          out.second = false; 
        }
        return(out);
      };

  };

/* ****************************************************************************************************** * 
 * Fast Matrix Operations
 *   Functions for calculating determinants of double-typed matrices
 * ****************************************************************************************************** */ 
  
  // determinant of 4x4 matrix [ row1 ; row2 ; row3 ; row4 ]
  double fourDeterminant(const std::vector< double >& row1, const std::vector< double >& row2,
                       const std::vector< double >& row3, const std::vector< double >& row4 );
                       
  // determinant of 3x3 matrix [ row1 ; row2 ; row3 ]
  double threeDeterminant(const vector< double >& v1, const vector< double >& v2, const vector< double >& v3);
  
  // given point [p1 , p2 , p3 ] , returns a vector<double> [ p1 , p2 , p3 , 1.0 ] 
  std::vector< double > pointFourVec( point pos );

/* ****************************************************************************************************** * 
 * Generic Vector and Point Operations
 *
 * ****************************************************************************************************** */ 

  template<class T>  T vecSum(std::vector<T> vec) {
      T sum = 0;
      for(auto v : vec) {
          sum += v;
      }
      return(sum);
  }

  template<class T>  T vecMean(std::vector<T> vec) {
      T sum = 0;
      int i = 0;
      for(auto v : vec) {
          sum += v;
          ++i;
      }
      return(sum/i);
  }

  template<class T> T vecMax(std::vector<T> vec) {
      T temp = vec[0];
      for ( auto v : vec ) {
          if ( v > temp ) {
              temp = v;
          }
      }
      return temp;
  }

  template<class T> T vecMin(std::vector<T> vec) {
      T temp = vec[0];
      for ( auto v : vec ) {
          if ( v < temp ) {
              temp = v;
          }
      }
      return temp;
  }
  
  // dot product of two vectors
  template<class T> T vecDot(std::vector<T> vec1, std::vector<T> vec2) {
    if ( vec1.size() == vec2.size() ) {
      T sum = 0;
      for (int i = 0; i < vec1.size(); ++i) {
        sum += vec1.at(i) * vec2.at(i);
      }
      return(sum);
    }
    else {
      std::cerr << " vecDot needs vectors of the same length " << std::endl;
      throw;
    }
  }
  
  // L2 norm of two vectors
  template<class T> T vecL2(std::vector<T> vec1, std::vector<T> vec2 ) {
    if ( vec1.size() == vec2.size() ) {
      T sum = 0;
      for (int i = 0; i < vec1.size(); ++i) {
        sum += pow( vec1.at(i)  -  vec2.at(i)  , 2);
      }
      return(std::sqrt(sum));
    }
    else {
      std::cerr << " vecL2 needs vectors of the same length " << std::endl;
      throw;
    }
  }
  
  // L2 norm of two points
  double pointL2( point a , point b ) {
    return( (a - b)*(a - b) );
  }


/* ****************************************************************************************************** * 
 * Miscellaneous                      
 *
 * ****************************************************************************************************** */ 
  
  bool   sameSign( double a, double b );
  double dist(point p1 ,point p2); 

  // return largest positive root of quadratic equation with coefficients a, b, c
  // if both roots negative or complex, return a really big number
  double quadSolve( double a, double b, double c );

};
#endif
