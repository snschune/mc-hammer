#ifndef __REACTION_H__
#define __REACTION_H__

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include <utility>

#include "Particle.h"

typedef std::shared_ptr< Particle > Part_ptr;

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
    virtual double      getXS  ( int group ) = 0;
    virtual void        sample ( Part_ptr p, std::stack< Part_ptr > & bank ) = 0;
};

class Capture : public Reaction 
{
  private:
    std::vector< double > captureXS; // size g

  public:
    Capture( int ng, std::vector< double > captureXSi ) : Reaction( ng ), captureXS( captureXSi ) { rxnName = "Capture"; };
   ~Capture() {};

    double getXS( int group ) { return captureXS[group-1]; };

    void   sample( Part_ptr p, std::stack< Part_ptr > &bank );
};

class Scatter : public Reaction 
{
  private:
    std::vector< std::vector< double > > scatterXS; // size g^2
    std::vector< double >                scatterTotalXS; // size g-> the total for each group (s11+s12+s13...+s1g)

  public:
    Scatter( int ng, std::vector< std::vector< double > > scatterXSi );
   ~Scatter() {};

    double getXS( int group ) { return scatterTotalXS[group-1]; };

    void   sample( Part_ptr p, std::stack< Part_ptr > &bank );
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

    double getXS ( int group ) { return fissionXS[group-1]; };

    void   sample( Part_ptr p, std::stack< Part_ptr > &bank );
};

#endif