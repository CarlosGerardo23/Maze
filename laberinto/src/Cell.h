#ifndef CELL_H
#define CELL_H
#include "ofMath.h"
#include "ofGraphics.h"
#include "Wall.h"
#include "ofMain.h"
#include <vector>
#include <string>

class Cell 
{
public:
	enum Direction
	{
		NORTH,
		SOUTH,
		EAST,
		WEST
	};

	ofVec3f pos,center;
	bool north=false, south=false, east=false, west=false;
	bool isPoint, neighbor, iamove = false;;
	float width, height;
	std::vector<Wall*>walls;
	int index;
	Cell* North;
	Cell* East;
	Cell* West;
	Cell* Soth;
	bool Neighbors[4]{ false,false,false,false };
	Cell();
	Cell(ofVec3f position);
	Cell(ofVec3f position, float w, float h);
	void draw();
	void buildWall(int direction);
	void destroyWall(int direction);
	void getNeighbor(Cell* n, Cell* s, Cell* e, Cell* w);
	void destroyNeighborWall(int direction);
	bool flagP = false, visitedP=false;
	int pIndex;
	bool shortes=false;
private:
	void drawIndex();

	
};


#endif
