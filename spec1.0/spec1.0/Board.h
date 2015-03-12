#ifndef Board_H
#define Board_H
#include <vector>
#include <ostream>
#include "Entity.h"


using namespace std;

class Board{
private:
	Board * _initCheck; // Used to check whether I am properly initialized.
	string fBoardName;
	int fBoardHeight;
	int fBoardWidth;
	vector<Entity*> fEntitiesPointer;
	vector<vector<Entity*> > fBoard;
	Player* fPlayer = NULL;

public:
/**
 * ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
 */
	/*
	 * Default constructor.
	 */
	Board();

	/*
	 * Will return true if the constructor of this object was called.
	 * @return Whether this object is properly initialized or not.
	 */
	bool properlyInitialized();

	// WARNING DESTRUCTOR REQUIRED FOR fEntitiesPointer, fBoard and fPlayer!!!

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
 * ENSURE(height > 0, "Height was smaller or equal to 0 when calling setHeight");
 * ENSURE((getHeight() == height), "setHeight postcondition failure");
 */
	/*
	 * Will set the height of the board.
	 * @param height The height to assign to the board.
	 */
	void setHeight(int height);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling setWidth");
 * ENSURE(width > 0, "Width was smaller or equal to 0 when calling setWidth");
 * ENSURE((getWidth() == width), "setWidth postcondition failure");
 */
	/*
	 * Will set the width of the board.
	 * @param width The width to assign to the board.
	 */
	void setWidth(int width);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling addEntity");
 * ENSURE(entity.properlyInitialized(), "Entity wasn't initialized when calling addEntity");
 * ENSURE(getEntities().size() <= (unsigned) (getWidth() * getHeight()), 
 * 	"Entity count must not exceed total amount of spaces");	
 * ENSURE((getEntities().back() == &entity), "addEntity postcondition failure");
 */
	/*
	 * Will add an entity to the board.
	 * @param entity The entity to add to the board.
	 */
	void addEntity(Entity& entity);

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling generateBoard");
 * ENSURE(getBoard().size() == (unsigned)getWidth() && getBoard()[0].size() == (unsigned)getHeight(), 
 *	"The board width must be equal to fBoardWidth and the board height must be equal to fBoardHeight");
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
 * ENSURE((*result).properlyInitialized(), "Player object must be properly initialized");		
 */
	/*
	 * Returns the player of the board.
	 * @return The player of the board.
	 */
	Player* getPlayer();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getHeight");
 * ENSURE(result > 0, "Board height must be greater than 0 when calling getHeight");
 */
	/*
	 * Returns the height of the board.
	 * @return The height of the board.
	 */
	int getHeight();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getWidth);
 * ENSURE(result > 0, "Board width must be greater than 0 when calling getWidth");
 */
	/*
	 * Returns the width of the board.
	 * @return The width of the board.
	 */
	int getWidth();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getBoard");
 * ENSURE(result.size() == (unsigned)getWidth() && result[0].size() == (unsigned)getHeight(), 
 *	"The board width must be equal to getWidth and the board height must be equal to getHeight");
 */
	/*
	 * Returns the 2D array that represents the board.
	 * @return The 2D array that represents the board.
	 */
	vector<vector<Entity*> > getBoard();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling isValid");
 */
	/*
	 * Returns whether it is possible to use this board.
	 * @return Whether it is possible to use this board.
	 */
	bool isValid();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling getEntities");
 * REQUIRE(result.size() <= (unsigned) (getWidth() * getHeight()),
 *	"Entity count exceeded maximum amount of free spaces when calling getEntities");		
 */
	/*
	 * Returns the entities assigned to this board.
	 * @return The entities assigned to this board.
	 */
	vector<Entity*> getEntities();

/*
 * REQUIRE(this->properlyInitialized(), "Board wasn't initialized when calling writeOn");
 * ENSURE(onStream != "", "onStream was empty when calling writeOn.");
 */
	/*
	 * Writes a representation of the board on onStream.
	 * @param onStream The stream to write the representation on.
	 */
	void writeOn(std::ostream& onStream);
};


#endif
