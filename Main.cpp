/*
 Author: ESGonzalez
 Date: 1/10/18
 Req. Files: Material.h
 */


#include "Transport.h"
#include <memory>

typedef std::shared_ptr<Transport> T_ptr;

int main(int argc , char *argv[]) 
//INPUT: numHis numGroups xsfilename 
//numHis: number of histories (initialized to 1)
//numGroups: number of groups we will be considering (initialized to 1)
//xsfilename: the input file containing a list of the cross sections (initialized to Berp.xs)
//to add: 
//tetfilename: the input file containing the information about the mesh
//outputfilename
//surface/cell information input file?

{
	//tester variables
	bool testmode = false;
	double rad = 1.0;
	double xsec = 1.0;
	//

	Constants constants;
	int nHist = 0;
	int numGroups = 1;
	std::string filename = "Berp.xs";
	
	
	if ( argc > 1 ) 
	{
		nHist = 	atoi( argv[1] );
		numGroups = atoi( argv[2] );
		if(argv[3] == "test")
		{
			testmode = true;
			rad  = atof( argv[4] );
			xsec = atof( argv[5] );
			
		}
		else
			filename = argv[3];
	}
	constants.setNumGroups(numGroups);
	constants.setNumHis(nHist);
	constants.lock();
	

	// TODO read this stuff from input
	if(testmode)
	{
		Geometry geometry(rad, xsec);
		vector<double> sourceGroups;
		sourceGroups.push_back(1.0);
		sourceGroups.push_back(0.0);
		setSourceSphere psource = setSourceSphere(0.0, 0.0, 0.0, 0.0, rad, sourceGroups);
	}
	else
	{
		vector<double> sourceGroups;
		sourceGroups.push_back(1.0);
		sourceGroups.push_back(0.0);
		setSourceSphere psource = setSourceSphere(0.0, 0.0, 0.0, 0.0, 3.0, sourceGroups);
		Geometry geometry( filename, constants.getNumGroups(), true );
	}

	T_ptr t = std::make_shared<Transport>(geometry , constants , nHist);

	cout << "running transport..." << endl;
	t->runTransport();
	cout << "completed" << endl;
	t->output();

	return 0;
}

