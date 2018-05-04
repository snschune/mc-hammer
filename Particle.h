/*
 Author: Blake
 Date: 11/8/17
 Req. Files: point.h
 */

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include "Random.h"
#include <memory>
#include <iostream>
#include <cmath>

class Cell;
class surface;

typedef std::shared_ptr<Cell>    Cell_ptr;
typedef std::shared_ptr<surface> Surf_ptr;

class Particle
{
private:
    bool alive;
    point pos;
    point dir;
    Cell_ptr cell; // the cell the particle is currently in
    Surf_ptr surf; // the surface the particle most recently crossed
    int group;
    int collisionCounter;
    const double  weight = 1; // temporary until var reduction is implemented

public:
    //constructor
    Particle(point posi, point diri, int gi);
    Particle( const Particle &p );
   ~Particle() {}; 
    
    //functions
    // gets
    bool isAlive()           const { return(alive);            };
    Cell_ptr getCell()       const { return(cell);             };
    Surf_ptr getSurf()       const { return(surf);             };
    point getPos()           const { return(pos);              };
    point getDir()           const { return(dir);              };   
    int   getGroup()         const { return(group);            };
    int   getNumCollisions() const { return(collisionCounter); };
    double getWeight()       const { return(weight);           };

    // sets
    void countCollision() {collisionCounter++; };
    void setCell(Cell_ptr celli);
    void setSurf(Surf_ptr surfi);
    void setGroup(int g);
    void setPos(point posi);
    void setDir(point diri);
    void setPos(double xi, double yi, double zi);
    void setDir(double ui, double vi, double wi);
    void move(double dist);
    void kill();
    void scatter( int gf );
    void rotate( double mu0, double rand );
    
    // prints
    void printState();
};


#endif

