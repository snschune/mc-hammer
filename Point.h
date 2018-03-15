#ifndef _POINT_HEADER_
#define _POINT_HEADER_

class point {
public:
    double x, y, z;
    
    point( double a, double b, double c ) : x(a), y(b), z(c) {};
    point( const point &p): x(p.x) , y(p.y) , z(p.z) {};
   ~point() {};
    
    point operator + (point const &pt); // add two points elementwise
    point operator - (point const &pt); // subtract two points elementwise
    double operator * (point const &pt); // dot product of points
    
    point operator / (double scalar);   // divide point elementwise by scalar
    point operator * (double scalar);   // multiply point elementwise by scalar
};


class ray {
public:
    ray( point p, point d );
   ~ray() {};
    
    point pos;
    point dir;

};



#endif
