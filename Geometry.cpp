/*
 Author: ESGonzalez
 Date: 1/8/18
 */

#include "Geometry.h"
Geometry::Geometry( std::string filename , int num_groups, bool loud )
{
    setup( filename, num_groups, loud );
}


void Geometry::setup( std::string filename , int num_groups, bool loud )
{
	if(filename == "test")
	{

		double radius = 0.01;
		double xsec = 1.0;
		
		//std::cout << "Test case specified.\nRadius: ";
		//std::cin >> radius;
		//std::cout << "Total Xsec: ";
		//std::cin >> xsec;

		//surface
		Surf_ptr sphere1 = make_shared<sphere>("sphere1", 0.0, 0.0, 0.0, radius);
		surfaces.push_back(sphere1);
	
		//Material
		vector<double> totalXSec;
		vector<double> siga;
		vector<vector<double>> sigs;
		vector<double> sigst;

		totalXSec.push_back(xsec);
		siga.push_back(xsec);
		sigst.push_back(0.0);
		sigs.push_back(sigst);
		Mat_ptr mat1 = make_shared<Material>(1, totalXSec, siga, sigs, sigst);
		materials.push_back(mat1); 
	
		//collision tally
		vector< Estimator_ptr > estimators;
		Estimator_ptr e1 = make_shared<CollisionTally>();
		estimators.push_back(e1);


		//cell
		pair< Surf_ptr, bool > surfpair1 (sphere1, true);
		vector< pair< Surf_ptr, bool > > cellSurfpairs1;
		cellSurfpairs1.push_back(surfpair1);
		Cell_ptr cell1 = make_shared<Cell>(mat1, cellSurfpairs1  , estimators );
		cells.push_back(cell1);
		cell1->name = "cell 1";

		//source
		vector<double> sourceGroups;
		sourceGroups.push_back(1.0);
		source = make_shared<setSourceSphere>(0.0, 0.0, 0.0, 0.0, radius, sourceGroups);
	}
	else
	{
		std::vector< double >   fissionxs;
		std::vector< double >   nu;
		std::vector< double >   totalxs;
		std::vector< vector< double > >   scatterxs;
		std::vector< double > scatterxsTotal;
		std::vector< double >   absorptionxs;

		std::ifstream xs_file;
		std::string dummyLine;
		int num_materials;
		int material_id = 0;
		double temp_xs;

		xs_file.open( filename );

		if ( xs_file.fail() ){ // make sure file opens
		   std::cout << "Error! File could not be opened." << std::endl;
		}

		if ( loud ) { // provide extra information if "loud" is true
		   std::cout << "Reading XS file..." << std::endl;
		}

		// first line of the file gives number of materials
		xs_file >> num_materials;

		if ( num_materials == 0 ) { // make sure there are XS's to read
		   std::cout << "Error! No materials to read from file." << std::endl;
		}

		for (int i = 1; i < (num_materials + 1); ++i) {
		   
		   // read XS's
		   xs_file >> material_id;
		   // The first three lines of a block do not contain XS's
		   getline(xs_file,dummyLine); // material id line
		   getline(xs_file,dummyLine); // chi
		   getline(xs_file,dummyLine); // energy bounds
		   
		   for (int j=0; j < num_groups; ++j) {
			  // fission
			  xs_file >> temp_xs;
			  fissionxs.push_back(temp_xs);
		   }
		   
		   for (int j=0; j < num_groups; ++j) {
			  // nu
			  xs_file >> temp_xs;
			  nu.push_back(temp_xs);
		   }
		   
		   for (int j=0; j < num_groups; ++j) {
			  // total
			  xs_file >> temp_xs;
			  totalxs.push_back(temp_xs);
		   }
		   
		   for (int j=0; j < num_groups; ++j) {
			  double scatter_tot_xs = 0;
			  vector< double> tempxsVec;
			  for (int k=0; k < num_groups; ++k) {
				 // scatter
				 xs_file >> temp_xs;
				 
				 tempxsVec.push_back(temp_xs);
				 scatter_tot_xs += temp_xs;
			  }
			  // absorption
			  scatterxs.push_back(tempxsVec);
			  tempxsVec.clear();
			  scatterxsTotal.push_back(scatter_tot_xs);
			  temp_xs = totalxs[j] - scatter_tot_xs;
			  absorptionxs.push_back(temp_xs);
		   }
		   
		   Mat_ptr temp_material = std::make_shared<Material>( num_groups, totalxs, absorptionxs, scatterxs, scatterxsTotal );
		   
		   materials.push_back( temp_material );
		   
		   // clear XS vectors
		   fissionxs.clear();
		   nu.clear();
		   totalxs.clear();
		   scatterxs.clear();
		   absorptionxs.clear();
		   
		}

		// make sure all materials were read
		if ( material_id != num_materials ) {
		   std::cout << "Error. Final material ID number does not match number of materials." << std::endl;
		}

		if ( loud ) { // provide extra information if "loud" is true
		   std::cout << "Cross sections read in successfully." << std::endl;
		}

		xs_file.close(); //close XS input file


		//surface bounbdaries
		Surf_ptr sphere1 = make_shared<sphere>("sphere1", 0.0, 0.0, 0.0, 3.0);
		Surf_ptr sphere2 = make_shared<sphere>("sphere2", 0.0, 0.0, 0.0, 10.0);
		surfaces.push_back(sphere1);
		surfaces.push_back(sphere2);


		//create estimator TODO add input for estimators
		// need to input a new vector of a shared pointer to an estimator (one for each group) to the cell
		//
		// Generate a Collision estimator for each group
		vector< Estimator_ptr > estimators1;
		for (int i = 1; i <= num_groups; ++i) {
		   estimators1.push_back( std::make_shared< CollisionTally >() );  
		}
		vector< Estimator_ptr > estimators2;
		for (int i = 1; i <= num_groups; ++i) {
		   estimators2.push_back( std::make_shared< CollisionTally >() );  
		}
	

		//custom material for testing

		//create cells
		pair< Surf_ptr, bool > surfpair1 (sphere1, true);
		vector< pair< Surf_ptr, bool > > cellSurfpairs1;
		cellSurfpairs1.push_back(surfpair1);
		Cell_ptr cell1 = make_shared<Cell>(materials[0] , cellSurfpairs1  , estimators1 );
		cells.push_back(cell1);
		cell1->name = "cell 1";

		pair< Surf_ptr, bool > surfpair2_1 (sphere1, false);
		pair< Surf_ptr, bool > surfpair2_2 (sphere2, true);
		vector< pair< Surf_ptr, bool > > cellSurfpairs2;
		cellSurfpairs2.push_back(surfpair2_1);
		cellSurfpairs2.push_back(surfpair2_2);
		Cell_ptr cell2 = make_shared<Cell>(materials[1] , cellSurfpairs2  , estimators2 );
		cells.push_back(cell2);
		cell2->name = "cell 2";

		//create source
		vector<double> sourceGroups;
		sourceGroups.push_back(1.0);
		sourceGroups.push_back(0.0);
		source = make_shared<setSourceSphere>(0.0, 0.0, 0.0, 0.0, 3.0, sourceGroups);
	}
    
	

}



Cell_ptr Geometry::whereAmI( point pos )
{
    
    Cell_ptr hereIAm = nullptr;
    
    for( auto cell : cells )
    {
        if ( cell->amIHere( pos ) == true )
        {
            hereIAm = cell;
        }
    }
	return hereIAm;
}


void Geometry::addCell(Cell_ptr newCell)
{
    cells.push_back(newCell);
}

void Geometry::addSurface( Surf_ptr newSurface)
{
    surfaces.push_back(newSurface);
}




