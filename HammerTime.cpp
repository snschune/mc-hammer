#include "HammerTime.h"

void HammerTime::startHist() {
    startTimer("History");
}

void HammerTime::endHist() {
    endTimer("History");
}

void HammerTime::startTimer( string key ) { 
    currentTimes[key] = clock();
}

void HammerTime::endTimer( string key ) {
    // check if key exists in currentTimes, 
    // which it would if startTimer has been called for this key
    if ( currentTimes.count(key) == 0) {
        std::cerr << "An endTimer() was called for a process for which the timer was never started! " << std::endl;
    } 
    else {
        // if the key exists, add a result
        clock_t time = clock() - currentTimes[key];
        results[key] += ((double)time) / CLOCKS_PER_SEC ; 
        calls[key]++;
    }
}

std::map <string , double> HammerTime::getAvgResults() {
    // check if the average has already been calculated
    if( ! avgResults.empty() ) {
        return(avgResults);
    }
    else {
        // take the average of each result vector
        for (const auto& any : results) {
            avgResults[any.first] = any.second / calls[any.first];
        }
    }
    return(avgResults);
}

void HammerTime::printAvgResults(string fname) {
    std::cout << std::endl << "Printing timing results to " << fname << ".." << std::endl;
    
    // check if the average has already been calculated
    if(avgResults.empty() ) {
        // take the average of each result vector
        for (const auto& any : results) {
            avgResults[any.first] = any.second / calls[any.first];
        }
    }
    // print the average results
    std::ofstream timeOut;
    timeOut.open( fname );
    timeOut << "Timing results averaged over " <<  calls["Histories"] << " histories:" << std::endl;
    for (const auto& any : avgResults) {
        timeOut << any.first << "   " << any.second << "  This block ran " << calls[any.first] << " times." << std::endl;
    }
}

double HammerTime::getAvgResult( string key ) {
    if(avgResults.empty() ) {
        // take the average of each result vector
        for (const auto& any : results) {
            avgResults[any.first] = any.second / calls[any.first];
        }
    }
    if ( avgResults.count(key) == 0 ) {
        std::cerr << "An was avgResult was called for a non-existent key! " << std::endl;
    } 
    else{ 
        return(avgResults[key]);
    }
 
    return(0);
}

double HammerTime::getAvgHistoryTime() {
    if(avgResults.empty() ) {
        // take the average of each result vector
        for (const auto& any : results) {
            avgResults[any.first] = any.second / calls[any.first];
        }
    }
    return(avgResults["History"]);
}
