/*
 Author: Blake
 Date: 11/21/17
 Req. Files: Cell.cpp, Material.h, Surface.h, Random.h
 */

#ifndef __TRANSPORT_H__
#define __TRANSPORT_H__

#include <iostream>
#include <memory>
#include <stack>
#include <limits>
#include <string>


#include "Cell.h"
#include "Material.h"
#include "Surface.h"
#include "Random.h"
#include "Particle.h"
#include "Constants.h"
#include "Geometry.h"
#include "Source.h"
#include "Mesh.h"
#include "Tet.h"
#include "HammerTime.h"

using std::vector;
using std::stack;
using std::cout;
using std::endl;


typedef std::shared_ptr<Cell>      Cell_ptr;
typedef std::shared_ptr<Particle>  Part_ptr;
typedef std::shared_ptr<Material>  Mat_ptr;
typedef std::shared_ptr<surface>   Surf_ptr;
typedef std::shared_ptr<Mesh>      Mesh_ptr;

class Transport {
private:
    int numHis;
    //vector<Mat_ptr> mats;
    //vector<Cell_ptr> cells;    //vector of cells (to be moved into Geometry)
    //vector<Surf_ptr> surfaces; //vector of surfaces '
    stack<Part_ptr> pstack;
    vector<double> tallies;
    Constants constants;
    Geometry geometry; 
    Mesh_ptr mesh;
    
public:
    //constructor
    Transport( Geometry geoin , Constants consti , int numhis , Mesh_ptr meshin);
   ~Transport() {}; 
        //to be altered once input is added
    
    //functions
    //void setup();
    void runTransport();
    void output();
};

#endif

