/*
 Author: ESGonzalez
 Date: 1/26/18
 */

#include "Utility.h"
#include <vector>

using std::vector;

double fourDeterminant(vector< double > v1, vector< double > v2, vector< double > v3, vector< double > v4) {
    
    if(v1.size() != 4 or v2.size() != 4 or v3.size() != 4 or v4.size() != 4) {
        std::cerr << " Vectors in fourDeterminant must be of length 4!" << std::endl;
        return(0);
    }
    
    double det1 = v2[1] * (v3[2] * v4[3] - v3[3] * v4[2]) + v2[2] * (v3[3] * v4[1] - v3[1] * v4[3]) + v2[3] * (v3[1] * v4[2] - v3[2] * v4[1]);
    double det2 = v2[0] * (v3[2] * v4[3] - v3[3] * v4[2]) + v2[2] * (v3[3] * v4[0] - v3[0] * v4[3]) + v2[3] * (v3[0] * v4[2] - v3[2] * v4[0]);
    double det3 = v2[0] * (v3[1] * v4[3] - v3[3] * v4[1]) + v2[1] * (v3[3] * v4[0] - v3[0] * v4[3]) + v2[3] * (v3[0] * v4[1] - v3[1] * v4[0]);
    double det4 = v2[0] * (v3[1] * v4[2] - v3[2] * v4[1]) + v2[1] * (v3[2] * v4[0] - v3[0] * v4[2]) + v2[2] * (v3[0] * v4[1] - v3[1] * v4[0]);
    double det_final = v1[0] * det1 - v1[1] * det2 + v1[2] * det3 - v1[3] * det4;
    
    return det_final;
}


double dist(point p1 , point p2) {
  return std::sqrt(
                   std::pow(p1.x - p2.x , 2) + 
                   std::pow(p1.y - p2.y , 2) + 
                   std::pow(p1.z - p2.z , 2)
                  );
}

bool sameSign( double a, double b )
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
double quadSolve( double a, double b, double c ) {
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
