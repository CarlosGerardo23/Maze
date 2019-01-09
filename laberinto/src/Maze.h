#ifndef MAZE_H
#define MAZE_H

#include "ofMath.h"
#include <vector>
#include "Cell.h"
#include "Player.h"

class Maze
{
public:
	Maze();
	Maze(ofVec3f pos, float size, float width, float height);
	float offset, w, h;
	ofVec3f position;
	int size;
	std::vector<Cell*> maze;
	void BuildMaze();
	void SetPlayer();
	void SetIa();
	void SetGoal();
	void BuildPath(int key);
	bool randNumber();
	void draw();
	void MovePlayer(int key);
	void SelectCell(int x, int y, int button);
	/*void CellGame();*/
	void MoveIa();
private:

	Player player;
	Player ia;
	Player object;
	std::vector<Cell*>BackT;
	std::vector<Cell*>Path;
	std::vector<Cell*> shortestPath;
	void BinaryTree();
	void SideWinder();
	void SetNeighbor();
	void BackTracker();
	void PathBackTracker(Cell* selectedCell);
	int GetNeighborID(Cell* cell, Cell* Neighbor);
	Cell* ChoseNeighbor(Cell* cell);
	int North = 0, South = 1, East = 2, West = 3;

	//PathFinding
	int lasCell;
	void SetPathIndex(Cell* cell, int pindex);
	void ShortestPath(Cell* cell);
	
	Cell* GetNextNeiPath(Cell* cell);
	bool updateia = false;
	void ChangueCellPath();
	void setShortestpathNei();
};

#endif
