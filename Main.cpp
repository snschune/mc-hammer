/*
 Author: ESGonzalez
 Date: 1/10/18
 Req. Files: Material.h
 */

#include "Geometry.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int num_groups = 2;
    
    Geometry( "Berp.xs", num_groups, true );
    
    return 0;
}

/*
#include "Transport.h"
#include <memory>

typedef std::shared_ptr<Transport> T_ptr;

int main()
{
    T_ptr t = std::make_shared<Transport>();
    
    //cout << "setting up..." << endl;
    //t->setup();
    //cout << "completed" << endl;
    cout << "running transport..." << endl;
    t->runTransport();
    cout << "completed" << endl;
    t->output();
    
    return 0;
}
*/

