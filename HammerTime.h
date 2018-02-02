/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 */

#ifndef _TIME_HEADER_
#define _TIME_HEADER_

#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include "Utility.h"

using std::string;
using std::vector;

class HammerTime {
    // this class is for timeing various subroutines in transport
    // Each history, any function can be timed by calling start and end on either side of it
    // At the beginning and end of each history, startHist() and endHist() should be called, so as to calculate average history time
    // There are multiple functions to get or print the results of the timer
    private:
        std::map<string , vector<double> >  results;
        std::map<string , clock_t >         currentTimes;
        std::map<string , double>           avgResults;
    public:
        HammerTime() {};
       ~HammerTime() {};

       void startHist();
       void endHist();

       void startTimer( string key );
       void endTimer( string key );

       std::map<string , double> getAvgResults(); 
       void printAvgResults(string fname);

       double getAvgResult( string key );
       double getAvgHistoryTime();
};



#endif

