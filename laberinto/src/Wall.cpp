#include "Wall.h"
#include "ofGraphics.h"
Wall::Wall()
{
	p1.x = 100;
	p1.y = 100;
	p1.z = 0;

	p2.x = 100;
	p2.y = 100;
	p2.z = 0;
}

void Wall::draw()
{
	ofDrawLine(p1, p2);
}

Wall::Wall(float x, float y,float x2, float y2)
{
	p1.x = x;
	p1.y = y;
	p1.z = 0;

	p2.x = x2;
	p2.y = y2;
	p2.z = 0;
}
