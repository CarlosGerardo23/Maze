#ifndef GAME_H
#define GAME_H

#include "Maze.h"
#include "Player.h"

class Game
{
public:
	Game(ofVec3f pos);
	void Init(bool flag);
	int size;
	void Draw();
	void Path(int key);
	void GameStart();
	void MoveIa();
private:
	bool iaMove=false;
	int width;
	int height;
	ofVec3f position;
	Maze* maze;
	

};

#endif

