/*
 Author: ESGonzalez
 Date: 02/09/18
 */

#include "XMLTag.h"

XMLTag::XMLTag( int leveli, std::string tagNamei ) : tagName(tagNamei), level(leveli) {}

void XMLTag::addAttribute( std::string name, std::string value ) {
	std::pair< std::string, std::string > attribute;
	attribute = std::make_pair( name, value );
	attributes.push_back( attribute );
}

void XMLTag::addDataArray( std::vector< double > newDataArray ) {
	dataArray = newDataArray;
}

void XMLTag::arrayToFile( std::ofstream &outStream, int perLine, bool isInt ) {
	int i = 0;
	outStream << std::string( 2*level+2, ' ');
	for ( auto element : dataArray ) {
		if (i==perLine) {
			i = 0;
			outStream << "\n" << std::string( 2*level+2, ' ');
		}
		if (isInt) {
			element = round(element);
		}
		outStream << element << " ";
		i++;
	}
	outStream << std::endl;
}

std::string XMLTag::getTagOpen() {
	std::string tagOpen;

	tagOpen = std::string( 2*level, ' ' ) + "<" + tagName;

	for ( auto attribute : attributes ) {
		tagOpen += " " + attribute.first + "=\"" + attribute.second + "\"";
	}

	tagOpen += ">";

	return tagOpen;
}

std::string XMLTag::getTagClose() {
	std::string tagClose;

	tagClose = std::string( 2*level, ' ' ) + "</" + tagName + ">";

	return tagClose;
}