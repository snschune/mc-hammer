#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <tgmath.h> 
#include "../Catch.h"
#include "../Estimator.h"

bool close(double a , double b) {
    std::cout << "abs(" << a << " , " << b << ") = " << fabs(a-b) << std::endl;
    return(fabs(a - b) < 0.0001);
};


TEST_CASE( "Estimator base class set/gets", "[Estimator]" ) {

    Estimator est;

    est.score(1.0);
    est.score(1.0);

    // score does the thing right
    SECTION ( " test score " ) {
      REQUIRE( close( est.getCurrentHistTally() ,  2.0));
    }
    
    est.endHist();
    est.score(1.0);
    est.score(1.0);
    est.score(1.0);
    
    // score does the thing right
    SECTION ( " test score again" ) {
      REQUIRE( est.getCurrentHistTally() ==  3.0);
    }

    est.endHist();
    est.score(1.0);
    est.score(1.0);
    est.endHist();

    // history tallies work
    SECTION ( " test flux " ) {
      REQUIRE( close( est.getScalarEstimator(3).first , 2.3333) );
    }

    SECTION ( " test uncertainty " ) {
      REQUIRE( close( est.getScalarEstimator(3).second , 0.57735) );
    }
  
}

TEST_CASE( "collision estimator std dev", "[Estimator]" ) {

    Estimator est2;

    est2.score(0.17);
    est2.score(0.12);
    est2.endHist();
    est2.score(3.2);
    est2.endHist();

    // history tallies work
    SECTION ( " test flux " ) {
      REQUIRE( close( est2.getScalarEstimator(2).first , 7.26409) );
    }

    SECTION ( " test uncertainty " ) {
      REQUIRE( close( est2.getScalarEstimator(2).second , 9.83104) );
    }
  
}


TEST_CASE( "Estimator with no scores" , "[Estimator]" ) {

    Estimator est;
    est.endHist();
    
    // history tallies work
    SECTION ( " test flux " ) {
      REQUIRE( est.getScalarEstimator(1).first == 0.0 );
    }

    SECTION ( " test uncertainty " ) {
      REQUIRE( close( est.getScalarEstimator(1).second , 0.0) );
    }
  
}

//TODO test case for vecSum, std dev and tally system
//print statements for fer-particle problem to verify tally manually

