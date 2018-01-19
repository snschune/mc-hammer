//
//  ReadCoarse.cpp
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "Point.h"
#include "Tet.h"
#include "mesh.h"

//may want to add tetvector to geometry
//Define your true vectors in main...



void readFile(std::string fileName, mesh &Mesh)
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
    
      
    point p;  //our zero point for initalization
    
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



 //SAMPLE MAIN FUNCTION
 
int main()
{
  mesh Mesh;
  
  std::cout<<"Enter the name of the file you wish to read in "<<std::endl;
  std::string theName;
  std::cin>>theName;
  
  point p;
  Tet myTet(p);
  

  readFile(theName,Mesh);
  
  std::cout<<"Number of Tets = "<<Mesh.getNumTets()<<std::endl;
  std::cout<<"Number of Vertices = "<<Mesh.getNumVertices()<<std::endl;
  
  Mesh.printVertices();
  
  Mesh.printTets();
  
 
  return 0;
}
