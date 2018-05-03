#ifndef __REACTION_H__
#define __REACTION_H__

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <utility>
#include <cassert>

#include "Particle.h"
#include "XSection.h"

typedef std::shared_ptr< Particle  > Part_ptr;
typedef std::shared_ptr< XSection >  XSec_ptr;

class Reaction
{    
  protected:
    std::string rxnName;
    XSec_ptr    xsec;

  public:
    Reaction( XSec_ptr xseci ) : xsec( xseci ) {};
   ~Reaction() {};

    virtual std::string name() final { return rxnName; };
    virtual void        sample ( Part_ptr p, std::stack< Part_ptr > & bank ) = 0;
};

class Capture : public Reaction 
{
  private:
    std::vector< double > captureXS;

  public:
    Capture( XSec_ptr capti );
   ~Capture() {};

    void sample( Part_ptr p, std::stack< Part_ptr > &bank );
};

class Scatter : public Reaction 
{
  private:
    std::vector< std::vector< double > > scatterXS;
    std::vector< double >                scatterTotalXS;
    int                                  nGroups;

  public:
    Scatter( XSec_ptr scati );
   ~Scatter() {};

    void sample( Part_ptr p, std::stack< Part_ptr > &bank );
};

class Fission : public Reaction 
{
  private:
    std::vector< double > fissionXS;
    std::vector< double > nu;
    std::vector< double > chi;

  public:
    Fission( XSec_ptr fissi );
   ~Fission() {};

    void sample( Part_ptr p, std::stack< Part_ptr > &bank );
};

#endif