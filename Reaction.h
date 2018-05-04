/*
  Author: ESGonzalez
  Date: 2/20/18
*/

#ifndef __REACTION_H__
#define __REACTION_H__

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <utility>

#include "Particle.h"
#include "Source.h"

typedef std::shared_ptr< Particle > Part_ptr;
typedef std::shared_ptr< Source >   Source_ptr;

class Reaction 
// Need to add safety features
{    
  protected:
    std::string rxnName;
    int         nGroups;

  public:
    Reaction( int ng ) : nGroups( ng ) {};
   ~Reaction() {};

    virtual std::string name() final { return rxnName; };
    virtual double      getXS  ( Particle& p ) = 0;
    virtual void        sample ( Particle& p, std::stack< Particle > & bank ) = 0;
};

class Capture : public Reaction 
{
  private:
    std::vector< double > captureXS; // size g

  public:
    Capture( int ng, std::vector< double > captureXSi ) : Reaction( ng ), captureXS( captureXSi ) { rxnName = "Capture"; };
   ~Capture() {};

    double getXS( Particle& p );

    void   sample( Particle& p, std::stack< Particle > &bank );
};

class Scatter : public Reaction 
{
  private:
    std::vector< std::vector< double > > scatterXS; // size g^2
    std::vector< double >                scatterTotalXS; // size g-> the total for each group (s11+s12+s13...+s1g)

  public:
    Scatter( int ng, std::vector< std::vector< double > > scatterXSi );
   ~Scatter() {};

    double getXS( Particle& p );

    void   sample( Particle& p, std::stack< Particle > &bank );
};

class Fission : public Reaction 
{
  private:
    std::vector< double > fissionXS; // size g
    std::vector< double > nu; // size g
    std::vector< double > chi; // size g

  public:
    Fission( int ng, std::vector< double > fissionXSi, std::vector< double > nui, std::vector< double > chii ) 
    : Reaction( ng ), fissionXS( fissionXSi ), nu( nui ), chi( chii ) { rxnName = "Fission"; };
   ~Fission() {};

    double getXS ( Particle& p );

    void   sample( Particle& p, std::stack< Particle > &bank );
};

#endif
