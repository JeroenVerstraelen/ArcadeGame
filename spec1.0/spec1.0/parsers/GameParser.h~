#include <string>
#include <map>
#include "../Board.h"
#include "../Entity.h"
#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"


using namespace std;


class BoardParser: public AbstractParser{
private:
	string readAttribute(TiXmlElement* elem, const char* attribute);
	string readElement(TiXmlElement* elem, const char* tag);

public:
	BoardParserr();
	virtual ~BoardParser();

	Board* parseBoard(TiXmlElement* elem);
	map<string, vector<string> > parseMovement(TiXmlElement* elem);
};
