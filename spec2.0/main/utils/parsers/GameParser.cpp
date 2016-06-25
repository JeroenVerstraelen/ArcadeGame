//============================================================================
// Name        : GameParser.cpp
// Author      : Jeroen Verstraelen
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#include <stdlib.h>
#include <vector>
#include <string>
#include <utility>
#include "GameParser.h"
#include "../DesignByContract.h"
#include "../../Board.h"
#include "../../Entity.h"

using namespace std;

const char* GameParser::readAttributeCString(TiXmlElement* elem, const char* tag) {
	const char* Attribute = elem->Attribute(tag);
	if(Attribute == NULL){
		cout << "Failed to read attribute with tag '" << tag  << "'." << endl;
		return "";
	}
	return Attribute;
}

string GameParser::readAttributeString(TiXmlElement* elem, const char* tag) {
	const char* Attribute = elem->Attribute(tag);
	if(Attribute == NULL){
		cout << "Failed to read attribute with tag '" << tag  << "'." << endl;
		return "";
	}
	return Attribute;
}

const char* GameParser::readElementCString(TiXmlElement* elem, const char* tag) {
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();
	if(text == NULL){
		cout << "Failed to read element with tag " << tag  << "." << endl;
		return "";
	}
	return text->Value();
}

string GameParser::readElementString(TiXmlElement* elem, const char* tag) {
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();
	if(text == NULL){
		cout << "Failed to read element with tag " << tag  << "." << endl;
		return "";
	}
	return text->Value();
}


void GameParser::parseBoardElement(Board& board, TiXmlElement* element){
	REQUIRE(board.properlyInitialized(), 
		"Board object was not properly initialized when calling parseBoardElement.");
	string elementName = element->Value();
	if(elementName == "NAAM")
		board.setName(readElementString(element, "NAAM"));
	else if(elementName == "LENGTE"){
		int height = atoi(readElementCString(element, "LENGTE"));	
		if(height <= 0){
			cout << "Invalid board Height: Height <= 0" << endl;
			return;
		}
		board.setHeight(height);
		if(board.getPlayer() != NULL){
			int y = board.getPlayer()->getY();
			if(y >= height){
					cout << "Invalid coordinates for player." << endl;
					return;
			}
		}
	}
	else if(elementName == "BREEDTE"){
		int width = atoi(readElementCString(element, "BREEDTE"));
		if(width <= 0){
			cout << "Invalid board width: width <= 0" << endl;
			return;
		}
		board.setWidth(width);
		if(board.getPlayer() != NULL){
			int x = board.getPlayer()->getX();
			if(x >= width){
					cout << "Invalid coordinates for player." << endl;
					return;
			}
		}
	}		
	else if(elementName == "SPELER"){
		Player* player = new Player();
		TiXmlElement* childElement = element->FirstChildElement();
		player->setPlayerName(readElementString(childElement, "NAAM"));
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));
		
		if(x < 0 or y < 0){
			cout << "Invalid coordinates for player." << endl;
			return;
		}
		if(board.getWidth() != 0 && board.getHeight() != 0){
			if(x>= board.getWidth() or y>= board.getHeight()){
				cout << "Invalid coordinates for player." << endl;
				return;
			}
		}
		player->setX(x);
		player->setY(y);
		board.setPlayer((*player));
	}
	else if(elementName == "MUUR"){
		Object* object = new Object();
		const char* trueCheck = "true";
		object->setType("muur");
		object->setMovable(strcmp(readAttributeCString(element, "beweegbaar"),trueCheck) == 0);
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "DOEL"){
		Object* object = new Object();
		object->setType("een doel");
		object->setMovable(false);
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "POORT"){
		Object* object = new Object();
		const char* trueCheck = "true";
		object->setType("een poort");
		object->setMovable(strcmp(readAttributeCString(element, "beweegbaar"),trueCheck) == 0);
		object->setClosed(true);
		TiXmlElement* childElement = element->FirstChildElement();
		object->setID(readElementString(childElement, "ID"));
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "KNOP"){
		Object* object = new Object();
		object->setType("een knop");
		object->setMovable(false);
		object->setID(readAttributeString(element, "id"));
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "TON"){
		Object* object = new Object();
		const char* trueCheck = "true";
		object->setType("een ton");
		object->setMovable(strcmp(readAttributeCString(element, "beweegbaar"),trueCheck) == 0);
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "WATER"){
		Object* object = new Object();
		const char* trueCheck = "true";
		object->setType("water");
		object->setMovable(false);
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "MONSTER"){
		Object* object = new Object();
		object->setType("een monster");
		object->setMovable(false);
		TiXmlElement* childElement = element->FirstChildElement();
		object->setID(readElementString(childElement, "ID"));
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}
	else if(elementName == "VALSTRIK"){
		Object* object = new Object();
		object->setType("een valstrik");
		object->setMovable(false);
		int x = atoi(readAttributeCString(element, "x"));
		int y = atoi(readAttributeCString(element, "y"));	
		if(x < 0 or y < 0 or x>= board.getWidth() or y>= board.getHeight()){
			cout << "Invalid coordinates for object." << endl;
			return;
		}
		object->setX(x);
		object->setY(y);
		board.addEntity((*object));
	}

	return;
}

void GameParser::parseBoard(TiXmlElement* element, Board& board) {
	if(element != NULL){
		TiXmlElement* currentElement = element->FirstChildElement();
		while(currentElement != NULL){
			parseBoardElement(board, currentElement);
			currentElement = currentElement->NextSiblingElement();
		}
		board.generateBoard();
	}
}


void GameParser::parseMovementElement(Board& board, TiXmlElement* element){
	REQUIRE(board.properlyInitialized(), 
		"Board object was not properly initialized when calling parseMovementElement.");
	string elementName = element->Value();
	if(elementName == "BEWEGING"){		
		pair<string, string> move;	
		pair<pair<string, string>, string> action;
		
		string actionType = "BEWEGING";
			
		TiXmlElement* NameElement = element->FirstChildElement("ID");
		TiXmlElement* MoveElement = element->FirstChildElement("RICHTING");
		
		string id = readElementString(NameElement, "ID");
		
		if(!board.contains(id)) {
			cout << "Board does not contain element: " << id << endl;
			return;
		}

		move = make_pair(id, readElementString(MoveElement, "RICHTING"));
		action = make_pair(move, actionType);
		board.addAction(action);
	}

	else if(elementName == "AANVAL"){		
		pair<string, string> attack;	
		pair<pair<string, string>, string> action;
		
		string actionType = "AANVAL";
			
		TiXmlElement* NameElement = element->FirstChildElement("ID");
		TiXmlElement* MoveElement = element->FirstChildElement("RICHTING");

		string id = readElementString(NameElement, "ID");
		
		if (!board.contains(id)) {
			cout << "Board does not contain element: " << id << endl;
			return;
		}

		attack = make_pair(id, readElementString(MoveElement, "RICHTING"));
		action = make_pair(attack, actionType);
		board.addAction(action);
	}
}

void GameParser::parseMovement(TiXmlElement* element, Board& board){
	REQUIRE(board.properlyInitialized(), 
		"Board object was not properly initialized when calling parseMovement.");
	TiXmlElement* currentElement = element->FirstChildElement();

	while(currentElement != NULL){
		parseMovementElement(board, currentElement);
		currentElement = currentElement->NextSiblingElement();
	}
}
