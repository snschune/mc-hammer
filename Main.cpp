#include "Transport.h"
#include <memory>

typedef std::shared_ptr<Transport> T_ptr;

int main(int argc , char *argv[]) 
//INPUT: numHis numGroups xsfilename 
//numHis: number of histories (initialized to 1)
//numGroups: number of groups we will be considering (initialized to 1)
//xsfilename: the input file containing a list of the cross sections (initialized to Berp.xs)
//entering "test" as the filename will start a test case for calculating leaking out of a sphere
//TODO: 
//tetfilename: the input file containing the information about the mesh
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
	int numGroups = 2;
	std::string xsFilename = "Berp.xs";
	
	
	if ( argc > 1 ) 
	{
		nHist = 	atoi( argv[1] );
		numGroups = atoi( argv[2] );
		xsFilename = argv[3];
	}
	constants.setNumGroups(numGroups);
	constants.setNumHis(nHist);
	constants.lock();
	

		
	Geometry geometry( xsFilename, constants.getNumGroups(), true );
	

	T_ptr t = std::make_shared<Transport>(geometry , constants , nHist);

	cout << "running transport..." << endl;
	t->runTransport();
	cout << "completed" << endl;
	t->output();

	return 0;
}

