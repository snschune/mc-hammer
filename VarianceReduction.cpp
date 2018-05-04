#include "VarianceReduction.h"

#include <cmath>

#include "Random.h"
#include "Cell.h"
#include "Material.h"

typedef std::shared_ptr< Material > Mat_ptr;

void VarianceReduction::split( Particle& p, std::stack<Particle>& pstack, double s )
{
  if ( s > 0.0 ) {
    unsigned int n = floor( s + Urand() );
    split( p, pstack, n ); 
  }
}


void VarianceReduction::split( Particle& p, std::stack<Particle>& pstack, unsigned int n )
{
  if ( n > 1 ) {
    p.adjustWgt( 1.0/n );
    for ( auto i = 0 ; i < n-1 ; i++ ) {
      pstack.push(p);
    }
  }
}

void VarianceReduction::roulette( Particle& p, std::stack<Particle>& pstack, double s ) {
  if ( s >= 0 && s < 1 ) {
    if ( Urand() < s ) {
      p.adjustWgt( 1.0 / s );
    }
    else {
      p.kill();
    }
  }
}

void VarianceReduction::importanceSplit( Particle& p, std::stack<Particle>& pstack, double I1, double I2 )
{
  if ( I2 == 0.0 ) {
    p.kill();
  }
  else {
    if ( I2 > I1 ) {
      split( p, pstack, I2/I1 );
    }
    else if ( I2 < I1 ) {
      roulette( p, pstack, I2/I1 );
    }
  }
}

void VarianceReduction::collisionSplit( Particle& p, std::stack<Particle>& pstack, unsigned int n )
{
  if ( n > 1 ) {
    p.adjustWgt( 1.0/n );
  
    Mat_ptr  M = p.getCell()->getMat();
    for ( auto i = 0 ; i < n-1 ; i++ ) {
      Particle q = p;
      M->sampleCollision( q, pstack );
      pstack.push(q);   
    }
  }
}
