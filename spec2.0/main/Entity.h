//============================================================================
// Name        : Entity.h
// Author      : Jeroen Verstraelen & Nisse Strauven
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#ifndef Entity_H
#define Entity_H
#include <utility>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


class Entity{
protected:
	Entity * _initCheck; // Used to check whether I am properly initialized.
	bool fIsObstacle;
	bool fIsMovable;
	bool fIsClosed = false;
	string fEntityType;
	int fX;
	int fY;
	string fID;

public:

/*
 * ENSURE(properlyInitialized(), "Constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Entity();

/*
 * ENSURE(properlyInitialized(), "Copy constructor must end in properlyInitialized state");
 */
	/*
	 * Copy constructor.
	 */
//	Entity(const Entity &entity);

	bool properlyInitialized();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setObstacle");
 * ENSURE(isObstacle() == isObstacle, "setObstacle postcondition failure");
 */
	void setObstacle(bool obstacle);

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setMovable");
 * ENSURE(isMovable() == isMovable, "setMovable postcondition failure");
 */
	void setMovable(bool movable);

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setClosed");
 * ENSURE(isClosed() == closed, "setClosed postcondition failure");
 */
	void setClosed(bool closed);

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setType");
 * ENSURE(getType() == type, "setType postcondition failure");
 */
	void setType(string type);

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setX");
 * ENSURE(getX() == x, "setX postcondition failure");
 */
	void setX(int x);

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setY");
 * ENSURE(getY() == y, "setY postcondition failure");
 */
	void setY(int y);

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling setID");
 * ENSURE(getID() == id, "setID postcondition failure");
 */
	void setID(string id);


/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling isObstacle");
 */
	bool isObstacle();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling isMovable");
 */
	bool isMovable();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling isClosed");
 */
	bool isClosed();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling getType");
 */
	string getType();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling getX");
 */
	int getX();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling getY");
 */
	int getY();

/*
 * REQUIRE(this->properlyInitialized(),"Entity wasn't initialized when calling getID");
 */
	virtual string getID();
};


class Player: public Entity{
private:
	string fPlayerName;
	vector<string> fMovements;

public:

/**
 * ENSURE(properlyInitialized(), "Constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Player();

/**
 * ENSURE(properlyInitialized(), "Copy constructor must end in properlyInitialized state");
 */
	/*
	 * Copy constructor.
	 */
//	Player(const Player &player);


/*
 * REQUIRE(this->properlyInitialized(), "Player wasn't initialized when calling setPlayerName");
 * ENSURE(getPlayerName() == playername, "setPlayerName postcondition failure");
 */
	void setPlayerName(string playername);

/*
 * REQUIRE(this->properlyInitialized(), "Player wasn't initialized when calling getPlayerName");
 */
	string getPlayerName();

/*
 * REQUIRE(this->properlyInitialized(), "Player wasn't initialized when calling getID");
 */
	string getID() override;

};


class Object: public Entity{
public:
/**
 * ENSURE(properlyInitialized(), "Constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Object();

/**
 * ENSURE(properlyInitialized(), "Copy constructor must end in properlyInitialized state");
 */
	/*
	 * Copy constructor.
	 */
//	Object(const Object &object);

};


#endif
