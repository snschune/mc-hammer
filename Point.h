#ifndef _POINT_HEADER_
#define _POINT_HEADER_

#include <memory>




class point {
  public:
    double x, y, z;

     point( double a, double b, double c ) : x(a), y(b), z(c) {};
    ~point() {};
};


/*class ray {
  public:
    ray( point p, point d );
    //ray( point p, point d ) : pos(p), dir(d) {};
    ~ray() {};

    point pos;
    point dir;
};
*/

#endif
