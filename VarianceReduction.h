#ifndef _VARIANCE_REDUCTION_HEADER_
#define _VARIANCE_REDUCTION_HEADER_

#include <stack>

#include "Particle.h"

class VarianceReduction {
  private:

  public:
    void split( Particle& p, std::stack<Particle>& pstack, double s );
    void split( Particle& p, std::stack<Particle>& pstack, unsigned int n );
    void roulette( Particle& p, std::stack<Particle>& pstack, double s );
    void importanceSplit( Particle& p, std::stack<Particle>& pstack, double I1, double I2 );
};


#endif
