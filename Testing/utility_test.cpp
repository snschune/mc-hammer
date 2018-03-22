#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <vector>
#include <iostream>

#include "Catch.h"
#include "Utility.h"


TEST_CASE( "Utility", "[utility]" ) {

    std::vector< int    > intVec;
    std::vector< double > doubleVec;

    for (int i=1; i<5; i++)
    {
      intVec.push_back( i );
      doubleVec.push_back( i * 1.0 );
    }

    
    // test returns sum of integer vector
    SECTION ( " sum a vector of integers " ) {
      REQUIRE( Utility::vecSum( intVec ) == 10 );
    }

    // test returns sum of double vector
    SECTION ( " sum a vector of doubles " ) {
      REQUIRE( Utility::vecSum( doubleVec ) == 10.0 );
    }

}
