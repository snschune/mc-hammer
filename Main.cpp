#include "Transport.h"
#include "Logo.h"
#include "Input.h"
#include <memory>
#include "HammerTime.h"

typedef std::shared_ptr<Transport>   T_ptr;
typedef std::shared_ptr<Mesh>        Mesh_ptr;
typedef std::shared_ptr<HammerTime>  Time_ptr;

int main(int argc , char *argv[]) 
//INPUT: xmlFilename
//xmlFilename: the xml-formatted input file containing the problem parameters
//TODO:

{
    std::string xmlFilename = "inputfiles/";

    if ( argc > 1 ) 
    {
        xmlFilename += argv[1];
    }

    printLogo();

    // Initialize and read xml input
    std::shared_ptr< Input > input = std::make_shared< Input > ();
    input->readInput( xmlFilename );

    // Create pointers to geometry, constants, and mesh
    std::shared_ptr< Geometry >   geometry  = input->getGeometry();
    std::shared_ptr< Constants >  constants = input->getConstants();
    std::shared_ptr< Mesh >       mesh      = input->getMesh();
    std::shared_ptr< HammerTime > timer     = input->getTimer();

    T_ptr t = std::make_shared<Transport>( geometry, constants, mesh, timer );

    cout << "running transport..." << endl;
    t->runTransport();
    cout << std::endl << "Transport finished!" << std::endl;
    cout << std::endl << "************************************************************************" << std::endl;
    cout << "************************************************************************" << std::endl;
    cout << "Printing outputs..." << endl;
    t->output();

    return 0;
}