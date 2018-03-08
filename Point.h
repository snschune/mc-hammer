#ifndef _POINT_HEADER_
#define _POINT_HEADER_

class point {
public:
    double x, y, z;
    
    point( double a, double b, double c ) : x(a), y(b), z(c) {};
    point( const point &p): x(p.x) , y(p.y) , z(p.z) {};
   ~point() {};
};

class ray {
public:
    ray( point p, point d );
   ~ray() {};
    
    point pos;
    point dir;
};

#endif
