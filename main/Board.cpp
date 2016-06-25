//============================================================================
// Name        : Board.cpp
// Author      : Jeroen Verstraelen & Nisse Strauven
// Version     :
// Description : ArcadeGame in C++
//============================================================================


#include <ostream>
#include <iostream>
#include <sstream>
#include <utility>
#include "utils/DesignByContract.h"
#include "Board.h"
#include "Entity.h"


using namespace std;


Board::Board(){
	_initCheck = this;
	fBoardName = "";
	fBoardWidth = 0;
	fBoardHeight = 0;
	fPlayerPointer = NULL;
	ENSURE(properlyInitialized(), 
		"constructor must end in properlyInitialized state");
}

Board::~Board(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling destructor");
	while (fEntitiesPointer.empty() == false){
		delete fEntitiesPointer.back(); 
		fEntitiesPointer.pop_back();
	}
}

bool Board::containsMovable(int x, int y){
	for(vector<Entity*>::iterator entityIterator = fBoard[x][y].begin(); 
		entityIterator != fBoard[x][y].end(); entityIterator++){
		if((*entityIterator) != NULL && (*entityIterator)->isMovable())
			return true;
	}
	return false;
}

bool Board::isWalkable(int x, int y){
	if(containsMovable(x, y))
		return true;
	for(vector<Entity*>::iterator entityIterator = fBoard[x][y].begin();
		entityIterator != fBoard[x][y].end(); entityIterator++){
		if((*entityIterator) != NULL && !(*entityIterator)->isMovable()){
			if((*entityIterator)->getType() == "water")
				return true;
			else if((*entityIterator)->getType() == "een knop")
				return true;
			else if((*entityIterator)->getType() == "een doel")
				return true;
			else if((*entityIterator)->getType() == "Player")
				return true;
			else if((*entityIterator)->getType() == "een poort"){
				if(!((*entityIterator)->isClosed()))
					return true;
			}
		}
		if((*entityIterator) == NULL)
			return true;
	}
	return false;	
}


bool Board::checkMove(int& x, int& y, string movement){
	if(movement == "OMHOOG"){
		y += 1;
		if(containsMovable(x, y)){
			if(!isWalkable(x, y+1) or containsMovable(x, y+1))
				return false;
		}
	}
	else if(movement == "OMLAAG"){
		y -= 1;
		if(containsMovable(x, y)){
			if(!isWalkable(x, y-1) or containsMovable(x, y-1))
				return false;
		}
	}
	else if(movement == "RECHTS"){
		x += 1;
		if(containsMovable(x, y)){
			if(!isWalkable(x+1, y) or containsMovable(x+1, y))
				return false;
		}
	}
	else if(movement == "LINKS"){
		x -= 1;
		if(containsMovable(x, y)){
			if(!isWalkable(x-1, y) or containsMovable(x-1, y))
				return false;
		}
	}
	else
		return false;
	if(y < 0 or y >= fBoardHeight)
		return false;
	if(x < 0 or y >= fBoardWidth)
		return false;
	if(fBoard[x][y].back() != NULL && fBoard[x][y].back()->getType() == "een monster")
		return false;
	if(!isWalkable(x, y))
		return false;
	return true;
}

bool Board::checkMoves(){
	for(vector<pair<pair<string, string>, string> >::iterator actionIterator = fActions.begin(); 
		actionIterator != fActions.end(); actionIterator++){
		pair<pair<string, string>, string> action = (*actionIterator);
		Entity* entityPointer = getEntity(action.first.first);
		int x = entityPointer->getX();
		int y = entityPointer->getY();
		string direction = action.first.second;
		string actionType = action.second;
		if(actionType == "BEWEGING"){
			if(!checkMove(x, y, direction))
				return false;
		}
	}
	return true;
}

void Board::deleteEntity(Entity* entityPointer){
	int x = entityPointer->getX();
	int y = entityPointer->getY();
	unsigned int index = 0;
	for( ; index != fEntitiesPointer.size(); index++){
		if(fEntitiesPointer[index] == entityPointer)
			break;
	}
	fEntitiesPointer.erase(fEntitiesPointer.begin()+index);
	fBoard[x][y].pop_back();
	if(fBoard[x][y].empty())
		fBoard[x][y].push_back(NULL);
	delete entityPointer; 
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
	fPlayerPointer = &player;
	addEntity(player);	
	ENSURE((*getPlayer()).getPlayerName() == player.getPlayerName(), "setPlayer postcondition failure");
}

