//============================================================================
// Name        : GameParser.h
// Author      : Jeroen Verstraelen
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#ifndef GameParser_H
#define GameParser_H
#include <string>
#include <map>
#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"
#include "../../Board.h"


using namespace std;


class GameParser: public AbstractParser{
private:
	const char* readAttributeCString(TiXmlElement* elem, const char* tag);

	string readAttributeString(TiXmlElement* elem, const char* tag);

	const char* readElementCString(TiXmlElement* elem, const char* tag);

	string readElementString(TiXmlElement* elem, const char* tag);

public:
	GameParser(){};

/**
 * REQUIRE(board.properlyInitialized(), "Board object was not properly initialized when calling parseBoardElement.");
 */
	void parseBoardElement(Board& board, TiXmlElement* element);

	void parseBoard(TiXmlElement* elem, Board& board);

/**
 * REQUIRE(board.properlyInitialized(), "Board object was not properly initialized when calling parseMovementElement.");
 */
        void parseMovementElement(Board& board, TiXmlElement* element);

/**
 * REQUIRE(board.properlyInitialized(), "Board object was not properly initialized when calling parseMovement.");
 */
	void parseMovement(TiXmlElement* elem, Board& board);
};

#endif
