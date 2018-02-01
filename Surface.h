#ifndef _SURFACE_HEADER_
#define _SURFACE_HEADER_

#include <string>

#include "Point.h"
#include "Utility.h"

class surface {
private:
    std::string surface_name;
    
public:
    surface( std::string label ) : surface_name(label) {};
    ~surface() {};
    
    virtual std::string name() { return surface_name; };
    
    virtual double eval( point p )   = 0;
    virtual double distance( point p, point u ) = 0;
};

class plane : public surface {
private:
    double a, b, c, d;
public:
    plane( std::string label, double p1, double p2, double p3, double p4 ) : surface(label), a(p1), b(p2), c(p3), d(p4) {};
    ~plane() {};
    
    double eval( point p );
    double distance( point p, point u );
};

class sphere : public surface {
private:
    double x0, y0, z0, rad;
public:
    sphere( std::string label, double p1, double p2, double p3, double p4 ) : surface(label), x0(p1), y0(p2), z0(p3), rad(p4) {};
    ~sphere() {};
    
    double eval( point p );
    double distance( point p, point u );
};


#endif
