/*
 Author: ESGonzalez
 Date: 02/09/18
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <cassert>
#include <utility>

#include "pugixml.hpp"
#include "Material.h"
#include "Surface.h"
#include "Cell.h"
#include "Source.h"
#include "Geometry.h"
#include "Tet.h"
#include "Mesh.h"
#include "HammerTime.h"

class Input
{
private:
	std::shared_ptr< Geometry >   geometry;
	std::shared_ptr< Mesh >       mesh;
	std::shared_ptr< Constants >  constants;
	std::shared_ptr< HammerTime > timer;
	std::string                   xsFilename;
	std::string                   meshFilename;
	std::string                   outFilename;
	std::string                   vtkFilename;
	std::string                   timeFilename;
	bool                          loud;
	int                           nHist;
	int                           nGroups;

public:
	Input() {};
	~Input() {};

	void readInput( std::string xmlFilename );

	std::shared_ptr< Geometry >   getGeometry()  { return geometry;  };
	std::shared_ptr< Mesh >       getMesh()      { return mesh;      };
	std::shared_ptr< Constants >  getConstants() { return constants; };
	std::shared_ptr< HammerTime > getTimer()     { return timer;     };
};

template< typename T >
std::shared_ptr< T > findByName( std::vector< std::shared_ptr< T > > vec, std::string name ) {
  for ( auto v : vec ) {
    if ( v->name() == name ) { return v; }
  }
  return nullptr;
}


#endif