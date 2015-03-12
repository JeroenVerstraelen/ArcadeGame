#include <string>
#include <iostream>
#include "utils/DesignByContract.h"
#include "Entity.h"


using namespace std;


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

Object::Object(){
	_initCheck = this;
	ENSURE(properlyInitialized(),
		"Constructor must end in properlyInitialized state");
}
