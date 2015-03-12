#ifndef Entity_H
#define Entity_H
#include <utility>
#include <string>


using namespace std;


class Entity{
protected:
	Entity * _initCheck; // Used to check whether I am properly initialized.
	bool fIsObstacle;
	bool fIsMovable;
	string fEntityType;
	int fX;
	int fY;

public:

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
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling isObstacle");
 */
	bool isObstacle();

/*
 * REQUIRE(this->properlyInitialized(), "Entity wasn't initialized when calling isMovable");
 */
	bool isMovable();

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
};


class Player: public Entity{
private:
	string fPlayerName;
public:
/**
 * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Player();

/*
 * REQUIRE(this->properlyInitialized(), "Player wasn't initialized when calling setPlayerName");
 * ENSURE(getPlayerName() == playername, "setPlayerName postcondition failure");
 */
	void setPlayerName(string playername);

/*
 * REQUIRE(this->properlyInitialized(), "Player wasn't initialized when calling getPlayerName");
 */
	string getPlayerName();
};


class Object: public Entity{
public:
/**
 * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Object();
};


#endif
