#include <utility>
#include "Board.h"

using namespace std;

class Entity{
protected:
	bool isObstacle;

public:
	// Default Constructor
	Entity();

	void setObstacle(bool obstacle);

	bool isObstacle();
}


class Player : public Entity{




}
