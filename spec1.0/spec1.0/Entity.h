#include <utility>
#include "Board.h"

using namespace std;

class Entity{
protected:
	bool fIsObstacle;
	string fType;
	int fX;
	int fY;

public:
	// Default Constructor
	Entity(int x, int y, bool isObstacle, bool isMovable, string entityType);

	void setObstacle(bool isObstacle);
	void setMovable(bool isMovable);
	void setType(string type);
	void setX(int x);
	void setY(int y);

	bool isObstacle();
	bool isMovable();
	string getType();
	int getX();
	int getY();
}


class Player : public Entity{
private:
	string fPlayerName;
public:
	Player(int x, int y, string name);
}
