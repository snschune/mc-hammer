#ifndef __XSection_H__
#define __XSection_H__

#include <vector>
#include <string>
#include <utility>

class Reaction;

typedef std::shared_ptr< Reaction > React_ptr;

class XSection 
{    
  protected:
    std::string  xsName;
    React_ptr rxn;

  public:
    XSection() {};
   ~XSection() {};

    // getters
    virtual std::string name()   final { return xsName; };
    virtual React_ptr   getRxn() final { return rxn; };
    virtual double      getXS( int group ) = 0;

    // setters
    virtual void        setRxn( React_ptr rxni ) final { rxn = rxni; return; };
};

class CaptureXS : public XSection 
{
  private:
    std::vector< double > captureXS; // size g

  public:
    CaptureXS( std::vector< double > captureXSi ) : captureXS( captureXSi ) { xsName = "Capture"; };
   ~CaptureXS() {};

    double getXS( int group ) { return captureXS[group-1]; };

    // get XS vectors
    std::vector< double > getCaptureXS() { return captureXS; };
};

class ScatterXS : public XSection 
{
  private:
    std::vector< std::vector< double > > scatterXS; // size g^2
    std::vector< double >                scatterTotalXS; // size g-> the total for each group (s11+s12+s13...+s1g)

  public:
    ScatterXS( std::vector< std::vector< double > > scatterXSi );
   ~ScatterXS() {};

    double getXS( int group ) { return scatterTotalXS[group-1]; };

    // get XS vectors
    std::vector< std::vector< double > > getScatterXS()      { return scatterXS;      };
    std::vector< double >                getScatterTotalXS() { return scatterTotalXS; };
};

class FissionXS : public XSection 
{
  private:
    std::vector< double > fissionXS; // size g
    std::vector< double > nu; // size g
    std::vector< double > chi; // size g

  public:
    FissionXS( std::vector< double > fissionXSi, std::vector< double > nui, std::vector< double > chii ) 
    : fissionXS( fissionXSi ), nu( nui ), chi( chii ) { xsName = "Fission"; };
   ~FissionXS() {};

    double getXS ( int group ) { return fissionXS[group-1]; };

    // get XS vectors
    std::vector< double > getFissionXS() { return fissionXS; };
    std::vector< double > getNu()        { return nu;        };
    std::vector< double > getChi()       { return chi;       };
};

#endif