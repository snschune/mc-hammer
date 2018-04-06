/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class is for grouping tallies to get an answer as a function of particle attributes
 *  e.g. energy group, collision order, angle, type, etc.
 */

#include <cassert>
#include "EstimatorCollection.h"

/* ****************************************************************************************************** * 
 * Base Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 

EstimatorCollection::EstimatorCollection(std::map< string , Bin_ptr > attributesin): attributes(attributesin) 
{
// default constructor calculates number of estimators required
  size = 1;
  for (const auto &vals : attributes) {
    size *= vals.second->getSize();
    binSizes.push_back( vals.second->getSize() );
  }
  
  for(int i = 0; i < size; ++i) {
    Estimator tally;
    Estimator_ptr estimator = std::make_shared<Estimator>(tally);
    estimators.push_back(estimator);
  }

};
/*
bool EstimatorCollection::checkValidAttributeName( std::string name) 
{
  bool valid = false;
  for(auto attribute : validAttributes) {
    if( name == attribute) {
      valid = true;
    }
  }
  return(valid);
};  

void EstimatorCollection::checkAttributeNames() 
{
  bool valid;
  for(auto const& val : attributes) {
    valid = checkValidAttributeName( val.first );
    if( valid == false ) {
      std::cout << "Error while parsing tally attributes!" << std::endl;
      std::cout << val.first << " is not a valid attribute for a " << estimatorType << " tally!" << std::endl;
      std::cout << "It will be ignored." << std::endl;

      // remove this attribute from the attribute map
      attributes.erase(val.first);
    }

  }
};  
*/
void EstimatorCollection::endHist() {
  for(auto estimator : estimators) {
    estimator->endHist();
  }
};

int EstimatorCollection::getLinearIndex(Part_ptr p ) {
  vector<int> indices;
  for(auto const& attribute : attributes) {
    std::pair<int , bool> index = attribute.second->getIndex(p);
    if(index.second == true) {
      // if the particle attribute is within the binning range, append the index to the n-dimensional indices
      indices.push_back( index.first );
    }
    else { 
      // if one of the particle attributes is outisde the binning range, return from the function and don't score any estimators
      return(0);
    }
  }
  return( Utility::linearizeIndices( indices ,  binSizes ) );
};

void EstimatorCollection::score(Part_ptr p  , double d) {
  estimators.at( getLinearIndex(p) )->score(d);
}

/* ****************************************************************************************************** * 
 * Collision Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 


/* ****************************************************************************************************** * 
 * Surface Estimator Collection                                   
 *
 * ****************************************************************************************************** */ 


void SurfaceFluenceEstimatorCollection::scoreSurfaceFluence(Part_ptr p , point surfNormal ) {
  // score the cos of the angle bt particle direction and surface normal
  estimators.at( getLinearIndex(p) )->score( 1 / ( p->getDir() * surfNormal ) );
};
