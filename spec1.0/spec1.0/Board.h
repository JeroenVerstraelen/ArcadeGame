#ifndef Base3D_CC
#define Base3D_CC

using namespace std;

class Board{
private:
	string fBoardName;
	int fBoardLength;
	int fBoardWidth
	vector<Entity*> fEntitiesPointer;
	Player fPlayer;
	vector<vector<Entity*> > fBoard;
public:
	Board(int width, int length, string name, Player player, 
		vector<Entity*> boardEntities);

	void setName(string boardName);
	void setPlayer(Player& player);
	void addEntity(Entity* entity);
	string getBoardName();
	Player getPlayer();
	vector<Entity> getEntities();
};


#endif
