#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>
#include <iostream>
#include <cmath> 

#include "Catch.h"
#include "Input.h"
#include "Transport.h"


TEST_CASE( "Absorber", "[absorber]" ) {

    double sigt = 1.0;
    double rad    = 4.0;
    double tau  = sigt * rad;
    int nGroups = 1;
    int nHist   = 100000;

    // set and lock constants
    std::shared_ptr< Constants > constants = std::make_shared< Constants > ();
    constants->setNumGroups( nGroups );
    constants->setNumHis( nHist );
    constants->lock();

    // setup super classes
    std::shared_ptr< Geometry > geometry = std::make_shared< Geometry >   ();
    std::shared_ptr< Mesh     > mesh     = std::make_shared< Mesh     >   ( "berpinpolyinair.thrm", false, constants );
    std::shared_ptr< HammerTime > timer  = std::make_shared< HammerTime > ();
    
    // setup material
    std::vector< double > totalXS;
    totalXS.push_back( sigt );

    std::shared_ptr< Nuclide > Nuc = std::make_shared< Nuclide > ( "theNuclude" );
    Nuc->addReaction( std::make_shared< Capture > ( 1, totalXS ) );

    std::shared_ptr< Material > Mat = std::make_shared< Material > ( "theMaterial", 1.0 );
    Mat->addNuclide( Nuc, 1.0 );

    // setup cell
    std::shared_ptr< surface > S = std::make_shared< sphere > ( "theSphere", 0, 0, 0, rad );
    std::shared_ptr< Cell > Cel = std::make_shared< Cell > ( "theCell" );
    std::shared_ptr< Estimator > Est = std::make_shared< CollisionTally >( "theEstimator" );
    std::pair< std::shared_ptr< surface >, bool > surfPair = std::make_pair( S, -1 );

    Cel->setMaterial( Mat );
    Cel->addEstimator( Est );
    Cel->addSurfacePair( surfPair );

    // setup source
    std::vector< double > sourceGroups;
    sourceGroups.push_back( 1.0 );

    std::shared_ptr< Source > sourc = std::make_shared< setSourceSphere > ( "theSource", 0, 0, 0, 0, rad, sourceGroups );

    // add objects to geometry
    geometry->addSurface( S );
    geometry->addCell( Cel );
    geometry->setSource( sourc );

    // setup transport
    std::shared_ptr< Transport > t = std::make_shared<Transport>( geometry, constants, mesh, timer );
    t->runTransport();
    double tally = Cel->getSingleGroupTally(nGroups, nHist).first;
    double stdev = Cel->getSingleGroupTally(nGroups, nHist).second;

    double analyticSolution = 0.818341685; // will need to put in equation for this
    double tol = 0.005;

    // test returns tally
    SECTION ( " check analytic solution " ) {
      REQUIRE( abs( tally - analyticSolution ) < tol ); // turn this into a function of stdev
    }
}
