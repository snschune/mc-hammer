//
//  mesh.cpp
//  Reader
//
//  Created by Rob Fonti on 1/18/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh( std::string fileName, bool loud , Constants_ptr constantsin ): constants(constantsin)
{
    readFile( fileName, loud );
    histCounter = 0;
}

void Mesh::readFile( std::string fileName, bool loud )
{
    std::string meshDirectory = "meshfiles/";
    std::ifstream inFile;
    inFile.open(meshDirectory+fileName);
    
    if ( inFile.fail() ){ // make sure file opens
        std::cerr << "Error! Mesh file could not be opened." << std::endl;
        exit(1);
    }
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "Reading Mesh file..." << std::endl;
    }
    
    std::vector< std::pair<int,Point_ptr> > verticesVector;
    
    int numVertices,numTets,c,d;
    
    inFile>>numVertices>>numTets>>c>>d;
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "\tFilename: " << fileName << std::endl;
        std::cout << "\tNumber of vertices: " << numVertices << std::endl;
        std::cout << "\tNumber of tets: " << numTets << std::endl;
    }
    
    for(int i = 0; i<numVertices; i++)
    {
        int idNumber;
        double xValue;
        double yValue;
        double zValue;
        
        
        inFile>>idNumber;
        inFile>>xValue>>yValue>>zValue;
        
        setNumVertices(numVertices);
        setNumTets(numTets);
        
        
        Point_ptr tempPtr = std::make_shared<point>(point(xValue-101.6,yValue-101.6,zValue-101.6));
        
        std::pair<int,Point_ptr> vertice;
        vertice = std::make_pair(idNumber,tempPtr);
        
        verticesVector.push_back(vertice);
        Mesh::addVertice(vertice);
        
    }
    
    for(int j = 0; j < numTets; j++)
    {
        //used to skip lines that we dont care about
        int wasteVariable1;
        int wasteVariable2;
        int wasteVariable3;
        inFile>>wasteVariable1>>wasteVariable2>>wasteVariable3;
    }
    
    
    std::vector<Tet> tetVector;  //just used for test case, can comment out or delete if desired
    
    //the indices temp1,2,3,4 correspond to elements of the vertices vector
    // initialize tets and push them into the mesh
    for (int k = 0; k < numTets; k++)
    {
        int tetIndex;
        int temp1,temp2,temp3,temp4;
        inFile>>tetIndex;
        inFile>>temp1>>temp2>>temp3>>temp4;
        
        // need this for VTK output
        connectivity.push_back(static_cast<double>(temp1-1));
        connectivity.push_back(static_cast<double>(temp2-1));
        connectivity.push_back(static_cast<double>(temp3-1));
        connectivity.push_back(static_cast<double>(temp4-1));
        
        Tet_ptr tetToAdd;
        
        
        point p(0,0,0);  //our zero point for initalization
        std::string tetName = "tet" + std::to_string( tetIndex );

        Tet newTet( tetName, p );

        // create a vector of estimators and fill it with collision tallies
        vector <Estimator_ptr> estimators;

        /*
        for(int i = 0; i < constants->getNumGroups(); ++i) {
            Estimator_ptr newTally = std::make_shared< CollisionTally > ( "tallyname" );
            newTet.addEstimator( newTally );  
        }
        */

        newTet.setVertices(verticesVector[temp1-1].second,verticesVector[temp2-1].second,
                           verticesVector[temp3-1].second,verticesVector[temp4-1].second);
        newTet.setID( tetIndex );
        
        Tet_ptr tempTet = std::make_shared<Tet>(newTet);
        
        
        addTet(tempTet);
        tetVector.push_back(newTet);
        tetHist.push_back(nullptr);
    }
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "\n\tMesh read in successfully.\n" << std::endl;
    }
    
    inFile.close();
}

void Mesh::addTet(Tet_ptr inTet)
{
    tetVector.push_back(inTet);
}

void Mesh::addVertice(std::pair<int,Point_ptr> inVertice)
{
    verticesVector.push_back(inVertice);
}

int Mesh::getTetID(Tet_ptr inTet)
{
    return inTet->getID();
}

std::vector < std::pair<int,Point_ptr> > Mesh::getVerticesVector()
{
    return verticesVector;
}

