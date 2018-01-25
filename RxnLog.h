/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class keeps a reaction log for the current particle being transported
 */


#ifndef _RXNLOG_HEADER_
#define _RXNLOG_HEADER_

#include "Point.h"
#include "Particle.h"

#include <vector>

using std::vector;

typedef std::shared_ptr<Particle> particle_ptr;

class rxnLog {
  private:
    int particleID;

    vector<int>    reactionType;
    vector<int>    material;
    vector<point>  locs;
  public:
     rxnLog(int pID) : particleID(pID) {};
    ~rxnLog()   {};
     
    void update(particle_ptr p, int rxn , int mat);
    
};

#endif
