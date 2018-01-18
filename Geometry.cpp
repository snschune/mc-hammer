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
    
    for (int i = 1; i < (num_materials + 1); ++i){
        
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
    Surf_ptr plane1 = make_shared<plane>("plane1", 0.0, 0.0, 1.0, 0.0);
    Surf_ptr plane2 = make_shared<plane>("plane2", 0.0, 0.0, 1.0, 5.0);
    surfaces.push_back(plane1);
    surfaces.push_back(plane2);
    
    
    //create cell
    pair< Surf_ptr, bool > surf1 (plane1, false);
    pair< Surf_ptr, bool > surf2 (plane2, true );
    vector< pair< Surf_ptr, bool > > cellSurfaces1;
    cellSurfaces1.push_back(surf1);
    cellSurfaces1.push_back(surf2);
    Cell_ptr cell1 = make_shared<Cell>(materials[0], cellSurfaces1);
    cells.push_back(cell1);
    
    
    
}

/*
 bool Geometry::amIHere( point pos, Cell& cell )
 {
 // requires a vector of pairs of surfaces and sense (bool) for each cell
 vector< pair<Surf_ptr ,bool> > surfNSenses = cell.getSurfNSenses();
 
 bool isWithin = true;
 //cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
 for( auto surfNSense : surfNSenses )
 {
 bool test = ( get<0>(surfNSense)->eval(pos) < 0 );
 isWithin = isWithin && ( test == get<1>(surfNSense) );
 }
 return isWithin;
 }
 */

Cell_ptr Geometry::whereAmI( point pos )
{
    
    Cell_ptr hereIAm = nullptr;
    
    for( auto cell : cells )
    {
        if ( bool test = cell->amIHere( pos ) == true )
        {
            hereIAm = cell;
        }
    }
    if(hereIAm == nullptr)
    {
	   std::cerr << "Particle unable to be located\n Exiting..." << endl;
	   exit(1);
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


