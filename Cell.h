/*
 Author: Blake
 Date: 11/8/17
 Req. Files: Cell.cpp, Material.h, Surface.h, Random.h
 */

#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include <memory>
#include <stack>
#include <limits>
#include <utility>
#include <tuple>
#include <vector>

#include "Material.h"
#include "Surface.h"
#include "Random.h"
#include "Particle.h"


using std::vector;
using std::stack;
using std::pair;
using std::tie;
using std::cout;
using std::endl;

typedef std::shared_ptr<Particle> Part_ptr; //found in Particle.h -> Material.h
typedef std::shared_ptr<Material> Mat_ptr;
typedef std::shared_ptr<surface> Surf_ptr;

class Cell
//Region in space, bounded by surfaces/
//NOTE: create all other objects before constructing a cell, or it leads to a pain in the butt
{
private:
    Mat_ptr mat; //material properties within cell
    //vector<Surf_ptr> surfaces; //surfaces that enclose cell
    //vector<bool> inside; //1 = inside cooresponding surface, 0 = outside
    vector<pair<Surf_ptr, bool>> surfaces;
    
public:
    //Constructor:
    Cell(Mat_ptr mati, vector< pair< Surf_ptr, bool > > surfacesi);
    //Functions:
    //vector<Surf_ptr> getSurfaces();
    //vector<bool> getInside();
    Mat_ptr getMat();
    
    //operations
    double distToSurface(Part_ptr pi);
    double distToCollision(Part_ptr pi);
    
    pair<Surf_ptr, double> closestSurface(Part_ptr p);
    void processRxn(Part_ptr p, stack<Part_ptr> &pstack);
    
    bool amIHere(point pos);
};
#endif 
