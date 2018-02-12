/*
 Author: ESGonzalez
 Date: 01/08/18
 /////////// Start Revision Log ///////////
 ESG - 01/26/18: Pulled XS reading out of setup and into its own function
 ESG - 01/31/18: Exit program if xs file failed to open
 ESG - 02/05/18: Fixed scatter_tot_xs vector in readXS()
 ESG - 02/11/18: Overhauled for xml formatting
 /////////// End Revision Log ///////////
*/

#include "Geometry.h"

Geometry::Geometry( std::string filename , int num_groups, int nhist, bool loud )
{
    //read in the cross sections from file
    readXS( filename, num_groups, loud );
}

void Geometry::readXS( std::string filename , int num_groups, bool loud )
{
    std::vector< double >   fissionxs;
    std::vector< double >   nu;
    std::vector< double >   totalxs;
    std::vector< std::vector< double > >   scatterxs;
    std::vector< double > scatterxsTotal;
    std::vector< double >   absorptionxs;
    
    std::ifstream xs_file;
    std::string dummyLine;
    std::string xsDirectory = "xsfiles/";
    int num_materials;
    int material_id = 0;
    double temp_xs;
    
    xs_file.open( xsDirectory+filename );
    
    if ( xs_file.fail() ){ // make sure file opens
        std::cerr << "Error! XS file could not be opened." << std::endl;
        exit(1);
    }
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "Reading XS file..." << std::endl;
    }
    
    // first line of the file gives number of materials
    xs_file >> num_materials;
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "\tFilename: " << filename << std::endl;
        std::cout << "\tNumber of energy groups: " << num_groups << std::endl;
        std::cout << "\tNumber of materials: " << num_materials << std::endl;
    }
    
    if ( num_materials == 0 ) { // make sure there are XS's to read
        std::cerr << "Error! No materials to read from file." << std::endl;
        exit(1);
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
        
        //create vector of vectors (GxG filled with zeroes)
        for(int j = 0; j<num_groups; ++j)
        {
        	std::vector<double> tempVector;
        	int tempVal = 0;
        	for(int k = 0; k<num_groups; ++k)
        	{
        		tempVector.push_back(tempVal);
        	}
        	scatterxs.push_back(tempVector);
        	tempVector.clear();
        }

        // fill scatter matrix
        for (int j=0; j < num_groups; ++j) { // loop over rows
            for (int k=0; k < num_groups; ++k) { // loop over collumns
                xs_file >> temp_xs;
                scatterxs[k][j] = temp_xs;             
            }
        }

        // fill scatterTotal and absorption vectors
        for (int j=0; j < num_groups; ++j) { // loop over rows
            double scatter_tot_xs = 0;
            for (int k=0; k < num_groups; ++k) { // loop over collumns
                scatter_tot_xs += scatterxs[j][k];                         
            }

            // absorption
            scatterxsTotal.push_back(scatter_tot_xs);
            temp_xs = totalxs[j] - scatter_tot_xs;
            absorptionxs.push_back(temp_xs);
        }

        std::string matLabel = "mat" + std::to_string( material_id );
        
        Mat_ptr tempMaterial = std::make_shared<Material>( matLabel, num_groups );
        tempMaterial->addTotalXS( totalxs );
        tempMaterial->addAbsXS( absorptionxs );
        tempMaterial->addScaXS( scatterxs );
        tempMaterial->addScaTotXS( scatterxsTotal );
        
        Geometry::addMaterial( tempMaterial );
        
        // clear XS vectors
        fissionxs.clear();
        nu.clear();
        totalxs.clear();
        scatterxs.clear();
        scatterxsTotal.clear();
        absorptionxs.clear();
        
    }
    
    // make sure all materials were read
    if ( material_id != num_materials ) {
        std::cerr << "Error. Final material ID number does not match number of materials." << std::endl;
    }
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "\n\tCross sections read in successfully.\n" << std::endl;
    }
    
    xs_file.close(); //close XS input file
}

void Geometry::addCell(Cell_ptr newCell )
{
    cells.push_back(newCell);
}

void Geometry::addSurface( Surf_ptr newSurface )
{
    surfaces.push_back(newSurface);
}

void Geometry::addMaterial( Mat_ptr newMaterial )
{
    materials.push_back(newMaterial);
}

void Geometry::setSource( Source_ptr newSource )
{
    source = newSource;
}

Cell_ptr Geometry::whereAmI( point pos ) {

    Cell_ptr hereIAm = nullptr;
    for( auto cell : cells ) {
        if ( cell->amIHere( pos ) == true ) {
            hereIAm = cell;
        }
    }
    return hereIAm;
}
