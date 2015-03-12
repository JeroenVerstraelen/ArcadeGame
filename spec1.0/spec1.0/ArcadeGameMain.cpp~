#include <iostream>
#include <fstream>
#include "Entity.h"
#include "Board.h"
#include "utils/parsers/AbstractParser.h"
#include "utils/parsers/GameParser.h"

using namespace std;


void writeToFile(Board& board){
	
}

int main(int argc, char **argv) {
	GameParser gameParser;
	if(!gameParser.loadFile("xmlDocuments/Speelveld1.0.xml"))
		return -1;	
	Board board = gameParser.parseBoard(gameParser.getRoot());
	if(!gameParser.loadFile("xmlDocuments/Bewegingen1.0.xml"))
		return -1;		
	map<string, vector<string> > playerMovement = gameParser.parseMovement(gameParser.getRoot());	
	writeToFile(board);
}
