//============================================================================
// Name        : AbstractParser.cpp
// Author      : Quinten Soetens
// Version     :
// Description : This code is written as an example solution for the exercises given in the course
//				 Project Software Engineering for the first year bachelor students at Universiteit Antwerpen
//============================================================================

#include "AbstractParser.h"

AbstractParser::AbstractParser() {
	// TODO Auto-generated constructor stub

}

AbstractParser::~AbstractParser() {
	// TODO Auto-generated destructor stub
}

bool AbstractParser::loadFile(string filename) {
	if(!doc.LoadFile(filename.c_str())){
		cerr << doc.ErrorDesc() << endl;
		return false;
	}

	root = doc.FirstChildElement();
	if(root == NULL){
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
		return false;
	}
	return true;
}

