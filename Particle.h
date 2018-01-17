/*
 Author: Blake
 Date: 11/8/17
 Req. Files: point.h
 */ 

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"

class Particle
{
private:
    ray r;
    bool alive;
    int region;
    int group;
public:
    //constructor
    Particle(ray ri, int regioni, int gi);
    //functions
    point getPos();
    point getDir();
    ray   getray();
    int   getGroup();
    
    void setGroup(int g);
    void setPos(point posi);
    void setDir(point diri);
    void setPos(double xi, double yi, double zi);
    void setDir(double ui, double vi, double wi);
    void move(double dist);
    void kill();
    
};


#endif
