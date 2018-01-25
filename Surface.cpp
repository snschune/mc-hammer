#include <cmath>
#include <limits>

#include "Point.h"
#include "QuadSolver.h"
#include "Surface.h"

double plane::eval( point p ) {
    return a * p.x  +  b * p.y  +  c * p.z  - d;
}

double plane::distance( point p, point u ) {
    
    double dist = ( d - a * p.x - b * p.y - c * p.z ) / ( a * u.x + b * u.y + c * u.z );
    if ( dist > 0.0 ) { return dist; }
    else { return std::numeric_limits<double>::max(); }
    
}

double sphere::eval( point p ) {
    return std::pow( p.x - x0, 2 ) + std::pow( p.y - y0, 2 ) + std::pow( p.z - z0, 2 )  - rad*rad;
}

double sphere::distance( point p, point u ) {
    // difference between each coordinate and current point
    point q( p.x - x0, p.y - y0, p.z - z0 );
    
    double b = 2.0 * ( q.x * u.x  +  q.y * u.y  +  q.z * u.z);
    double c = eval( p );
    
    return quad_solve( 1.0, b, c );
    
}
