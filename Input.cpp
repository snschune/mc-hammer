/*
 Author: ESGonzalez
 Date: 02/09/18
 */

#include "Input.h"

void Input::readInput( std::string xmlFilename ) {

  pugi::xml_document input_file;
  pugi::xml_parse_result load_result = input_file.load_file( xmlFilename.c_str() );

  if ( ! load_result ) {
    std::cout << load_result.description() << std::endl;
    throw;
  }

  // get setup parameters
  pugi::xml_node input_setup = input_file.child("setup");
  xsFilename   = input_setup.attribute("xsfile").value();
  meshFilename = input_setup.attribute("meshfile").value();
  nGroups      = input_setup.attribute("ngroups").as_int();
  nHist        = input_setup.attribute("nhistories").as_int();
  loud         = input_setup.attribute("loud").as_bool();

  // get outfile parameters
  pugi::xml_node input_outfiles = input_file.child("outfiles");
  outFilename  = input_outfiles.attribute("outfile").value();
  vtkFilename  = input_outfiles.attribute("vtkfile").value();
  timeFilename = input_outfiles.attribute("timefile").value();

  // set and lock constants
  constants = std::make_shared< Constants > ();
  constants->setNumGroups( nGroups );
  constants->setNumHis( nHist );

  // initialize geometry and mesh objects
  geometry = std::make_shared< Geometry >   ();
  mesh     = std::make_shared< Mesh >       ( meshFilename, loud, constants );
  timer    = std::make_shared< HammerTime > ();

  // set outfiles
  mesh->setOutFilename( outFilename );
  mesh->setVTKFilename( vtkFilename );
  timer->setOutFilename( timeFilename );

  /* ===================================================================================================================== *
   *
   * Iterate over Nuclides
   * 
   * ===================================================================================================================== */
  
  std::vector< std::shared_ptr< Nuclide > > nuclides;
  pugi::xml_node inputNuclides = input_file.child("nuclides");
  for ( auto n : inputNuclides ) {
    std::string name = n.attribute("name").value();

    std::shared_ptr< XSection > xsec;
    std::shared_ptr< Reaction > rxn;

    std::shared_ptr< Nuclide > Nuc = std::make_shared< Nuclide > ( n.attribute("name").value() );
    nuclides.push_back( Nuc );

    // iterate over its reactions
    for ( auto r : n.children() ) 
    {
      double tempXS;
      std::string rxnType = r.name();

      if ( rxnType == "Capture" ) 
      {
        std::vector< double > captureXS;
        pugi::xml_node xs = r.child("xs");
        if ( xs )
        {
          pugi::xml_attribute xsList = xs.attribute("value");
          if ( xsList ) 
          {
            std::istringstream inString( xsList.value() );
            while ( inString >> tempXS ) { captureXS.push_back( tempXS ); }
          }
          else
          {
            std::cout << " unknown attribute type for caputre xs vector in nuclide " << name << std::endl;
            throw;
          }
          if ( captureXS.size() != nGroups )
          {
            std::cout << " the number of elements in the capture xs vector for nuclide " 
                      << name << " does not equal nGroups." << std::endl;
            throw;
          }
          xsec  = std::make_shared< CaptureXS > ( captureXS );
          rxn   = std::make_shared< Capture >   ( xsec );
          xsec->setRxn( rxn );

          Nuc->addXSection( xsec );
          captureXS.clear();
        }
        else
        {
          std::cout << " unknown xs vector type for capture reaction in nuclide " << name << std::endl;
          throw;
        }
      }
      else if ( rxnType == "Scatter" ) 
      {
        std::vector< double > tempXSVec;
        std::vector< std::vector< double > > scatterXS;

        for ( pugi::xml_node groupXS : r.children() )
        {
          std::string dataType = groupXS.name();
          if ( dataType == "xs" )
          {
            pugi::xml_attribute xsList = groupXS.attribute("value");
            if ( xsList )
            {
              std::istringstream inString( xsList.value() );
              while ( inString >> tempXS ) { tempXSVec.push_back( tempXS ); }
            }
            else
            {
              std::cout << " unknown attribute type for scatter xs vector in nuclide " << name << std::endl;
              throw;
            }
            if ( tempXSVec.size() != nGroups )
            {
              std::cout << " the number of elements in the capture xs vector for nuclide " 
                        << name << " does not equal nGroups." << std::endl;
              throw;
            }
            scatterXS.push_back( tempXSVec );
            tempXSVec.clear();
          }
          else
          {
            std::cout << " unknown xs vector type for scatter reaction in nuclide " << name << std::endl;
            throw;
          }
        }
        if ( scatterXS.size() != nGroups )
        {
          std::cout << " the number of elements in the scatter xs vector for nuclide " 
                    << name << " does not equal nGroups." << std::endl;
          throw;
        }
        xsec  = std::make_shared< ScatterXS > ( scatterXS );
        rxn   = std::make_shared< Scatter >   ( xsec );
        xsec->setRxn( rxn );

        Nuc->addXSection( xsec );

        scatterXS.clear();
      }
      else if ( rxnType == "Fission" ) 
      {
        std::vector< double > fissionXS, nuXS, chiXS;
        for ( pugi::xml_node xs: r.children() )
        {
          std::string name = xs.name();
          if ( name == "xs" )
          {
            pugi::xml_attribute xsList = xs.attribute("value");
            if ( xsList ) 
            {
              std::istringstream inString( xsList.value() );
              while ( inString >> tempXS ) { fissionXS.push_back( tempXS ); }
            }
            else
            {
              std::cout << " unknown attribute type for caputre xs vector in nuclide " << name << std::endl;
              throw;
            }
            if ( fissionXS.size() != nGroups )
            {
              std::cout << " the number of elements in the fission xs vector for nuclide " 
                        << name << " does not equal nGroups." << std::endl;
              throw;
            }
          }
          else if ( name == "nu" )
          {
            pugi::xml_attribute xsList = xs.attribute("value");
            if ( xsList ) 
            {
              std::istringstream inString( xsList.value() );
              while ( inString >> tempXS ) { nuXS.push_back( tempXS ); }
            }
            else
            {
              std::cout << " unknown attribute type for caputre xs vector in nuclide " << name << std::endl;
              throw;
            }
            if ( nuXS.size() != nGroups )
            {
              std::cout << " the number of elements in the nu vector for nuclide " 
                        << name << " does not equal nGroups." << std::endl;
              throw;
            }
          }
          else if ( name == "chi" )
          {
            pugi::xml_attribute xsList = xs.attribute("value");
            if ( xsList ) 
            {
              std::istringstream inString( xsList.value() );
              while ( inString >> tempXS ) { chiXS.push_back( tempXS ); }
            }
            else
            {
              std::cout << " unknown attribute type for caputre xs vector in nuclide " << name << std::endl;
              throw;
            }
            if ( chiXS.size() != nGroups )
            {
              std::cout << " the number of elements in the chi vector for nuclide " 
                        << name << " does not equal nGroups." << std::endl;
              throw;
            }
          }
          else
          {
            std::cout << " unknown xs vector type for fission reaction in nuclide " << name << std::endl;
            throw;
          }
        }
        if ( fissionXS.size() == nuXS.size() && nuXS.size() == chiXS.size() ) 
        {
          xsec  = std::make_shared< FissionXS > ( fissionXS, nuXS, chiXS );
          rxn   = std::make_shared< Fission >   ( xsec );
          xsec->setRxn( rxn );

          Nuc->addXSection( xsec );

          fissionXS.clear();
          nuXS.clear();
          chiXS.clear();
        }
        else 
        {
          std::cout << " the number of elements in the xs vectors for fission reaction in nuclide " 
                    << name << " are not equivalent" << std::endl;
          throw;
        }
      }
      else 
      {
        std::cout << "unknown reaction type " << rxnType << std::endl;
        throw;
      }
    }
  } 

  /* ===================================================================================================================== *
   *
   * Iterate over Materials
   * 
   * ===================================================================================================================== */
  
  std::vector< std::shared_ptr< Material > > materials;
  pugi::xml_node inputMaterials = input_file.child("materials");
  for ( auto m : inputMaterials ) 
  {
    std::string name = m.attribute("name").value();
    double      aden = m.attribute("density").as_double();
    
    std::shared_ptr< Material > Mat = std::make_shared< Material > ( name, aden );    
    materials.push_back( Mat );

    // iterate over nuclides
    for ( auto n : m.children() ) 
    {
      if ( (std::string) n.name() == "nuclide" ) 
      {
        std::string nuclideName = n.attribute("name").value();
        double      frac         = n.attribute("frac").as_double();
        
        Mat->addNuclide( findByName( nuclides, nuclideName ), frac );
      }
    }
  }

  /* ===================================================================================================================== *
   *
   * Iterate over surfaces
   * 
   * ===================================================================================================================== */
  
  pugi::xml_node input_surfaces = input_file.child("surfaces");
  for ( auto s : input_surfaces ) {
    std::string type = s.name();
    std::string name = s.attribute("name").value();

    std::shared_ptr< surface > S;
    if ( type == "plane" ) {
      double a = s.attribute("a").as_double();
      double b = s.attribute("b").as_double();
      double c = s.attribute("c").as_double();
      double d = s.attribute("d").as_double();
      S = std::make_shared< plane > ( name, a, b, c, d );
    }
    else if ( type == "sphere" ) {
      double x0  = s.attribute("x0").as_double();
      double y0  = s.attribute("y0").as_double();
      double z0  = s.attribute("z0").as_double();
      double rad = s.attribute("rad").as_double();
      S = std::make_shared< sphere > ( name, x0, y0, z0, rad );
    }
    else {
      std::cout << " unkown surface type " << type << std::endl;
      throw;
    }

    geometry->addSurface( S );

  }

  /* ===================================================================================================================== *
   *
   * Iterate over cells
   * 
   * ===================================================================================================================== */
  
  pugi::xml_node input_cells = input_file.child("cells");
  for ( auto c : input_cells ) {
    std::string name = c.attribute("name").value();

    std::shared_ptr< Cell > Cel = std::make_shared< Cell > ( name );

    // cell material
    if ( c.attribute("material") ) {
      std::shared_ptr< Material > matPtr = findByName( materials, c.attribute("material").value() );
      if ( matPtr ) {
        Cel->setMaterial( matPtr );
      }
      else {
        std::cout << " unknown material " << c.attribute("material").value() << " in cell " << name << std::endl;
        throw;
      } 
    }
   
    // iterate over surfaces
    for ( auto s : c.children() ) {
      if ( (std::string) s.name() == "surface" ) {
        std::string name  = s.attribute("name").value();
        int      intSense = s.attribute("sense").as_int();
        bool     boolSense;
        if (intSense == +1) {
          boolSense = false;
        }
        else if (intSense == -1) {
          boolSense = true;
        }
        else {
          std::cout << " unknown sense value " << intSense << " for surface " << s.attribute("name").value() << std::endl;
          throw;
        }

        std::shared_ptr< surface > SurfPtr = findByName( geometry->getSurfaces(), name );

        if ( SurfPtr ) {
          std::pair< std::shared_ptr< surface >, bool > surfPair = std::make_pair( SurfPtr, boolSense );
          Cel->addSurfacePair( surfPair );
        }
        else {
          std::cout << " unknown surface with name " << name << std::endl;
          throw;
        }
      }
      else {
        std::cout << " unknown data type " << s.name() << " in cell " << name << std::endl;
        throw;
      }
    }
    geometry->addCell( Cel );
  }

  /* ===================================================================================================================== *
   *
   * Iterate over estimators
   * 
   * ===================================================================================================================== */

  pugi::xml_node input_estimators = input_file.child("estimators");
  for ( auto e : input_estimators ) {
    std::string type      = e.name();
    std::string name      = e.attribute("name").value();
    std::string apply     = e.attribute("apply").value();
    std::string applyName = e.attribute("applyName").value();
    
  
    // TODO parse particle attribute binning
    // TODO write an input function that generates a map if attribute name strings to binning structures
    // and throws an exception if a name is not recognized or the binning structue format is wrong
    
    // Initialize a shared pointer to the correct ParticleAttributeBinningStructure given the input
    // all EstimatorCollections specified together share a single ParticleAttributeBinningStructure
    // so that if adaptive binning is implemented it will apply uniformly over all EstimatorCollections
    // for now default to GroupBinningStructure
    Bin_ptr binning = std::make_shared<GroupBinningStructure>(nGroups);
    
    // initialize attribute map 
    std::map< string , Bin_ptr> attributeMap;
    // For now just make one with the group binning as the only attribute
    attributeMap["Group"] = binning;

      
    if ( type == "CollisionTally" ) {
      // make sure all attributes in the attribute map are consistent with a CollisionTally
      // by creating a dummy collision tally and doing an attribute check
      //CollisionEstimatorCollection col(attributeMap);
      //col.checkAttributeNames();

      if ( apply == "cell" ) {
        // special case "all_cells"
        if ( applyName == "all_cells" ) {
          for ( auto cel : geometry->getCells() ) {
            // make a CollisionEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceFluence);
            cel->addEstimator(est);
          }
        }
        else {
          std::shared_ptr< Cell > cel = findByName( geometry->getCells() , applyName );

          if ( cel ) {
            // make a CollisionEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceFluence );
            cel->addEstimator(est);
          }
          else {
            std::cout << " unknown cell with name " << applyName << " for estimator " << name << std::endl;
            throw;
          }
        }
      }
      else if ( apply == "tet" ) {
        // special case "all_tets"
        if ( applyName == "all_tets" ) {
          constants->setAllTets();
          if (constants->getAllTets()) {
            std::cout << "Success!" << std::endl;
          }
          for ( auto t : mesh->getTets() ) {
            // make a CollisionEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceFluence );
            t->addEstimator(est);
          }
        }
        else {
          std::shared_ptr< Tet > tet = findByName( mesh->getTets(), applyName );

          if ( tet ) {
            // make a CollisionEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::Collision );
            tet->addEstimator(est);
          }
          else {
            std::cout << " unknown tet with name " << applyName << " for estimator " << name << std::endl;
            throw;
          }
        }
      }
      else {
        std::cout << " unknown apply type with name " << apply << " for estimator " << name << std::endl;
        throw;
      }
    }
    else if ( type == "SurfaceFluenceTally" ) {
      // make sure all attributes in the attribute map are consistent with a SurfaceTally
      // by creating a dummy surface tally and doing an attribute check
      //SurfaceFluenceEstimatorCollection surf(attributeMap);
      //surf.checkAttributeNames();

      if ( apply == "surface" ) {
        // special case "all_cells"
        if ( applyName == "all_surfaces" ) {
          for ( auto surf : geometry->getSurfaces() ) {
            // make a SurfaceEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceFluence);
            surf->addEstimator(est);
          }
        }
        else {
          std::shared_ptr< surface > surf = findByName( geometry->getSurfaces() , applyName );

          if ( surf ) {
            // make a SurfaceEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceFluence );
            surf->addEstimator(est);
          }
          else {
            std::cout << " unknown surface with name " << applyName << " for estimator " << name << std::endl;
            throw;
          }
        }
      }
      else {
        std::cout << " unknown apply type with name " << apply << " for estimator " << name << std::endl;
        throw;
      }
    }
    else if ( type == "SurfaceCurrentTally" ) {
      // make sure all attributes in the attribute map are consistent with a SurfaceTally
      // by creating a dummy surface tally and doing an attribute check
      // SurfaceCurrentEstimatorCollection surf(attributeMap);
      // surf.checkAttributeNames();

      if ( apply == "surface" ) {
        // special case "all_cells"
        if ( applyName == "all_surfaces" ) {
          for ( auto surf : geometry->getSurfaces() ) {
            // make a SurfaceEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceCurrent );
            surf->addEstimator(est);
          }
        }
        else {
          std::shared_ptr< surface > surf = findByName( geometry->getSurfaces() , applyName );

          if ( surf ) {
            // make a SurfaceEstimatorCollection shared ptr and cast it as an EstimatorCollection shared ptr 
            // use the attributeMap for this estimator as the constructor
            EstCollection_ptr est = std::make_shared<EstimatorCollection>( attributeMap , EstimatorCollection::EstimatorType::SurfaceCurrent );
            surf->addEstimator(est);
          }
          else {
            std::cout << " unknown surface with name " << applyName << " for estimator " << name << std::endl;
            throw;
          }
        }
      }
      else {
        std::cout << " unknown apply type with name " << apply << " for estimator " << name << std::endl;
        throw;
      }
    }
    else {
      std::cout << " unknown estimator type with name " << type << std::endl;
      throw;
    }
  

  }
 
  /* ===================================================================================================================== *
   *
   * Iterate over Sources
   * 
   * ===================================================================================================================== */
  
  pugi::xml_node input_sources = input_file.child("sources");
  for ( auto so : input_sources ) {
    std::string type  = so.name();
    std::string name  = so.attribute("name").value();

    std::shared_ptr< Source > sourc;

    if ( type == "setSourceSphere" ) {
      double x0   = so.attribute("xSource").as_double();
      double y0   = so.attribute("ySource").as_double();
      double z0   = so.attribute("zSource").as_double();
      double radi = so.attribute("radInner").as_double();
      double rado = so.attribute("radOuter").as_double();
      std::string dist = so.attribute("distribution").value();

      if ( dist == "hardcoded" ) {
        // all neutrons come from the first group
        std::vector< double > sourceGroups;
        sourceGroups.push_back( 1.0 );
        for ( int i=1; i<nGroups; i++ ) {
          sourceGroups.push_back( 0.0 );
        }
        sourc = std::make_shared< setSourceSphere > ( name, x0, y0, z0, radi, rado, sourceGroups );
      }
      else {
        std::cout << " unknown distribution type with name " << dist << std::endl;
        throw;
      }
    }
    else if ( type == "setSourcePoint" ) {
      double x0   = so.attribute("xSource").as_double();
      double y0   = so.attribute("ySource").as_double();
      double z0   = so.attribute("zSource").as_double();
      std::string dist = so.attribute("distribution").value();

      if ( dist == "hardcoded" ) {
        // all neutrons come from the first group
        std::vector< double > sourceGroups;
        sourceGroups.push_back( 1.0 );
        for ( int i=1; i<nGroups; i++ ) {
          sourceGroups.push_back( 0.0 );
        }
        sourc = std::make_shared< setSourcePoint > ( name, x0, y0, z0, sourceGroups );
      }
      else {
        std::cout << " unknown distribution type with name " << dist << std::endl;
        throw;
      }
    }
    else {
      std::cout << " unnknown source type with name " << type << std::endl;
      throw;
    }
    geometry->setSource( sourc );
  }
  constants->lock(); // Please don't move this
}
