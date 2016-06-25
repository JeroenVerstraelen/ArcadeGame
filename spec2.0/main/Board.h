//============================================================================
// Name        : Board.h
// Author      : Jeroen Verstraelen & Nisse Strauven
// Version     :
// Description : ArcadeGame in C++
//============================================================================

#ifndef Board_H
#define Board_H
#include <vector>
#include <ostream>
#include <sstream>
#include "Entity.h"


using namespace std;

class Board{
private:
	Board * _initCheck; // Used to check whether I am properly initialized.
	string fBoardName;
	int fBoardHeight;
	int fBoardWidth;
	vector<Entity*> fEntitiesPointer; // Vector of all entities on the board.
	vector<vector<vector<Entity*> > > fBoard; // 2d array of vectors of pointers to entities representing the board.
	vector<pair<pair<string, string>, string> > fActions; // List of actions <<id, direction>, itemtype>.
	vector<pair<pair<string, string>, string> > fActionsRemaining; // List of remaining actions <<id, direction>, itemtype>.
	Player* fPlayerPointer;

	bool containsMovable(int x, int y);
	bool isWalkable(int x, int y);
	bool checkMove(int& x, int& y, string movement);
	bool checkMoves();
	void deleteEntity(Entity* entityPointer);

public:
/**
 * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Board();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling destructor");
 */
	/*
	 * Destructor.
	 */
 	~Board();

	/*
	 * Will return true if the constructor of this object was called.
	 * @return Whether this object is properly initialized or not.
	 */
	bool properlyInitialized();


/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling setName");
 * ENSURE((getBoardName() == boardName), "setName postcondition failure");
 */
	/*
	 * Will set the name of the board.
	 * @param boardName The name to assign to the board.
	 */
	void setName(string boardName);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling setPlayer");
 * ENSURE(player.properlyInitialized(), "Player wasn't initialized when calling setPlayer");
 * ENSURE(getPlayer().getPlayerName() == player.getPlayerName(), "setPlayer postcondition failure");
 */
	/*
	 * Will set the player of the board.
	 * @param player The player to assign to the board.
	 */
	void setPlayer(Player& player);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling setHeight");
 * ENSURE((getHeight() == height), "setHeight postcondition failure");
 */
	/*
	 * Will set the height of the board.
	 * @param height The height to assign to the board.
	 */
	void setHeight(int height);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling setWidth");
 * ENSURE((getWidth() == width), "setWidth postcondition failure");
 */
	/*
	 * Will set the width of the board.
	 * @param width The width to assign to the board.
	 */
	void setWidth(int width);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling setActions");
 * ENSURE((getActions() == actions), "setWidth postcondition failure");
 */
	/*
	 * Will set the actions of the board.
	 * @param actions The actions to assign to the board.
	 */
	void setActions(vector<pair<pair<string, string>, string> > actions);


/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling addEntity");
 * ENSURE(entity.properlyInitialized(), "Entity wasn't initialized when calling addEntity");
 * ENSURE((getEntities().back() == &entity), "addEntity postcondition failure");
 */
	/*
	 * Will add an entity to the board.
	 * @param entity The entity to add to the board.
	 */
	void addEntity(Entity& entity);

/*	
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling addAction");
 */	
	/*
	 * Will add an action to the board.
	 * @param action The action to be added.
	 */
	void addAction(pair<pair<string,string>, string> action);	

/*	
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling doActions");
 */	
	/*
	 * Will execute all actions.
	 * @return Whether all actions succeeded.
	 */
	bool doActions();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling generateBoard");
 */
	/*
	 * Will generate the 2D array that represents the board.
	 */
	void generateBoard();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getBoardName");
 * ENSURE(result != "", "The board name must not be blank");
 */
	/*
	 * Returns the name of the board.
	 * @return The name of the board.
	 */
	string getBoardName();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getPlayer");
 */
	/*
	 * Returns the player of the board.
	 * @return The player of the board.
	 */
	Player* getPlayer();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getHeight");
 * ENSURE(result >= 0, "Board height must be greater or equal than 0 when calling getHeight");
 */
	/*
	 * Returns the height of the board.
	 * @return The height of the board.
	 */
	int getHeight();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getWidth);
 * ENSURE(result >= 0, "Board width must be greater or equal than 0 when calling getWidth");
 */
	/*
	 * Returns the width of the board.
	 * @return The width of the board.
	 */
	int getWidth();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getActions");
 */
	/*
	 * Returns the actions of the board.
	 * @return The actions of the board.
	 */
	vector<pair<pair<string, string>, string> > getActions();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getBoard");
 * ENSURE(result.size() == (unsigned)getWidth() && result[0].size() == (unsigned)getHeight(), 
 *	"The board width must be equal to getWidth and the board height must be equal to getHeight");
 */
	/*
	 * Returns the 2D array that represents the board.
	 * @return The 2D array that represents the board.
	 */
	vector<vector<vector<Entity*> > > getBoard();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling contains");	
 */
	/*
	 * Returns whether the board contains an entity with id.
	 * @return whether the board contains an entity with id.
	 */
	bool contains(string id);


/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling isValid");
 */
	/*
	 * Returns whether this board has errors.
	 * @return Whether this board has errors.
	 */
	bool isValid();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getEntities");
 */
	/*
	 * Returns the entities assigned to this board.
	 * @return The entities assigned to this board.
	 */
	vector<Entity*> getEntities();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getEntity");	
 */
	/*
	 * Returns a pointer to the entity with id.
	 * @return a pointer to the entity with id.
	 */
	Entity* getEntity(string id);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling writeOn");
 * ENSURE(onStream != "", "onStream must not be empty after calling writeOn.");
 */
	/*
	 * Writes a representation of the board on onStream.
	 * @param onStream The stream to write the representation on.
	 */
	bool writeOn(ostringstream& onStream);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling writeActions");
 */
	/*
	 * Writes all the remaining actions on onStream.
	 * @param onStream The stream to write the actions on.
	 */
	bool writeActions(ostringstream& onStream);

/*	
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling project");
 */	
	/*
	 * Writes a graphical representation of the board on onStream.
	 * @param onStream The stream to write the board on.
	 */
	bool project(ostringstream& onStream);
};


#endif
