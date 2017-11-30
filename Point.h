#ifndef _POINT_HEADER_
#define _POINT_HEADER_

#include <memory>




class point {
  public:
    double x, y, z;

     point( double a, double b, double c ) : x(a), y(b), z(c) {};
    ~point() {};
};

typedef std::shared_ptr<point> p_ptr;

class ray {
  public:
    ray( p_ptr p, p_ptr d );
    //ray( point p, point d ) : pos(p), dir(d) {};
    ~ray() {};

    p_ptr pos;
    p_ptr dir;
};

#endif
