/*
 Author: Blake
 Date: 11/8/17
 Req. Files: point.h
 */

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include <memory>
#include <iostream>
#include <cmath>

class Cell;

typedef std::shared_ptr<Cell> Cell_ptr;

class Particle
{
private:
    bool alive;
    point pos;
    point dir;
    Cell_ptr cell; //still need to change this
    int group;
public:
    //constructor
    Particle(point posi, point diri, Cell_ptr celli, int gi);
    //functions
    bool isAlive();
    Cell_ptr getCell();
    point getPos();
    point getDir();
    //r_ptr getray();
    int   getGroup();

    void setCell(int c);
    void setGroup(int g);
    void setPos(point posi);
    void setDir(point diri);
    void setPos(double xi, double yi, double zi);
    void setDir(double ui, double vi, double wi);
    void move(double dist);
    void kill();
    
    void printState();
};


#endif

