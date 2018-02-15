/*
 Author: ESGonzalez
 Date: 02/09/18
 */

#ifndef __XMLTAG_H__
#define __XMLTAG_H__

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <math.h>

/*
XMLTag class can be used for generating and printing 
xml-style tags by naming them and adding attributes
*/

class XMLTag
{
private:
	int level; // specifies the level of indention for an xml tag
	std::string tagName; // specifies what the tag's name or type will be
	std::vector< std::pair< std::string , std::string > > attributes; // list of a tag's attirbutes
	std::vector< double > dataArray; // optional data arrays belonging to an xml tag

public:
	// constructor
	XMLTag( int level, std::string tagName );

	void addAttribute( std::string name, std::string value ); 
	void addDataArray( std::vector< double > newDataArray );
	void arrayToFile( std::ofstream &outStream, int perLine, bool isInt ); // prints a data array to file

	std::string getTagOpen(); // gets the opening tag
	std::string getTagClose(); // gets the closing tag

};


#endif