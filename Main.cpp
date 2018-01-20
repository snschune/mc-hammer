/*
 Author: ESGonzalez
 Date: 1/10/18
 Req. Files: Material.h
 */


#include "Transport.h"
#include <memory>

typedef std::shared_ptr<Transport> T_ptr;

int main(int argc , char *argv[]) {
    
    int nHist = 0;

    if ( argc > 1 ) {
        nHist = atoi( argv[1] );
    }

    Constants constants;
    constants.setNumGroups(2);
    constants.lock();

    // TODO read this stuff from input
    std::string filename = "Berp.xs";
    Geometry geometry( filename, constants.getNumGroups(), true );
    
    T_ptr t = std::make_shared<Transport>(geometry , constants , nHist);
    
    //cout << "setting up..." << endl;
    //t->setup();
    //cout << "completed" << endl;
    cout << "running transport..." << endl;
    t->runTransport();
    cout << "completed" << endl;
    t->output();
    
    return 0;
}

