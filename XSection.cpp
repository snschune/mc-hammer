#include "XSection.h"

ScatterXS::ScatterXS( std::vector< std::vector< double > > scatterXSi ) : scatterXS( scatterXSi )
{
  xsName = "Scatter";
  int nGroups = scatterXS.size();

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