void Board::addEntity(Entity& entity){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling addEntity");
	ENSURE(entity.properlyInitialized(), 
		"Entity wasn't initialized when calling addEntity");
	fEntitiesPointer.push_back(&entity);
	ENSURE(getEntities().back() == &entity, "addEntity postcondition failure");
}

void Board::setHeight(int height){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setHeight");	
	fBoardHeight = height;
	ENSURE((getHeight() == height), "setHeight postcondition failure");
}

void Board::setWidth(int width){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setWidth");
	fBoardWidth = width;
	ENSURE((getWidth() == width), "setWidth postcondition failure");	
}

void Board::setActions(vector<pair<pair<string, string>, string> > actions){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling setActions");
	fActions = actions;
	ENSURE((getActions() == actions), "setWidth postcondition failure");	
}

void Board::generateBoard(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling generateBoard");	
	
	// Clear the previous board (If there is one).
	fBoard.clear();

	// Generating empty board.
	for(int col = 0; col < fBoardWidth; col++){
		vector<vector<Entity*> > temporary;
		for(int row = 0; row < fBoardHeight; row++){
			vector<Entity*> emptyTile;
			emptyTile.push_back(NULL);
			temporary.push_back(emptyTile);
		}
		fBoard.push_back(temporary);
	}

	// Generating Entities on board.
	for(unsigned int index = 0; index < fEntitiesPointer.size(); index++){
		Entity* entityPointer = fEntitiesPointer[index];
		int entityX = entityPointer->getX();
		int entityY = entityPointer->getY();
		if(fBoard[entityX][entityY][0] != NULL)
			cout << "Error: two entities at the same location when generating board." << endl;
		fBoard[entityX][entityY][0] = entityPointer;
	}

	/* Cannot be used when generating empty board.
	ENSURE(getBoard().size() == (unsigned)getWidth() && getBoard()[0].size() == (unsigned)getHeight(), 
		"The board width must be equal to fBoardWidth"\
		"and the board height must be equal to fBoardHeight");
	*/
}

void Board::addAction(pair<pair<string,string>, string> action){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling addAction");
	fActions.push_back(action);
	fActionsRemaining.push_back(action);
}

