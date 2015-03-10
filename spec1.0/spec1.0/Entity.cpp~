using namespace std;

Entity::Entity(int x, int y, bool obstacle, bool movable, string type){
	fX = x;
	fY = y;
	fIsObstacle = obstacle;
	fIsMoveable = movable;
	fEntityType = type;
}


void Entity::setObstacle(bool isObstacle){
	fIsObstacle = isObstacle;
}


void Entity::setMovable(bool isMoveable){
	fIsMoveable = isMoveable;
}

void Entity::setType(string type){
	fEntityType = type;
}

void Entity::setX(int x){
	int fX = x;
}

void Entity::setY(int y){
	int fY = y;
}


bool Entity::isObstacle(){
	return fIsObstacle;
}

bool Entity::isMovable(){
	return fIsMoveable;
}

int Entity::getX(){
	return fX;
}

int Entity::getY(){
	return fY;
}



Player::Player(int x, int y, string name){
	fX = x;
	fY = y;
	fEntityType = "player";
	fPlayerName = name;
}
