//
//  mesh.cpp
//  Reader
//
//  Created by Rob Fonti on 1/18/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include <stdio.h>
#include "mesh.h"


mesh::mesh()
{
  
}

void mesh:: addTet(std::pair<int,std::shared_ptr<Tet>> inTet)
{
  tetVector.push_back(inTet);
}

void mesh:: addVertice(std::pair<int,std::shared_ptr<point>> inVertice)
{
  verticesVector.push_back(inVertice);
}

int mesh:: getTetID(std::pair<int,std::shared_ptr<Tet>> inTet)
{
  return inTet.second->getID();
}

std::vector < std::pair<int,std::shared_ptr<point>> > mesh:: getVerticesVector()
{
  return verticesVector;
}

int mesh:: getNumVertices()
{
  return numVertices;
}

int mesh:: getNumTets()
{
  return numTets;
}

void mesh:: setNumTets(int inNumber)
{
  numTets = inNumber;
}

void mesh:: setNumVertices(int inNumber)
{
  numVertices = inNumber;
}

void mesh::printTets()
{
  std::cout<<"Printing Tets..."<<std::endl;
  for(int i = 0; i<numTets; i++)
  {
    std::cout<<"Tet Number "<<i+1<<":"<<std::endl;
    std::cout<<"Vertex 1: "<<tetVector[i].second->getVert1().x<<" "
    <<tetVector[i].second->getVert1().y<<" "<<tetVector[i].second->getVert1().z<<std::endl;
    std::cout<<"Vertex 2: "<<tetVector[i].second->getVert2().x<<" "
    <<tetVector[i].second->getVert2().y<<" "<<tetVector[i].second->getVert2().z<<std::endl;
    std::cout<<"Vertex 3: "<<tetVector[i].second->getVert3().x<<" "
    <<tetVector[i].second->getVert3().y<<" "<<tetVector[i].second->getVert3().z<<std::endl;
    std::cout<<"Vertex 4: "<<tetVector[i].second->getVert4().x<<" "
    <<tetVector[i].second->getVert4().y<<" "<<tetVector[i].second->getVert4().z<<std::endl;
  }
}

void mesh:: printVertices()
{
  std::cout<<"Printing Vertices..."<<std::endl;
  for(int i = 0; i<numVertices; i++)
  {
    std::cout<<"Vertice "<<verticesVector[i].first<<" = "<<verticesVector[i].second->x
    <<" "<<verticesVector[i].second->y<<" "<<verticesVector[i].second->z<<std::endl;
  }
}


