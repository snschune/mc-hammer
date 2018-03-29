/*
  Author: ESGonzalez
  Date: 2/20/18
*/

#include "Reaction.h"

double Capture::getXS( Part_ptr p )
{
  int g = p->getGroup();
  return captureXS[g-1];
}

void Capture::sample( Part_ptr p, std::stack< Part_ptr > &bank )
{
  p->kill();
}

Scatter::Scatter( int ng, std::vector< std::vector< double > > scatterXSi ) : Reaction( ng ), scatterXS( scatterXSi )
{
  rxnName = "Scatter";

  // Fill the total scatter vector
  for (int j=0; j < nGroups; ++j) 
  { // loop over rows
    double scatterTotInc = 0; // increment the scatter xs total
    for (int k=0; k < nGroups; ++k) 
    { // loop over columns
      scatterTotInc += scatterXS[j][k];                         
    }  
    scatterTotalXS.push_back(scatterTotInc);
  }

}

double Scatter::getXS( Part_ptr p )
{
  int g = p->getGroup();
  return scatterTotalXS[g-1];
}

void Scatter::sample( Part_ptr p, std::stack< Part_ptr > &bank )
{
  //select energy group to shift
  double rand = Urand();
  double cutoff = 0;
  int gf = 0;
  int g = p->getGroup();
  std::vector<double> curSigs = scatterXS[g-1];
  for(int i = 0; i < nGroups; i++)
  {
    cutoff += curSigs[i]/scatterTotalXS[g-1]; 
    if(rand < cutoff)
      {
        gf = i+1;
        break;  
      }
  }
  p->scatter( gf );
}

double Fission::getXS( Part_ptr p )
{
  int g = p->getGroup();
  return fissionXS[g-1];
}

void  Fission::sample( Part_ptr p, std::stack< Part_ptr > &bank ) {

  p->kill();

  /*
  // create random number of secondaries from multiplicity distributon and
  // push all but one of them into the bank, and set working particle to the last one
  // if no secondaries, kill the particle
  int     g = p->getGroup();
  int     n = floor( nu[g-1] + Urand() );
  double x0 = p->getPos().x;
  double y0 = p->getPos().y;
  double z0 = p->getPos().z;

  Source_ptr source = std::make_shared< setSourcePoint > ( "induced_fission", x0, y0, z0, chi );

  if ( n <= 0 ) 
  {
    p->kill();
  }
  else 
  {
    // bank all but last particle (skips if n = 1)
    for ( int i = 0 ; i < ( n - 1 ) ; i++ ) 
    {
      Part_ptr q = source->sample();
      q->setCell( p->getCell() );
      bank.push( q );
    }
    // set working particle to last one
    Part_ptr q = source->sample();
    q->setCell( p->getCell() );
    *p = *q; // figure out how to do this
  }
  */
  
}
