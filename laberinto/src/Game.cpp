#include "Game.h"

Game::Game(ofVec3f pos)
{
	position = pos;
	width = 40;
	height = 40;
}

void Game::Init(bool flag)
{
	if (!flag)
	{
		maze = new Maze(position, size, width, height);

		maze->BuildMaze();
		maze->SetPlayer();
		maze->SetGoal();
		maze->SetIa();
	}
	
}

void Game::Draw()
{
	maze->draw();
}

void Game::Path(int key)
{
	if (key == 'r')
	{
		maze = new Maze(position, size, width, height);
	}else
	maze->BuildPath(key);
}

void Game::GameStart()
{
	//maze->CellGame();
	iaMove = true;
}

void Game::MoveIa()
{
	if (iaMove)
		maze->MoveIa();
}