int Mesh::getNumVertices()
{
    return numVertices;
}

int Mesh::getNumTets()
{
    return numTets;
}

void Mesh::setNumTets(int inNumber)
{
    numTets = inNumber;
}

void Mesh::setNumVertices(int inNumber)
{
    numVertices = inNumber;
}

void Mesh::printTets()
{
    std::cout<<"Printing Tets..."<<std::endl;
    for(int i = 0; i<numTets; i++)
    {
        std::cout<<"Tet Number "<<i+1<<":"<<std::endl;
        std::cout<<"Vertex 1: "<<tetVector[i]->getVert1()[0]<<" "
        <<tetVector[i]->getVert1()[1]<<" "<<tetVector[i]->getVert1()[2]<<std::endl;
        std::cout<<"Vertex 2: "<<tetVector[i]->getVert2()[0]<<" "
        <<tetVector[i]->getVert2()[1]<<" "<<tetVector[i]->getVert2()[2]<<std::endl;
        std::cout<<"Vertex 3: "<<tetVector[i]->getVert3()[0]<<" "
        <<tetVector[i]->getVert3()[1]<<" "<<tetVector[i]->getVert3()[2]<<std::endl;
        std::cout<<"Vertex 4: "<<tetVector[i]->getVert4()[0]<<" "
        <<tetVector[i]->getVert4()[1]<<" "<<tetVector[i]->getVert4()[2]<<std::endl;
    }
}

void Mesh::printVertices()
{
    std::cout<<"Printing Vertices..."<<std::endl;
    for(int i = 0; i<numVertices; i++)
    {
        std::cout<<"Vertice "<<verticesVector[i].first<<" = "<<verticesVector[i].second->x
        <<" "<<verticesVector[i].second->y<<" "<<verticesVector[i].second->z<<std::endl;
    }
}

Tet_ptr Mesh::whereAmI( point pos )
{
    Tet_ptr hereIAm = nullptr;

    std::vector< double > testPoint = pointFourVec( pos );
    
    for( auto tet : tetVector )
    {
        if ( tet->amIHere( testPoint ) == true )
        {
            return tet;
        }
    }

    if ( hereIAm == nullptr )
    {
       // std::cout << "ERROR: Couldn't locate Tet." << std::endl;
    }
    return hereIAm;
}

void Mesh::scoreTally(Part_ptr p, double xs) {
    //what tet in the mesh did the particle collide in?
    Tet_ptr t = whereAmI( p->getPos() );
    
    // make sure its a valid mesh element
    if(t != nullptr) {
        //score the tally in that tet
        t->scoreTally(p , xs);
        for(int i = 0; i < histCounter; i++)
        {
            if(t == tetHist[i])
            {
                return;
            }
        }
        tetHist[histCounter] = t;
        histCounter++;
    }
    else {
        std::cerr << "Particle could not be located in the Mesh, failed to score tally " << std::endl;
    }
}

void Mesh::endTallyHist() {
    for(int i = 0; i < histCounter; i++)
    {
        tetHist[i]->endTallyHist();
        tetHist[i] = nullptr;
    }
    histCounter = 0;
}

void Mesh::printMeshTallies() {
    std::cout << "Printing mesh tallies to " << "outfiles/" << outFilename << "..." << std::endl;

    std::ofstream meshTallyStream;
    meshTallyStream.open( "outfiles/" + outFilename );

    meshTallyStream << "Mesh tally output" << std::endl;

    for(auto tet : tetVector) {
        meshTallyStream << tet->getID();
        for (auto tally : tet->getTally(constants->getNumHis()) ) {
            meshTallyStream << "   " << tally.first;
        }
        meshTallyStream << std::endl;
    }
    meshTallyStream.close();
}

