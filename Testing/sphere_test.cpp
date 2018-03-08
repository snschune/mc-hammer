#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>

#include "Catch.h"
#include "Surface.h"
#include "Random.h"


TEST_CASE( "Sphere", "[sphere]" ) {

    double x0 =  1.0;
    double y0 =  2.0;
    double z0 = -3.0;
    double r  =  4.0;

    std::string sphere_name = "mySphere";

    sphere theSphere( sphere_name, x0, y0, z0, r );

    // test returns appropriate name
    SECTION ( " return surface name " ) {
      REQUIRE( theSphere.name() == sphere_name );
    }

    // test evaluation for a single point outside sphere
    SECTION ( " evaluation outside sphere " ) {
      point p( 3.0, 2.0, 1.0 );
      double eval_result = 4.0;
      REQUIRE( theSphere.eval(p) == Approx( eval_result ) );
    }

    // test evaluation for a single point inside sphere
    SECTION ( " evaluation inside sphere " ) {
      point p( 1.0, 1.0, -1.0 );
      double eval_result = -11.0;
      REQUIRE( theSphere.eval(p) == Approx( eval_result ) );
    }    

    // test evaluation for a single point on sphere
    SECTION ( " evaluation on sphere " ) {
      point p( 1.0, 2.0, 1.0 );
      double eval_result = 0.0;
      REQUIRE( theSphere.eval(p) == Approx( eval_result ) );
    }

    // test 1000 random points in box from -10 to 10
    SECTION ( " random points near sphere " ) {
      bool rand_test_result = true;
      for ( unsigned i = 0 ; i < 1000 ; i++ ) {
        point  p( 20.0 * Urand() - 10.0, 20.0 * Urand() - 10.0, 20.0 * Urand() - 10.0 );
        double eval_result = pow( p.x - x0, 2 ) + pow( p.y - y0, 2 ) + pow( p.z - z0, 2 ) - r*r;
        rand_test_result = rand_test_result && ( theSphere.eval(p) == eval_result );
      }
      REQUIRE( rand_test_result );
    }

    // test smallest positive distance, one intersection
    SECTION ( " distance one intersection " ) {
      point p( 2.0, 2.0, -3.0 );
      point d( 1.0, 0.0, 0.0 );
      double eval_result = 3.0;
      REQUIRE( theSphere.distance( p, d ) == Approx( eval_result ) );
    } 

    // test smallest positive distance, two intersections
    SECTION ( " distance two intersections " ) {
      point p( -4.0, 2.0, -3.0 );
      point d( 1.0, 0.0, 0.0 );
      double eval_result = 1.0;
      REQUIRE( theSphere.distance( p, d ) == Approx( eval_result ) );
    } 

    // test smallest positive distance, no intersections (negative roots)
    SECTION ( " distance no intersections (negative roots) " ) {
      point p( -4.0, 2.0, -3.0 );
      point d( -1.0, 0.0, 0.0 );
      double eval_result = std::numeric_limits<double>::max();
      REQUIRE( theSphere.distance( p, d ) == Approx( eval_result ) );
    } 

    // test smallest positive distance, no intersections (complex roots)
    SECTION ( " distance no intersections (complex roots) " ) {
      point p( -4.0, 2.0, -3.0 );
      point d( 0.0, 0.0, 1.0 );
      double eval_result = std::numeric_limits<double>::max();
      REQUIRE( theSphere.distance( p, d ) == Approx( eval_result ) );
    } 

}