bool Board::doActions(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling doActions");
	if(isValid()){
		for(vector<pair<pair<string, string>, string> >::iterator actionIterator = fActions.begin();
			actionIterator != fActions.end(); actionIterator++){
			pair<pair<string, string>, string> action = (*actionIterator);
			Entity* entityPointer = getEntity(action.first.first);
			int x = entityPointer->getX();
			int y = entityPointer->getY();
			int oldX = x;
			int oldY = y;
			string direction = action.first.second;
			string actionType = action.second;
			if(actionType == "BEWEGING"){
				if(fBoard[oldX][oldY].back()->getType() == "een knop"){
					string id = fBoard[oldX][oldY].back()->getID();
					for(unsigned int i = 0; i < fEntitiesPointer.size(); i++){
						if(fEntitiesPointer[i]->getID() == id){
							fEntitiesPointer[i]->setClosed(true);
							break;
						}
					} 	
				}

				if(!checkMove(x, y, direction)){
					if(fBoard[oldX][oldY].back()->getType() == "een knop"){				
						string id = fBoard[oldX][oldY].back()->getID();
						for(unsigned int i = 0; i < fEntitiesPointer.size(); i++){
							if(fEntitiesPointer[i]->getID() == id){
								fEntitiesPointer[i]->setClosed(false);
								break;
							}
						} 
					} 	

					cout << "Invalid movement." << endl;
					return false;
				}	
				// If there is a movable object on our path.
				if(containsMovable(x, y)){
					Entity* movableObject = fBoard[x][y].back();
					int temporaryX = x;
					int temporaryY = y;
					if(direction == "OMHOOG")
						temporaryY += 1;
					else if(direction == "OMLAAG")
						temporaryY -= 1;
					else if(direction == "RECHTS")
						temporaryX += 1;
					else if(direction == "LINKS")
						temporaryX -= 1;
					if(fBoard[temporaryX][temporaryY].back() != NULL){
						if((fBoard[temporaryX][temporaryY].back()->getType() == "een monster" or
						fBoard[temporaryX][temporaryY].back()->getType() == "Player")){
							cout << "Invalid movement." << endl;
							return false;	
						}
						else if(fBoard[temporaryX][temporaryY].back()->getType() == "water"){
							deleteEntity(fBoard[x][y].back());
							fBoard[temporaryX][temporaryY][0] = NULL;;
							continue;
						}
						
					}
					fBoard[temporaryX][temporaryY].push_back(movableObject);
					fBoard[x][y].pop_back();
					if(fBoard[x][y].empty())
						fBoard[x][y].push_back(NULL);
					movableObject->setX(temporaryX);
					movableObject->setY(temporaryY);
				}
				// If there is an interactable object on our path.
				if(isWalkable(x, y)){
						if(fBoard[x][y][0] != NULL && fBoard[x][y][0]->getType() == "een doel"){
							cout << "Goal reached, game has ended." << endl;
							return true;
						}
						else if(fBoard[x][y][0] != NULL && fBoard[x][y][0]->getType() == "een knop"){
							string id = fBoard[x][y][0]->getID();
							for(unsigned int i = 0; i < fEntitiesPointer.size(); i++){
								if(fEntitiesPointer[i]->getID() == id){
									fEntitiesPointer[i]->setClosed(false);
									break;
								}
							} 
						}
				}

				if(entityPointer->getType() == "een monster"){
					if(fBoard[x][y][0] != NULL && fBoard[x][y][0]->getType() == "water"){
						deleteEntity(entityPointer);
						cout << "A monster has drowned in water." << endl;
					}
					else if(fPlayerPointer->getX() == x && fPlayerPointer->getY() == y){
						cout << "A monster has killed you. GAME OVER" << endl;	
						return true;
					}
				}
				else{
					if(fBoard[x][y][0] != NULL && fBoard[x][y][0]->getType() == "water"){
						cout << "You have drowned in water. GAME OVER" << endl;
						return true;
					}
				}
				fBoard[oldX][oldY].pop_back();
				if(fBoard[oldX][oldY].empty())
					fBoard[oldX][oldY].push_back(NULL);

				entityPointer->setX(x);
				entityPointer->setY(y);
				if(fBoard[x][y][0] == NULL)
					fBoard[x][y][0] = entityPointer;
				else
					fBoard[x][y].push_back(entityPointer);
				fActionsRemaining.erase(fActionsRemaining.begin());
			}
			else{
				if(!checkMove(x, y, direction)){
					if(fBoard[x][y].back()->getType() == "een monster"){
						deleteEntity(fBoard[x][y].back());
						cout << "A monster has been killed" << endl;
					}
				}
			}
		}
	}
	return true;
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
	Player* result = fPlayerPointer;
	return result;
}

int Board::getHeight(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getHeight");	
	int result = fBoardHeight;
	ENSURE(result >= 0, 
		"Board height must be greater or equal than 0 when calling getHeight");
	return result;
}

int Board::getWidth(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getWidth");	
	int result = fBoardWidth;
	ENSURE(result >= 0, 
		"Board width must be greater or equal than 0 when calling getWidth");
	return result;
}


vector<pair<pair<string, string>, string> > Board::getActions() {
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getActions");
	vector<pair<pair<string, string>, string> > actions = fActions;
	
	return actions; 
}

vector<vector<vector<Entity*> > > Board::getBoard(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getBoard");
	vector<vector<vector<Entity*> > > result = fBoard;
	ENSURE(result.size() == (unsigned)getWidth() && result[0].size() == (unsigned)getHeight(), 
		"The board width must be equal to getWidth"\
		"and the board height must be equal to getHeight");
	return result;
}


bool Board::contains(string id) {
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling contains");	
	for(vector<Entity*>::iterator entityPointer = fEntitiesPointer.begin();
		entityPointer != fEntitiesPointer.end(); entityPointer++) {
		if((*entityPointer)->getID() == id) {
			return true;
		}
	}
	return false;
}

bool Board::isValid(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling isValid");	
	if(fBoardWidth > 0 && fBoardHeight > 0){
		if(fPlayerPointer != NULL && fBoardName != ""){
			if(fBoard.size() ==  (unsigned)fBoardWidth && fBoard[0].size() ==  (unsigned)fBoardHeight){
				if(fEntitiesPointer.size() <=  (unsigned)(fBoardWidth * fBoardHeight)){
					return true;
				}
			}
		}
	}
	return false;
}

vector<Entity*> Board::getEntities(){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getEntities");
	vector<Entity*> result = fEntitiesPointer;
	return result;
}

