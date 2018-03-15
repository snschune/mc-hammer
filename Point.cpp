#include <cmath>

#include "Point.h"


point point::operator + (point const &pt) {
  point p(pt.x + x , pt.y + y, pt.z + z);
  return(p);
}

point point::operator - (point const &pt) {
  point p(x - pt.x  , y - pt.y, z - pt.z);
  return(p);
}

double point::operator * (point const &pt) {
  return( x * pt.x + y * pt.y + z * pt.z );
}

point point::operator / (double scalar) {
  point p(x / scalar  , y / scalar , z / scalar);
  return(p);
}

point point::operator * (double scalar) {
  point p(x * scalar  , y * scalar , z * scalar);
  return(p);
}

ray::ray( point p, point d ) : pos(p), dir(d) {
    
    // normalize direciton vector
    double norm = 1.0 / std::sqrt( dir.x * dir.x  +  dir.y * dir.y  +  dir.z * dir.z );
    dir.x *= norm; dir.y *= norm; dir.z *= norm;
    
}


