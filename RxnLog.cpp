/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class keeps a reaction log for the current particle being transported
 */

#include "RxnLog.h"

void rxnLog::update(particle_ptr p , int rxn , int mat){
    reactionType.push_back(rxn);
    material.push_back(mat);
    locs.push_back(p->getPos());
};

