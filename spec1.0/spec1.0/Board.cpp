using namespace std;

Board::Board(int boardWidth, int boardLength, string name, Player player, 
		vector<Entity*> entities){
	for(int row = 0; row < boardLength; row++){
		vector<Entity*> temporary;
		for(int col = 0; col < boardWidth; col++){
			temporary.push_back(NULL);
		}
		fBoard.push_back(temporary);
	}

	fBoardWidth = boardWidth;
	fBoardLength = boardLength;
	fBoardName = name;
	fPlayer = player;
	fEntitiesPointer = entities;

	for(int index = 0; index < fEntitiesPointer.size(); index++){
		Entity* entityPointer = fEntitiesPointer[index];
		int entityX = entityPointer->getX();
		int entityY = entityPointer->getY();
		board[entityX][entityY] = entityPointer;
	}
}

void Board::setName(string boardName){
	fBoardName = boardName;
}

void Board::setPlayer(Player& player){
	fPlayer = player;
}

void Board::addEntity(Entity* entityPointer){
	fEntitiesPointer.push_back(entityPointer);
}


string Board::getBoardName(){
	return fBoardName;
}

Player Board::getPlayer(){
	return fPlayer;
}

vector<Entity> Board::getEntities(){
	return fEntityPointer;
}
