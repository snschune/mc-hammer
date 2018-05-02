#include "Reaction.h"

Capture::Capture( XSec_ptr capti ) : Reaction( capti ) {
  // make sure the correction XS is attached
  std::shared_ptr< CaptureXS > capt = std::dynamic_pointer_cast< CaptureXS > ( capti );
  rxnName = "Capture";
  assert( rxnName == capt->name() );

  // call the XS vectors
  captureXS = capt->getCaptureXS();
}

void Capture::sample( Part_ptr p, std::stack< Part_ptr > &bank ) {
  p->kill();
}

Scatter::Scatter( XSec_ptr scati ) : Reaction( scati ) {
  // make sure the correction XS is attached
  std::shared_ptr< ScatterXS > scat = std::dynamic_pointer_cast< ScatterXS > ( scati );
  rxnName = "Scatter";
  assert( rxnName == scat->name() );

  // call the XS vectors
  scatterXS      = scat->getScatterXS();
  scatterTotalXS = scat->getScatterTotalXS();

  // set the number of groups
  nGroups = scatterXS.size();
}

void Scatter::sample( Part_ptr p, std::stack< Part_ptr > &bank ) {
  // select energy group to shift
  double rand = Urand();
  double cutoff = 0;
  int gf = 0;
  int g = p->getGroup();
  std::vector<double> curSigs = scatterXS[g-1];
  for(int i = 0; i < nGroups; i++)
  {
    cutoff += curSigs[i]/scatterTotalXS[g-1]; 
    if( rand < cutoff )
      {
        gf = i+1;
        break;  
      }
  }
  p->scatter( gf );
}

Fission::Fission( XSec_ptr fissi ) : Reaction( fissi ) {
  // make sure the correction XS is attached
  std::shared_ptr< FissionXS > fiss = std::dynamic_pointer_cast< FissionXS > ( fissi );
  rxnName = "Fission";
  assert( rxnName == fiss->name() );

  // call the XS vectors
  fissionXS = fiss->getFissionXS();
  nu        = fiss->getNu();
  chi       = fiss->getChi();
}

void  Fission::sample( Part_ptr p, std::stack< Part_ptr > &bank ) {

  p->kill(); // need to rewrite this 
  
}