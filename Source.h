#include <tuple>
#include <vector>
#include <memory>

#ifndef _SOURCE_HEADER_
#define _SOURCE_HEADER_

class Source {
public:
	std::shared_ptr<std::vector<std::tuple <double, double, double, double, double, double> > > pstack; 
  	//Tuple includes x,y,z,mu,phi,energy

	std::vector<std::tuple <double, double, double, double, double, double> > source();
};

#endif
