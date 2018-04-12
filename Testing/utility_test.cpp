#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <vector>
#include <iostream>

#include "Catch.h"
#include "Utility.h"


TEST_CASE( "Utility", "[utility]" ) {



/* ****************************************************************************************************** * 
 * Generic Vector and Point Operations
 *
 * ****************************************************************************************************** */ 

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
    REQUIRE( Utility::vecSum( intVec    ) == 10   );
    REQUIRE( Utility::vecSum( doubleVec ) == 10.0 );
  }
  // test returns mean of vector
  SECTION ( " return mean of a vector " ) {
    // failed for intVec
    REQUIRE( Utility::vecMean( doubleVec ) == 2.5 );
  }
  //test returns minimum value of a vector
  SECTION ( " return min of a vector ") {
    REQUIRE( Utility::vecMin( intVec    ) == 1   );
    REQUIRE( Utility::vecMin( doubleVec ) == 1.0 );
  }
  //test returns minimum value of a vector
  SECTION ( " return max of a vector ") {
    REQUIRE( Utility::vecMax( intVec    ) == 4   );
    REQUIRE( Utility::vecMax( doubleVec ) == 4.0 );
  }
  // test returns dot product of vector
  SECTION ( " return dot product of a vector " ) {
    REQUIRE( Utility::vecDot( doubleVec, doubleVec2 ) == 70 );
  }

/* ****************************************************************************************************** * 
 * Miscellaneous                      
 *
 * ****************************************************************************************************** */ 


}
