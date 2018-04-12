#include "Utility.h"
#include <vector>

using std::vector;

/* ****************************************************************************************************** * 
 * Fast Matrix Operations
 *   Functions for calculating determinants of double-typed matrices
 * ****************************************************************************************************** */ 

double Utility::fourDeterminant(const vector< double >& v1, const vector< double >& v2, const vector< double >& v3, const vector< double >& v4) {
    
    double det1 = v2[1] * (v3[2] * v4[3] - v3[3] * v4[2]) + v2[2] * (v3[3] * v4[1] - v3[1] * v4[3]) + v2[3] * (v3[1] * v4[2] - v3[2] * v4[1]);
    double det2 = v2[0] * (v3[2] * v4[3] - v3[3] * v4[2]) + v2[2] * (v3[3] * v4[0] - v3[0] * v4[3]) + v2[3] * (v3[0] * v4[2] - v3[2] * v4[0]);
    double det3 = v2[0] * (v3[1] * v4[3] - v3[3] * v4[1]) + v2[1] * (v3[3] * v4[0] - v3[0] * v4[3]) + v2[3] * (v3[0] * v4[1] - v3[1] * v4[0]);
    double det4 = v2[0] * (v3[1] * v4[2] - v3[2] * v4[1]) + v2[1] * (v3[2] * v4[0] - v3[0] * v4[2]) + v2[2] * (v3[0] * v4[1] - v3[1] * v4[0]);
    double det_final = v1[0] * det1 - v1[1] * det2 + v1[2] * det3 - v1[3] * det4;
    
    return det_final;
}

double Utility::threeDeterminant(const vector< double >& v1, const vector< double >& v2, const vector< double >& v3)
{
    double det = v1[0] * (v2[1] * v3[2] - v2[2] * v3[1]) - v1[1] * (v2[0] * v3[2] - v2[2] * v3[0]) + v1[2] * (v2[0] * v3[1] - v2[1] * v3[0]);
    return det;
}

std::vector< double > Utility::pointFourVec( point pos )
{
    // Takes a point and returns a vector (length 4) with a "1.0" appended
    std::vector< double > fourVec;
    
    fourVec.push_back( pos.x );
    fourVec.push_back( pos.y );
    fourVec.push_back( pos.z );
    fourVec.push_back( 1.0 );
    
    return fourVec;
}

/* ****************************************************************************************************** * 
 * Miscellaneous                      
 *
 * ****************************************************************************************************** */ 

double Utility::dist(point p1 , point p2) {
  return std::sqrt(
                   std::pow(p1.x - p2.x , 2) + 
                   std::pow(p1.y - p2.y , 2) + 
                   std::pow(p1.z - p2.z , 2)
                  );
}

bool Utility::sameSign( double a, double b )
{
    bool signTest;
    if ( a*b < 0.0 )
    {
        signTest = false;
    }
    else
    {
        signTest = true;
    }
    
    return signTest;
}

// return smallest positive real root if it exists; if it does not, return very big number
double Utility::quadSolve( double a, double b, double c ) {
    double d = b*b - 4.0 * a * c;
    
    if ( d < 0.0 ) {
        // roots are complex, return huge number
        return std::numeric_limits<double>::max();
    }
    else if ( d == 0 ) {
        // identical roots
        double r = -0.5 * b / a;
        r = r >= 0.0 ? r : std::numeric_limits<double>::max();
        return r;
    }
    else {
        double sqrtd = std::sqrt(d);
        double ai    = 0.5 / a;
        
        double r1 = ai * ( -1.0 * b - sqrtd );
        double r2 = ai * ( -1.0 * b + sqrtd );
        
        r1 = r1 >= 0.0 ? r1 : std::numeric_limits<double>::max();
        r2 = r2 >= 0.0 ? r2 : std::numeric_limits<double>::max();
        
        return std::fmin( r1, r2 );
    }
    
}

int Utility::linearizeIndices( std::vector<int> indices , std::vector<int> binSizes) {
  if(indices.size() != binSizes.size() ) {
    std::cerr << "Error in Utility::linearizeIndices! indices and binSizes must be the same size" << std::endl;
    throw;
  }
  int n = 0;
  if(binSizes.size() == 1) {
    return(indices.at(0));
  }
  else {
    for(int i = 1; i < indices.size(); ++i) {
      int add = indices.at(i);
      for(int j = i-1; j < 0; --j) {
        add *= binSizes.at(j);
      }
      n += add;
    }
  }

  return(n);
}

/* ****************************************************************************************************** * 
 * Generic Vector and Point Operations
 *
 * ****************************************************************************************************** */ 

// L2 norm of two points
double pointL2( point a , point b ) {
  return( (a - b)*(a - b) );
}

