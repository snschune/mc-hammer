/*
 Author: ESGonzalez
 Date: 01/08/18
*/

#include "Geometry.h"

Cell_ptr Geometry::whereAmI( point pos ) 
{ // Returns a pointer to the cell
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

/*
void Geometry::readXS( std::string filename , int nGroups, bool loud )
{
  std::vector< double >                  fissionxs;
  std::vector< double >                  nu;
  std::vector< double >                  chi;
  std::vector< double >                  totalxs;
  std::vector< double >                  scatterxsTotal;
  std::vector< double >                  absorptionxs;
  std::vector< double >                  capturexs;
  std::vector< std::vector< double > >   scatterxs;
  
  std::ifstream xs_file;
  std::string   dummyLine;
  std::string   xsDirectory = "xsfiles/";
  int           num_materials;
  int           material_id = 0;
  double        temp_xs;
  
  xs_file.open( xsDirectory+filename );
  
  if ( xs_file.fail() )
  { // make sure file opens
    std::cerr << "Error! XS file could not be opened." << std::endl;
    throw;
  }
  
  if ( loud ) 
  { // provide extra information if "loud" is true
    std::cout << "Reading XS file..." << std::endl;
  }
  
  // first line of the file gives number of materials
  xs_file >> num_materials;
  
  if ( loud ) 
  { // provide extra information if "loud" is true
    std::cout << "\tFilename: " << filename << std::endl;
    std::cout << "\tNumber of energy groups: " << nGroups << std::endl;
    std::cout << "\tNumber of materials: " << num_materials << std::endl;
  }
  
  if ( num_materials == 0 ) { // make sure there are XS's to read
    std::cerr << "Error! No materials to read from file." << std::endl;
    throw;
  }
  
  for (int i = 1; i < ( num_materials + 1 ); ++i) 
  {
    // read XS's
    xs_file >> material_id;
    
    getline( xs_file,dummyLine ); // material id line  
    for ( int j=0; j < nGroups; ++j ) 
    {
      // chi
      xs_file >> temp_xs;
      chi.push_back( temp_xs );
    }  
    for ( int j=0; j < nGroups; ++j ) 
    {
      // dummy variables
      double dummy_xs;
      xs_file >> dummy_xs;
    }
    
    for ( int j=0; j < nGroups; ++j ) 
    {
      // fission
      xs_file >> temp_xs;
      fissionxs.push_back( temp_xs );
    }
    
    for ( int j=0; j < nGroups; ++j ) 
    {
      // nu
      xs_file >> temp_xs;
      nu.push_back( temp_xs );
    }
    
    for ( int j=0; j < nGroups; ++j ) 
    {
      // total
      xs_file >> temp_xs;
      totalxs.push_back( temp_xs );
    }
    
    //create vector of vectors (GxG filled with zeroes)
    for( int j = 0; j < nGroups; ++j )
    {
      std::vector<double> tempVector;
      int tempVal = 0;
      for( int k = 0; k < nGroups; ++k )
      {
      	tempVector.push_back( tempVal );
      }
      scatterxs.push_back( tempVector );
      tempVector.clear();
    }  
    // fill scatter matrix
    for ( int gout=0; gout < nGroups; ++gout ) 
    { // loop over outgoing energy
      for ( int gin=0; gin < nGroups; ++gin ) 
      { // loop over incident energy
        xs_file >> temp_xs;
        scatterxs[gin][gout] = temp_xs;             
      }
    }  
    // fill scatterTotal and absorption vectors
    for ( int j=0; j < nGroups; ++j ) 
    { // loop over rows
      double scatter_tot_xs = 0;
      for ( int k=0; k < nGroups; ++k ) 
      { // loop over collumns
        scatter_tot_xs += scatterxs[j][k];                         
      }  
      // absorption and capture
      scatterxsTotal.push_back( scatter_tot_xs );
      temp_xs = totalxs[j] - scatter_tot_xs;
      absorptionxs.push_back( temp_xs );
      temp_xs = absorptionxs[j] - fissionxs[j];
      capturexs.push_back( temp_xs );
    }  

    Reaction_ptr captReaction = std::make_shared<Capture>( nGroups, capturexs          );
    Reaction_ptr scatReaction = std::make_shared<Scatter>( nGroups, scatterxs          );
    Reaction_ptr fissReaction = std::make_shared<Fission>( nGroups, fissionxs, nu, chi );  
    std::string nucLabel = "nuc" + std::to_string( material_id );
    Nuclide_ptr  tempNuclide  = std::make_shared<Nuclide>( nucLabel );
    tempNuclide->addReaction( captReaction );
    tempNuclide->addReaction( scatReaction );
    tempNuclide->addReaction( fissReaction );  
    std::string matLabel = "mat" + std::to_string( material_id );
    Mat_ptr tempMaterial = std::make_shared<Material>( matLabel, 1.0 );
    tempMaterial->addNuclide( tempNuclide, 1.0 );
    
    addMaterial( tempMaterial );
    
    // clear XS vectors
    chi.clear();
    fissionxs.clear();
    nu.clear();
    totalxs.clear();
    scatterxs.clear();
    scatterxsTotal.clear();
    absorptionxs.clear();
    capturexs.clear();
  }
  
  // make sure all materials were read
  if ( material_id != num_materials ) 
  {
    std::cerr << "Error. Final material ID number does not match number of materials." << std::endl;
  }
  
  if ( loud ) 
  { // provide extra information if "loud" is true
    std::cout << "\n\tCross sections read in successfully.\n" << std::endl;
  }
  
  xs_file.close(); //close XS input file
}
*/