void Mesh::writeToVTK() {


    std::cout << "Writing mesh tallies to " << "outfiles/" << vtkFilename << "..." << std::endl;

    std::ofstream vtkStream;
    vtkStream.open( "outfiles/" + vtkFilename );

    // Specify file type
    XMLTag vtkfile( 0, "VTKFile" );
    vtkfile.addAttribute( "type", "UnstructuredGrid" );
    vtkfile.addAttribute( "version", "0.1" );
    vtkfile.addAttribute( "byte_order", "LittleEndian" );
    vtkfile.addAttribute( "compressor", "vtkZLibDataCompressor");

    // Specify grid type
    XMLTag unstGrid( 1, "UnstructuredGrid");

    // Piece (has information for points and cells)
    XMLTag piece( 2, "Piece" );
    piece.addAttribute( "NumberOfPoints", std::to_string(numVertices) );
    piece.addAttribute( "NumberOfCells", std::to_string(numTets) );

    // Point Data (not currently using)
    XMLTag pointData1( 3, "PointData" );

    // CellData (xml calls them 'cells', hammer calls them 'tets')
    // Need to find a way to loop through a tet's estimators
    XMLTag cellData( 3, "CellData" );
    cellData.addAttribute( "Scalars", "mesh_tallies");

    for ( auto tally : tetVector[0]->getTally(constants->getNumHis()) ) {
           std::vector<double> tempVec;
           cellDataVec.push_back(tempVec);
        }

    for ( auto tet : tetVector ) {
        int i = 0;
        for (auto tally : tet->getTally(constants->getNumHis()) ) {
            if ( i == constants->getNumGroups() ) {
                i = 0;
            }
            cellDataVec[i].push_back(tally.first);
            i++;
        }
    }

    std::vector< std::shared_ptr< XMLTag > > tallyTags;
    int i = 0;
    double tallyMin, tallyMax;
    for ( auto dataVec : cellDataVec ) {

        //std::string tallyName = tetVector[0]->getEstimators()[i]->name();
        //TODO fix this
        std::string tallyName = "";
        XMLTag tallyTag( 4, "DataArray" );
        tallyTag.addAttribute( "type", "Float64");
        tallyTag.addAttribute( "Name", tallyName );
        tallyTag.addAttribute( "format", "ascii" );
        tallyMin = vecMin(dataVec);
        tallyMax = vecMax(dataVec);
        // the string stream is the only way I was able to retain precision
        std::ostringstream maxStream, minStream;
        maxStream << tallyMax;
        minStream << tallyMin;
        std::string maxString = maxStream.str();
        std::string minString = minStream.str();
        tallyTag.addAttribute( "RangeMin", minString );
        tallyTag.addAttribute( "RangeMax", maxString );
        tallyTag.addDataArray( dataVec );
        std::shared_ptr< XMLTag > Tag_ptr = std::make_shared< XMLTag >( tallyTag );

        tallyTags.push_back( Tag_ptr );

        i++;
    }

    // Points and data array
    XMLTag points( 3, "Points" );
    XMLTag pointsData( 4, "DataArray" );
    pointsData.addAttribute( "type", "Float64" );
    pointsData.addAttribute( "Name", "Points" );
    pointsData.addAttribute( "NumberOfComponents", "3" );
    pointsData.addAttribute( "format", "ascii" );

    // Find the max/min value vertex in the mesh
    double maxCoor = verticesVector[0].second->x;
    double minCoor = verticesVector[0].second->x;

    std::vector< double > vtkPointVec;

    for ( auto vert : verticesVector ) {
        // Find max
        if ( (vert.second->x) > maxCoor ) { maxCoor = vert.second->x; }
        if ( (vert.second->y) > maxCoor ) { maxCoor = vert.second->y; }
        if ( (vert.second->y) > maxCoor ) { maxCoor = vert.second->y; }
        // Find min
        if ( (vert.second->x) < minCoor ) { minCoor = vert.second->x; }
        if ( (vert.second->y) < minCoor ) { minCoor = vert.second->y; }
        if ( (vert.second->y) < minCoor ) { minCoor = vert.second->y; }

        vtkPointVec.push_back(vert.second->x);
        vtkPointVec.push_back(vert.second->y);
        vtkPointVec.push_back(vert.second->z);
    }

    // the string stream is the only way I was able to retain precision
    std::ostringstream maxCoorStream, minCoorStream;
    maxCoorStream << maxCoor;
    minCoorStream << minCoor;
    std::string maxCoorString = maxCoorStream.str();
    std::string minCoorString = minCoorStream.str();

    pointsData.addAttribute( "RangeMin", minCoorString );
    pointsData.addAttribute( "RangeMax", maxCoorString );
    pointsData.addDataArray( vtkPointVec );

    // Cells and data arrays
    XMLTag cells( 3, "Cells" );
    XMLTag cellsData1( 4, "DataArray" ); // tells vtk which points are associated with each tet
    XMLTag cellsData2( 4, "DataArray" ); // tells vtk how to segment the the tet associations
    XMLTag cellsData3( 4, "DataArray" ); // tells vtk which type of cell to build

    cellsData1.addAttribute( "type", "Int64" );
    cellsData1.addAttribute( "Name", "connectivity" );
    cellsData1.addAttribute( "format", "ascii" );
    cellsData1.addAttribute( "RangeMin", "0" );
    cellsData1.addAttribute( "RangeMax", std::to_string(numVertices-1) );
    cellsData1.addDataArray( connectivity );

    cellsData2.addAttribute( "type", "Int64" );
    cellsData2.addAttribute( "Name", "offsets" );
    cellsData2.addAttribute( "format", "ascii" );
    cellsData2.addAttribute( "RangeMin", "4" ); // 4 corresponds to number of verts in tet
    cellsData2.addAttribute( "RangeMax", std::to_string(4*numTets) );

    std::vector< double > offsets;
    for ( int i = 0; i<numTets; i++ ) {
        offsets.push_back( 4.0*(i+1) );
    }

    cellsData2.addDataArray( offsets );

    cellsData3.addAttribute( "type", "UInt8" );
    cellsData3.addAttribute( "Name", "types" );
    cellsData3.addAttribute( "format", "ascii" );
    cellsData3.addAttribute( "RangeMin", "10" ); // 10 corresponds to vtk cell type (tetrahedron)
    cellsData3.addAttribute( "RangeMax", "10" ); // 10 corresponds to vtk cell type (tetrahedron)

    std::vector< double > vtkCellType;
    for ( int i = 0; i<numTets; i++) {
        vtkCellType.push_back( 10 );
    }

    cellsData3.addDataArray( vtkCellType );

    // Write all XMLTags and Data Arrays to file
    vtkStream << "<?xml version=\"1.0\"?>" << std::endl;
    vtkStream << vtkfile.getTagOpen() << std::endl;
    vtkStream << unstGrid.getTagOpen() << std::endl;
    vtkStream << piece.getTagOpen() << std::endl;
    vtkStream << pointData1.getTagOpen() << std::endl;
    vtkStream << pointData1.getTagClose() << std::endl;
    vtkStream << cellData.getTagOpen() << std::endl;
    // loop over the estimator tallies and write to file
    for ( auto tag : tallyTags ) {
        vtkStream << tag->getTagOpen() << std::endl;
        tag->arrayToFile( vtkStream, 24, false );
        vtkStream << tag->getTagClose() << std::endl;
    }
    vtkStream << cellData.getTagClose() << std::endl;
    vtkStream << points.getTagOpen() << std::endl;
    vtkStream << pointsData.getTagOpen() << std::endl;
    pointsData.arrayToFile( vtkStream, 12, false );
    vtkStream << pointsData.getTagClose() << std::endl;
    vtkStream << points.getTagClose() << std::endl;
    vtkStream << cells.getTagOpen() << std::endl;
    vtkStream << cellsData1.getTagOpen() << std::endl;
    cellsData1.arrayToFile( vtkStream, 24, true );
    vtkStream << cellsData1.getTagClose() << std::endl;
    vtkStream << cellsData2.getTagOpen() << std::endl;
    cellsData2.arrayToFile( vtkStream, 16, true );
    vtkStream << cellsData2.getTagClose() << std::endl;
    vtkStream << cellsData3.getTagOpen() << std::endl;
    cellsData3.arrayToFile( vtkStream, 32, true );
    vtkStream << cellsData3.getTagClose() << std::endl;
    vtkStream << cells.getTagClose() << std::endl;
    vtkStream << piece.getTagClose() << std::endl;
    vtkStream << unstGrid.getTagClose() << std::endl;
    vtkStream << vtkfile.getTagClose() << std::endl;

    vtkStream.close();
}
