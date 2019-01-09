#ifndef WALL_H
#define WALL_H
#include "ofMath.h"

class Wall
{
public:
	ofVec3f p1, p2;
	Wall();
	void draw();
	Wall(float x, float y, float x2, float y2);
};
#endif
