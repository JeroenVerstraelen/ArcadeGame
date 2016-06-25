//============================================================================
// Name        : Entity.cpp
// Author      : Jeroen Verstraelen & Nisse Strauven
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "utils/DesignByContract.h"
#include "Entity.h"


using namespace std;
/*
 * ENTITY
 */
Entity::Entity(){
	fIsObstacle = false;
	fIsMovable = false;
	fEntityType = "Entity";
	fX = 0;
	fY = 0;
	_initCheck = this;
	ENSURE(properlyInitialized(),
		"Constructor must end in properlyInitialized state");
}

bool Entity::properlyInitialized(){
	return _initCheck == this;
}

void Entity::setObstacle(bool obstacle){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling setObstacle");
	fIsObstacle = obstacle;
	ENSURE(isObstacle() == obstacle, "setObstacle postcondition failure");
}

void Entity::setMovable(bool movable){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling setMovable");
	fIsMovable = movable;
	ENSURE(isMovable() == movable, "setMovable postcondition failure");
}

void Entity::setClosed(bool closed){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling setClosed");
	fIsClosed = closed;
	ENSURE(isClosed() == closed, 
		"setClosed postcondition failure");
}

void Entity::setType(string type){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling setType");
	fEntityType = type;
	ENSURE(getType() == type, "setType postcondition failure");
}

void Entity::setX(int x){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling setX");
	fX = x;
	ENSURE(getX() == x, "setX postcondition failure");
}

void Entity::setY(int y){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling setY");
	fY = y;
	ENSURE(getY() == y, "setY postcondition failure");
}


void Entity::setID(string id){
	REQUIRE(this->properlyInitialized(),
		 "Entity wasn't initialized when calling setID");
	fID = id;
 	ENSURE(getID() == id, 
		"setID postcondition failure");
}

bool Entity::isObstacle(){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling isObstacle");
	return fIsObstacle;
}

bool Entity::isMovable(){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling isMovable");
	return fIsMovable;
}

bool Entity::isClosed(){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling isClosed");
	return fIsClosed;
}

string Entity::getType(){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling getType");
	return fEntityType;
}

int Entity::getX(){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling getX");
	return fX;
}

int Entity::getY(){
	REQUIRE(this->properlyInitialized(), 
		"Entity wasn't initialized when calling getY");
	return fY;
}

string Entity::getID(){
	REQUIRE(this->properlyInitialized(),
		 "Entity wasn't initialized when calling getID");
	return fID;
}


/*
 * PLAYER
 */
Player::Player(){
	_initCheck = this;
	setType("Player");
	ENSURE(properlyInitialized(),
		"constructor must end in properlyInitialized state");
}

void Player::setPlayerName(string playername){
	REQUIRE(this->properlyInitialized(), 
		"Player wasn't initialized when calling setPlayerName");
	fPlayerName = playername;
	ENSURE(getPlayerName() == playername, "setPlayerName postcondition failure");
}


string Player::getPlayerName(){
	REQUIRE(this->properlyInitialized(), 
		"Player wasn't initialized when calling getPlayerName");
	return fPlayerName;
}

string Player::getID(){
	REQUIRE(this->properlyInitialized(), 
		"Player wasn't initialized when calling getID");
	return getPlayerName();
}



/*
 * OBJECT
 */
Object::Object(){
	_initCheck = this;
	ENSURE(properlyInitialized(),
		"Constructor must end in properlyInitialized state");
}


