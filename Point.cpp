#include <cmath>

#include "Point.h"
//Overloaded operator for =
point point::operator=(const point &rhs)
{
  point p2(rhs.x,rhs.y,rhs.z);
  return p2;
}

ray::ray( point p, point d ) : pos(p), dir(d) {
    
    // normalize direciton vector
    double norm = 1.0 / std::sqrt( dir.x * dir.x  +  dir.y * dir.y  +  dir.z * dir.z );
    dir.x *= norm; dir.y *= norm; dir.z *= norm;
    
}


