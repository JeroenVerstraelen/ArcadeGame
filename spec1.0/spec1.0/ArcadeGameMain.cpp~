#include <iostream>
#include "Entity.h"
#include "Board.h"
#include "/AbstractParser.h"
#include "/GameParser.h"

using namespace std;

int main(int argc, char **argv) {
	AbstractParser parser();

	GameParser gameParser();
	gameParser.loadFile("Speelveld1.0.xml");
	Board board = gameParser.parseBoard(gameParser.getRoot());

	gameParser.loadFile("Bewegingen1.0.xml");
	map<string, vector<string> > playerMovement = gameParser.parseMovement(gameParser.getRoot());	
	
}
