#include "Transport.h"
#include "Logo.h"
#include <memory>
#include "HammerTime.h"

typedef std::shared_ptr<Transport>   T_ptr;
typedef std::shared_ptr<Mesh>        Mesh_ptr;
typedef std::shared_ptr<HammerTime>  Time_ptr;

int main(int argc , char *argv[]) 
//INPUT: numHis numGroups xsFileName meshFileName
//numHis: number of histories (initialized to 1)
//numGroups: number of groups we will be considering (initialized to 1)
//xsFileName: the input file containing a list of the cross sections (initialized to Berp.xs)
//meshFileName: the input file containing a list of tets (initialized to coarse.thrm)
//entering "test" as the filename will start a test case for calculating leaking out of a sphere
//TODO:
//outputfilename
//surface/cell information input file?
//

{
	//tester variables
	bool testmode = false;
	double rad = 1.0;
	double xsec = 1.0;
	//

	Constants constants;
	int nHist = 1000;
	int numGroups = 1;
	std::string xsFileName = "test";
    std::string meshFileName = "coarse.thrm";
    bool loud = true; // Print extended dialogue
	
	
	if ( argc > 1 ) 
	{
		nHist = 	atoi( argv[1] );
		numGroups = atoi( argv[2] );
		xsFileName = argv[3];
        meshFileName = argv[4];
	}

	constants.setNumGroups(numGroups);
	constants.setNumHis(nHist);
	constants.lock();
		
    printLogo();
    
    // initialize geometry
	Geometry geometry( xsFileName, constants.getNumGroups(), constants.getNumHis(), loud );
    Mesh mesh( meshFileName, loud , constants);
    Mesh_ptr m = std::make_shared<Mesh>(mesh);
    
    // initialize a timer
    HammerTime time;
    Time_ptr timer = std::make_shared<HammerTime>(time);

	T_ptr t = std::make_shared<Transport>(geometry , constants , nHist , m , timer);

	cout << "running transport..." << endl;
	t->runTransport();
	cout << "Printing outputs..." << endl;
	t->output();

	return 0;
}

