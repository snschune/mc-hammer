//
//  mesh.cpp
//  Reader
//
//  Created by Rob Fonti on 1/18/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh( std::string fileName, bool loud , Constants constantsin): constants(constantsin)
{
    readFile( fileName, loud );
}

void Mesh::readFile( std::string fileName, bool loud )
{
    std::string meshDirectory = "MeshFiles/";
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
        
        Mesh::setNumVertices(numVertices);
        Mesh::setNumTets(numTets);
        
        
        Point_ptr tempPtr = std::make_shared<point>(point(xValue,yValue,zValue));
        
        std::pair<int,Point_ptr> vertice;
        vertice = std::make_pair(idNumber,tempPtr);
        
        verticesVector.push_back(vertice);
        Mesh::addVertice(vertice);
        
    }
    
    int j = 268;
    
    for(j = 268; j < 1575; j++)
    {
        //used to skip lines that we dont care about
        int wasteVariable1;
        int wasteVariable2;
        int wasteVariable3;
        inFile>>wasteVariable1>>wasteVariable2>>wasteVariable3;
    }
    
    
    std::vector<Tet> tetVector;  //just used for test case, can comment out or delete if desired
    
    int k = 1575;
    
    //the indices temp1,2,3,4 correspond to elements of the vertices vector
    // initialize tets and push them into the mesh
    for (k = 0; k < 2881-1574; k++)
    {
        int tetIndex;
        int temp1,temp2,temp3,temp4;
        inFile>>tetIndex;
        inFile>>temp1>>temp2>>temp3>>temp4;
        
        
        std::pair<int,Tet_ptr> tetToAdd;
        
        
        point p(0,0,0);  //our zero point for initalization

        // create a vector of estimators and fill it with collision tallies
        vector <Estimator_ptr> estimators;
        for(int i = 0; i < constants.getNumGroups(); ++i) {
		   estimators.push_back( std::make_shared< CollisionTally >(constants.getNumHis()) );  
        }
        
        Tet newTet(p , estimators);
        newTet.setVertices(verticesVector[temp1-1].second,verticesVector[temp2-1].second,
                           verticesVector[temp3-1].second,verticesVector[temp4-1].second);
        newTet.setID( tetIndex );
        
        Tet_ptr tempTet = std::make_shared<Tet>(newTet);
        
        tetToAdd = std::make_pair(tetIndex,tempTet);
        
        
        Mesh::addTet(tetToAdd);
        tetVector.push_back(newTet);
    }
    
    if ( loud ) { // provide extra information if "loud" is true
        std::cout << "\n\tMesh read in successfully.\n" << std::endl;
    }
    
    inFile.close();
}

void Mesh::addTet(std::pair<int,Tet_ptr> inTet)
{
    tetVector.push_back(inTet);
}

void Mesh::addVertice(std::pair<int,Point_ptr> inVertice)
{
    verticesVector.push_back(inVertice);
}

int Mesh::getTetID(std::pair<int,Tet_ptr> inTet)
{
    return inTet.second->getID();
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
        std::cout<<"Vertex 1: "<<tetVector[i].second->getVert1()[0]<<" "
        <<tetVector[i].second->getVert1()[1]<<" "<<tetVector[i].second->getVert1()[2]<<std::endl;
        std::cout<<"Vertex 2: "<<tetVector[i].second->getVert2()[0]<<" "
        <<tetVector[i].second->getVert2()[1]<<" "<<tetVector[i].second->getVert2()[2]<<std::endl;
        std::cout<<"Vertex 3: "<<tetVector[i].second->getVert3()[0]<<" "
        <<tetVector[i].second->getVert3()[1]<<" "<<tetVector[i].second->getVert3()[2]<<std::endl;
        std::cout<<"Vertex 4: "<<tetVector[i].second->getVert4()[0]<<" "
        <<tetVector[i].second->getVert4()[1]<<" "<<tetVector[i].second->getVert4()[2]<<std::endl;
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
        if ( tet.second->amIHere( testPoint ) == true )
        {
            hereIAm = tet.second;
        }
    }

    if ( hereIAm == nullptr )
    {
        std::cout << "ERROR: Couldn't locate Tet." << std::endl;
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
    }
    else {
        std::cerr << "Particle could not be located in the Mesh, failed to score tally " << std::endl;
    }
}

void Mesh::endTallyHist() {
    for(auto tet : tetVector) {
        tet.second->endTallyHist();
    }
}

void Mesh::printMeshTallies(std::string fname) {
    std::cout << "Printing mesh tallies to " << fname << " ..." << std::endl;

    std::ofstream meshTallyStream;
    meshTallyStream.open(fname);

    meshTallyStream << "Mesh tally output" << std::endl;

    for(auto tet : tetVector) {
        meshTallyStream << tet.first;
        for (auto tally : tet.second->getTally() ) {
            meshTallyStream << "   " << tally.first;
        }
        meshTallyStream << std::endl;
    }
}


