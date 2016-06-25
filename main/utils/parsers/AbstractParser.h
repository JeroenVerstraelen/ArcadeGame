//============================================================================
// Name        : AbstractParser.h
// Author      : Quinten Soetens
// Version     :
// Description : This code is written as an example solution for the exercises given in the course
//				 Project Software Engineering for the first year bachelor students at Universiteit Antwerpen
//============================================================================

#ifndef ABSTRACTPARSER_H_
#define ABSTRACTPARSER_H_

#include <iostream>
#include "tinyxml/tinyxml.h"

using namespace std;

/*
 * This class is meant as a superclass for classes that can load parse xml files.
 * The abstract parsers can load any xml file into a TinyXML document (TiXmlDocument)
 * and remembers the first element (aka the root) in that document.
 */
class AbstractParser {
private:
	TiXmlElement * root;
	TiXmlDocument doc;
public:
	AbstractParser(){};

	/*
	 * Returns the first element (aka the root) of the loaded XML Document.
	 * Root is returned as a TiXmlElement*
	 */
	TiXmlElement* getRoot(){return root;}

	/*
	 * Loads any XML file. Returns true when loading the file was succesfull.
	 * Returns false, when something went wrong during loading.
	 */
	bool loadFile(string filename);
};

#endif /* ABSTRACTPARSER_H_ */
