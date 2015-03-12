#include <ostream>
#include <iostream>
#include "utils/DesignByContract.h"
#include "Board.h"
#include "Entity.h"


using namespace std;


Board::Board(){
	_initCheck = this;
	ENSURE(properlyInitialized(), 
		"constructor must end in properlyInitialized state");
}

bool Board::properlyInitialized() {
	return _initCheck == this;
}


void Board::setName(string boardName){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setName");	
	fBoardName = boardName;
	ENSURE((getBoardName() == boardName), "setName postcondition failure");
}

void Board::setPlayer(Player& player){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setPlayer");
	ENSURE(player.properlyInitialized(), 
		"Player wasn't initialized when calling setPlayer");
	fPlayer = &player;	
	ENSURE((*getPlayer()).getPlayerName() == player.getPlayerName(), "setPlayer postcondition failure");
}

void Board::addEntity(Entity& entity){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling addEntity");
	ENSURE(entity.properlyInitialized(), 
		"Entity wasn't initialized when calling addEntity");
	ENSURE(getEntities().size() <= (unsigned) (getWidth() * getHeight()),
		"Entity count must not exceed total amount of spaces");	
	fEntitiesPointer.push_back(&entity);
	ENSURE(getEntities().back() == &entity, "addEntity postcondition failure");
}

void Board::setHeight(int height){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setHeight");	
	ENSURE(height > 0, 
		"Height was smaller or equal to 0 when calling setHeight");
	fBoardHeight = height;
	ENSURE((getHeight() == height), "setHeight postcondition failure");
}

void Board::setWidth(int width){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setWidth");
	ENSURE(width > 0, 
		"Width was smaller or equal to 0 when calling setWidth");
	fBoardWidth = width;
	ENSURE((getWidth() == width), "setWidth postcondition failure");	
}

void Board::generateBoard(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling generateBoard");	
	// Generating empty board.
	for(int col = 0; col < fBoardWidth; col++){
		vector<Entity*> temporary;
		for(int row = 0; row < fBoardHeight; row++){
			temporary.push_back(NULL);
		}
		fBoard.push_back(temporary);
	}
	// Generating Entities on board.
	for(unsigned int index = 0; index < fEntitiesPointer.size(); index++){
		Entity* entityPointer = fEntitiesPointer[index];
		int entityX = entityPointer->getX();
		int entityY = entityPointer->getY();
		fBoard[entityX][entityY] = entityPointer;
	}
	ENSURE(getBoard().size() == (unsigned)getWidth() && getBoard()[0].size() == (unsigned)getHeight(), 
		"The board width must be equal to fBoardWidth"\
		"and the board height must be equal to fBoardHeight");
}


string Board::getBoardName(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getBoardName");	
	string result = fBoardName;
	ENSURE(result != "", 
		"The board name must not be blank");
	return result;
}

Player* Board::getPlayer(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getPlayer");
	Player* result = fPlayer;
	ENSURE((*result).properlyInitialized(), 
		"Player object must be properly initialized");	
	return result;
}

vector<Entity*> Board::getEntities(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getEntities");
	vector<Entity*> result = fEntitiesPointer;
	REQUIRE(result.size() <= (unsigned) (getWidth() * getHeight()),
		"Entity count exceeded maximum amount of free spaces"\
		"when calling getEntities");		
	return result;
}

int Board::getHeight(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getHeight");	
	int result = fBoardHeight;
	ENSURE(result > 0, 
		"Board height must be greater than 0 when calling getHeight");
	return result;
}

int Board::getWidth(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getWidth");	
	int result = fBoardWidth;
	ENSURE(result > 0, 
		"Board width must be greater than 0 when calling getWidth");
	return result;
}

vector<vector<Entity*> > Board::getBoard(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getBoard");
	vector<vector<Entity*> > result = fBoard;
	ENSURE(result.size() == (unsigned)getWidth() && result[0].size() == (unsigned)getHeight(), 
		"The board width must be equal to getWidth"\
		"and the board height must be equal to getHeight");
	return result;
}

bool Board::isValid(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling isValid");	
	if(fBoardWidth > 0 && fBoardHeight > 0){
		if(fPlayer != NULL && fBoardName == ""){
			if(fBoard.size() ==  (unsigned)fBoardWidth && fBoard[0].size() ==  (unsigned)fBoardHeight){
				if(fEntitiesPointer.size() <=  (unsigned)(fBoardWidth * fBoardHeight)){
					return true;
				}
			}
		}
	}
	return false;
}


void Board::writeOn(std::ostream& onStream) {
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling writeOn");
	onStream << fBoardName << endl;
	for(int col = fBoardWidth-1; col >= 0; col--){
		onStream << col;
		for (int row = 0; row < fBoardHeight; row++) {
			if(fBoard[row][col] != NULL)
				onStream << " | " << fBoard[row][col]->getType();
			else{
				onStream << " |     ";
			}
		}
		onStream << " |" << std::endl;
	};
	onStream << "  ------------- " << endl;
 	ENSURE(onStream != "", 
		"onStream was empty when calling writeOn.");
}
