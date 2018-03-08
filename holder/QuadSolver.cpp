#include <cmath>
#include <limits>

#include "QuadSolver.h"

// return smallest positive real root if it exists; if it does not, return very big number
double quad_solve( double a, double b, double c ) {
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
