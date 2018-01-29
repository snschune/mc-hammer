//
//  mesh.cpp
//  Reader
//
//  Created by Rob Fonti on 1/18/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include "Mesh.h"


Mesh::Mesh()
{
    
}

void Mesh:: addTet(std::pair<int,std::shared_ptr<Tet>> inTet)
{
    tetVector.push_back(inTet);
}

void Mesh:: addVertice(std::pair<int,std::shared_ptr<point>> inVertice)
{
    verticesVector.push_back(inVertice);
}

int Mesh:: getTetID(std::pair<int,std::shared_ptr<Tet>> inTet)
{
    return inTet.second->getID();
}

std::vector < std::pair<int,std::shared_ptr<point>> > Mesh:: getVerticesVector()
{
    return verticesVector;
}

int Mesh:: getNumVertices()
{
    return numVertices;
}

int Mesh:: getNumTets()
{
    return numTets;
}

void Mesh:: setNumTets(int inNumber)
{
    numTets = inNumber;
}

void Mesh:: setNumVertices(int inNumber)
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

void Mesh:: printVertices()
{
    std::cout<<"Printing Vertices..."<<std::endl;
    for(int i = 0; i<numVertices; i++)
    {
        std::cout<<"Vertice "<<verticesVector[i].first<<" = "<<verticesVector[i].second->x
        <<" "<<verticesVector[i].second->y<<" "<<verticesVector[i].second->z<<std::endl;
    }
}

void readFile(std::string fileName, Mesh &Mesh)
{
    std::ifstream inFile;
    inFile.open(fileName);
    std::vector< std::pair<int,std::shared_ptr<point>> > verticesVector;
    
    int numVertices,numTets,c,d;
    
    inFile>>numVertices>>numTets>>c>>d;
    
    for(int i = 0; i<numVertices; i++)
    {
        int idNumber;
        double xValue;
        double yValue;
        double zValue;
        
        
        inFile>>idNumber;
        inFile>>xValue>>yValue>>zValue;
        
        Mesh.setNumVertices(numVertices);
        Mesh.setNumTets(numTets);
        
        
        std::shared_ptr<point> tempPtr = std::make_shared<point>(point(xValue,yValue,zValue));
        
        std::pair<int,std::shared_ptr<point>> vertice;
        vertice = std::make_pair(idNumber,tempPtr);
        
        verticesVector.push_back(vertice);
        Mesh.addVertice(vertice);
        
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
    
    
    std:: vector<Tet> tetVector;  //just used for test case, can comment out or delete if desired
    
    int k = 1575;
    
    //the indices temp1,2,3,4 correspond to elements of the vertices vector
    
    for (k = 0; k < 2881-1574; k++)
    {
        int tetIndex;
        int temp1,temp2,temp3,temp4;
        inFile>>tetIndex;
        inFile>>temp1>>temp2>>temp3>>temp4;
        
        
        std::pair<int,std::shared_ptr<Tet>> tetToAdd;
        
        
        point p(0,0,0);  //our zero point for initalization
        
        Tet newTet(p);
        newTet.setVertices(verticesVector[temp1-1].second,verticesVector[temp2-1].second,
                           verticesVector[temp3-1].second,verticesVector[temp4-1].second);
        
        std::shared_ptr<Tet> tempTet = std::make_shared<Tet>(newTet);
        
        tetToAdd = std::make_pair(tetIndex,tempTet);
        
        
        Mesh.addTet(tetToAdd);
        tetVector.push_back(newTet);
    }
    inFile.close();
}

std::shared_ptr<Tet> Mesh::whereAmI( point pos )
{
    std::shared_ptr<Tet> hereIAm = nullptr;
    
    for( auto tet : tetVector )
    {
        if ( tet.second->amIHere( pos ) == true )
        {
            hereIAm = tet.second;
        }
    }
    return hereIAm;
}
