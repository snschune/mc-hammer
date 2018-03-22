#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <vector>
#include <iostream>

#include "Catch.h"
#include "Utility.h"


TEST_CASE( "Utility", "[utility]" ) {

    std::vector< int    > intVec;
    std::vector< double > doubleVec, doubleVec2;

    for (int i=1; i<5; i++)
    {
      intVec.push_back( i );
      doubleVec.push_back( i * 1.0 );
      doubleVec2.push_back( i * 1.0 + 4.0 );
    }

    
    // test returns sum of vector
    SECTION ( " sum a vector " ) {
      REQUIRE( Utility::vecSum( intVec ) == 10 );
      REQUIRE( Utility::vecSum( doubleVec ) == 10.0 );
    }

    // test returns mean of vector
    SECTION ( " return mean of a vector " ) {
      // failed for intVec
      REQUIRE( Utility::vecMean( doubleVec ) == 2.5 );
    }

    // test returns dot product of vector
    SECTION ( " return mean of a vector " ) {
      REQUIRE( Utility::vecDot( doubleVec, doubleVec2 ) == 70 );
    }

}