Entity* Board::getEntity(string id){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling getEntity()");	
	for(vector<Entity*>::iterator entityPointer = fEntitiesPointer.begin();
		entityPointer != fEntitiesPointer.end(); entityPointer++) {
		if((*entityPointer)->getID() == id) {
			return (*entityPointer);
		}
	}
	return NULL;
}

bool Board::writeOn(ostringstream& onStream) {
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling writeOn");
	onStream << "Het huidige speelveld is " << fBoardName << ":" << endl;
	onStream << "Eigenschappen van dit veld:" << endl;
	onStream << "-Breedte " << fBoardWidth << endl;
	onStream << "-Lengte " << fBoardHeight << endl << endl;

	if(fPlayerPointer == NULL)
		return false;
	onStream << "Speler " << fPlayerPointer->getPlayerName() << " bevindt zich in dit speelveld op positie (" 
		<< fPlayerPointer->getX() << "," << fPlayerPointer->getY() << ")." << endl << endl; 


	for(vector<Entity*>::iterator entityIterator = fEntitiesPointer.begin(); 
		entityIterator != fEntitiesPointer.end(); entityIterator++){
		Entity* entityPointer = *entityIterator;
		if(entityPointer == NULL)
			return false;

		string type = entityPointer->getType();
		if(type != "muur" && type != "Player"){
			if(type == "een knop"){
				onStream << "Er bevindt zich een knop (gelinkt aan poort " 
					<< entityPointer->getID() << ") op positie (" 
					<< entityPointer->getX() << "," << entityPointer->getY() << ")." << endl << endl;
			}
			else if(type == "een poort"){
				onStream << "Er bevindt zich een poort (met id " 
					<< entityPointer->getID() << ") op positie (" 
					<< entityPointer->getX() << "," << entityPointer->getY() << ")." << endl << endl;
			}
			else{
				onStream << "Er bevindt zich " << type  << " op positie (" 
					<< entityPointer->getX() << "," << entityPointer->getY() << ")." << endl << endl;
			}
		}
	}

 	ENSURE(onStream != "", 
		"onStream must not be empty after calling writeOn.");
	return true;
}


bool Board::writeActions(ostringstream& onStream){
	REQUIRE(this->properlyInitialized(),
		"Board wasn't initialized when calling writeActions");
	if(fActionsRemaining.empty()){
		onStream << "Er zijn geen acties." << endl;
		return true;
	}
	for(vector<pair<pair<string,string>,string> >::iterator actionIterator = fActionsRemaining.begin();
		actionIterator != fActionsRemaining.end(); actionIterator++){
		if((*actionIterator).first.first != fPlayerPointer->getPlayerName()){
			(onStream << "Monster " << (*actionIterator).first.first 
			<< " zal volgende beweging nog uitvoeren: " << endl);
			onStream << (*actionIterator).first.second << endl;
		}
		else {
			if((*actionIterator).second == "AANVAL"){
				(onStream << "Speler " << fPlayerPointer->getPlayerName() 
				<< " zal volgende aanval nog uitvoeren: " << endl);
				onStream << (*actionIterator).first.second << endl;				
			}
			else{
				(onStream << "Speler " << fPlayerPointer->getPlayerName() 
				<< " zal volgende beweging nog uitvoeren: " << endl);
				onStream << (*actionIterator).first.second << endl;	
			}
		}
	}
	return true;
}

bool Board::project(ostringstream& onStream){
	REQUIRE(this->properlyInitialized(), 
		"Board wasn't initialized when calling project");
	if(!isValid())
		return false;

	for(int row = fBoardHeight-1; row > -1; row--){
		for(int col = 0; col < fBoardWidth; col++){
			if(fBoard[col][row].back() == NULL){
				onStream << " ";
				continue;
			}
			Entity* entity = fBoard[col][row].back();
			string entityType = entity->getType();
			if(entityType == "muur")
				onStream << "#";
			else if(entityType == "Player")
				onStream << "Y";
			else if(entityType == "een doel")
				onStream << "X";
			else if(entityType == "een knop")
				onStream << ".";
			else if(entityType == "een ton")
				onStream << "O";
			else if(entityType == "een poort"){
				if(entity->isClosed())
					onStream << "=";
				else
					onStream << " ";				
			}
			else if(entityType == "een monster")
				onStream << "&";
			else if(entityType == "water")
				onStream << "~";
		}
		onStream << endl;
	}
	return true;
}
