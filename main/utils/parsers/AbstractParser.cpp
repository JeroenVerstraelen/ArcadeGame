//============================================================================
// Name        : AbstractParser.cpp
// Author      : Quinten Soetens
// Version     :
// Description : This code is written as an example solution for the exercises given in the course
//				 Project Software Engineering for the first year bachelor students at Universiteit Antwerpen
//============================================================================

#include "AbstractParser.h"

bool AbstractParser::loadFile(string filename) {
	if(!doc.LoadFile(filename.c_str())){
		cerr << "Failed to load file: Bad XML" << endl;
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

