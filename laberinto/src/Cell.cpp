#include "Cell.h"

Cell::Cell()
{
	pos.x = 100;
	pos.y = 100;
	pos.z = 0;
	width = 100;
	height = 100;
	isPoint = false;
	neighbor = false;
	center.x = 50;
	center.y = 50;

}

Cell::Cell(ofVec3f position)
{
	pos = position;
	width = 100;
	height = 100;
	isPoint = false;
	neighbor = false;
	center.x = position.x+width/2;
	center.y = position.y+height/2;
	center.z = position.z;

}

Cell::Cell(ofVec3f position, float w, float h)
{
	pos = position;
	width = w;
	height = h;
	isPoint = false;
	neighbor = false;
	center.x = position.x + width / 2;
	center.y = position.y + height / 2;
	center.z = position.z;


}

void Cell::draw()
{
	if(north)
	walls[0]->draw();
	if(south)
	walls[1]->draw();
	if(west)
	walls[3]->draw();
	if(east)
	walls[2]->draw();

	drawIndex();
	/*walls[0]->draw();
	walls[1]->draw();*/
	//walls[2]->draw();
	//walls[3]->draw();

}

void Cell::buildWall(int direction)
{
	
	switch (direction)
	{
	case NORTH:
		walls.push_back(new Wall(pos.x, pos.y, pos.x + width, pos.y));
		north = true;
		break;
	case SOUTH:
		walls.push_back(new Wall(pos.x, pos.y + height, pos.x + width, pos.y + height));
		south = true;
		break;
	case EAST:
		walls.push_back(new Wall(pos.x + width, pos.y, pos.x + width, pos.y + height));
		west = true;
		break;
	case WEST:
		walls.push_back(new Wall(pos.x, pos.y, pos.x, pos.y + height));
		east = true;
		break;
	default:

		break;
	}
	
	
	
	

	//walls[NORTH] = new Wall(pos.x,pos.y,pos.x+width,pos.y);
	//walls[SOUTH] = new Wall(pos.x, pos.y+height, pos.x + width, pos.y+height);
	//walls[EAST] = new Wall(pos.x+width, pos.y, pos.x + width, pos.y+height);
	//walls[WEST] = new Wall(pos.x, pos.y, pos.x, pos.y+height);

}

void Cell::destroyWall(int direction)
{
	switch (direction)
	{
	case NORTH:
		delete walls[0];
		north = false;
		break;
	case SOUTH:
		delete walls[1];		
		south = false;
		break;
	case WEST:
		delete walls[3];		
		west = false;
		break;
	case EAST:
		delete walls[2];		
		east = false;
		break;
	default:

		break;
	}
}

void Cell::getNeighbor(Cell * n, Cell * s, Cell * e, Cell * w)
{
	this->North = n;
	this->Soth = s;
	this->East = e;
	this->West = w;
}

void Cell::destroyNeighborWall(int direction)
{
	switch (direction)
	{
	case NORTH:
		if (this->North != NULL)
		{
			delete walls[0];

			this->North->destroyWall(SOUTH);
			north = false;
		}
		
		break;
	case SOUTH:
		
		if (this->Soth != NULL)
		{
			delete walls[1];
			this->Soth->destroyWall(NORTH);
			south = false;
		}
		break;
	case WEST:
		
		if (this->West != NULL)
		{
			delete walls[3];

			this->West->destroyWall(EAST);
			west = false;
		}
		break;
	case EAST:
		
		if (this->East != NULL)
		{
			delete walls[2];
			this->East->destroyWall(WEST);
			east = false;
		}
		break;
	default:

		break;
	}
}

void Cell::drawIndex()
{
	if(flagP)
	ofDrawBitmapString(ofToString(pIndex), center.x, center.y);
}


