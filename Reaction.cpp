#include "Reaction.h"

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

void  Fission::sample( Part_ptr p, std::stack< Part_ptr > &bank ) {

  p->kill(); // need to rewrite this 
  
}