#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>

#include "Catch.h"
#include "Surface.h"
#include "Random.h"


TEST_CASE( "Plane", "[plane]" ) {

    double a =  1.0;
    double b =  2.0;
    double c = -3.0;
    double d =  4.0;

    std::string plane_name = "myPlane";

    plane thePlane( plane_name, a, b, c, d );

    // test returns appropriate name
    SECTION ( " return surface name " ) {
      REQUIRE( thePlane.name() == plane_name );
    }

    // test evaluation for a single point outside plane
    SECTION ( " evaluation positive side of plane " ) {
      point p( 3.0, 2.0, -1.0 );
      double eval_result = +6.0;
      REQUIRE( thePlane.eval(p) == Approx( eval_result ) );
    }

    // test evaluation for a single point outside plane
    SECTION ( " evaluation negative side of plane " ) {
      point p( -3.0, -2.0, +1.0 );
      double eval_result = -14.0;
      REQUIRE( thePlane.eval(p) == Approx( eval_result ) );
    }

    // test evaluation for a single point on plane
    SECTION ( " evaluation on plane " ) {
      point p( 3.0, 2.0, 1.0 );
      double eval_result = +0.0;
      REQUIRE( thePlane.eval(p) == Approx( eval_result ) );
    }

    // test 1000 random points in box from -10 to 10
    SECTION ( " random points near plane " ) {
      bool rand_test_result = true;
      for ( unsigned i = 0 ; i < 1000 ; i++ ) {
        point  p( 20.0 * Urand() - 10.0, 20.0 * Urand() - 10.0, 20.0 * Urand() - 10.0 );
        double eval_result = a*p.x + b*p.y + c*p.z - d;
        rand_test_result = rand_test_result && ( thePlane.eval(p) == eval_result );
      }
      REQUIRE( rand_test_result );
    }

    // test smallest positive distance w/ intersection
    SECTION ( " distance with intersection " ) {
      point p( -3.0, -2.0, +1.0 );
      point d( 1.0, 0.0, 0.0 );
      double eval_result = 14.0;
      REQUIRE( thePlane.distance( p, d ) == Approx( eval_result ) );
    } 

    // test smallest positive distance w/ no intersection
    SECTION ( " distance with no intersection " ) {
      point p( -3.0, -2.0, +1.0 );
      point d( -1.0, 0.0, 0.0 );
      double eval_result = std::numeric_limits<double>::max();
      REQUIRE( thePlane.distance( p, d ) == Approx( eval_result ) );
    } 

}
