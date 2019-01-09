#ifndef PLAYER_H
#define PLAYER_H

#include "ofMath.h"
#include "ofGraphics.h"
#include "Cell.h"


class Player
{

public:
	Player();
	void Move(const float& sppedx, const float& speedy);
	
	void SetPlayer(const float& x, const float& y, const float& s);
	void drawObject();
	void drawIa();
	

	void draw();
	void SetActualCell(Cell* cell);
	Cell* actualCell;
	ofVec2f getPos();
	void SetPos(ofVec3f p);
	bool isdraw = false;
	void MoveToNeihborCell(std::vector<Cell*>& cell);
private:
	ofVec2f pos;
	float size;


};
#endif // !PLAYER_H
