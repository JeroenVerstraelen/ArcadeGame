#include "BoardParser.h"
#include <stdlib.h>


BoardParser::BoardParser() {
}

BoardParser::~BoardParser() {
}

const char* readAttribute(TiXmlElement* elem, const char* tag) {
	const char* attribute = elem->attribute(tag);
	if(attribute == NULL)
		return "";
	return attribute;
}

string BoardParser::readElement(TiXmlElement* elem, const char* tag) {
	TiXmlElement* e = elem->FirstChildElement(tag);
	TiXmlNode* node = e->FirstChild();
	TiXmlText* text = node->ToText();
	if(text == NULL)
		return "";
	return text->Value();
}

Board* BoardParser::parseBoard(TiXmlElement* elem) {	
	string board_name = readElement(elem, "NAAM");
	int length = readElement(elem, "LENGTE");
	int width = readElement(elem, "BREEDTE");

	TiXmlElement* player_element = elem->FirstChildELement("SPELER");
	string player_name = readElement(player_element, "NAAM");
	int player_x = atoi(readAttribute(player_element->attribute("x")));
	int player_y = atoi(readAttribute(player_element->attribute("y")));
	Player player(player_x, player_y, player_name);

	vector<Entity> entities;
	for(TiXmlElement* object_element = elem->FirstChildElement("OBSTAKEL"); object_element != NULL; 
		object_element = object_element->NextSiblingElement("OBSTAKEL")){
		bool movable = readAttribute(object_element, attribute("beweegbaar")) == "true";
		int object_x = atoi(readAttribute(object_element->attribute("x")));
		int object_y = atoi(readAttribute(object_element->attribute("y")));	
		string type = readElement(object_element->FirstChildElement("TYPE"));

		Entity entity(object_x, object_y, true, movable, type);
		entities.push_back(entity);
	}

	return Board(length, width, board_name, player, entities);
}


map<string, vector<string> > BoardParser::parseMovement(TiXmlElement* elem){
	map<string, vector<string> > player_movement;

	for(TiXmlElement* movement_element = elem->FirstChildElement("BEWEGING"); movement_element != NULL;
		object_element = movement_element->NextSiblingElement("BEWEGING")){
		string player_name = readElement(movement_element("SPELERNAAM"));
		string move = readElement(movement_element("BEWEGING"));
		player_movement[player_name].push_back(move);
	}	

	return player_movement;
}

