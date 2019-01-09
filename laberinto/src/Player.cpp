#include "Player.h"

Player::Player()
{
	pos.x = 0;
	pos.y = 0;
	actualCell = NULL;
}

void Player::Move(const float& sppedx, const float& speedy)
{
	
	pos.x += sppedx;
	pos.y += speedy;

}



void Player::SetPlayer(const float& x, const float& y, const float& s)
{
	pos.x = x;
	pos.y = y;
	size = s;
	
}

void Player::drawObject()
{
	if (isdraw)
	{
		ofSetColor(0,0,255);
		ofDrawCircle(pos.x, pos.y, size);
	}
		
}

void Player::drawIa()
{
	if (isdraw)
	{
		ofSetColor(255, 0, 0);
		ofDrawCircle(pos.x, pos.y, size);
	}
}

void Player::draw()
{
	if (isdraw)
	{
		ofSetColor(255, 255, 255);
		ofDrawCircle(pos.x, pos.y, size);
	}
}

void Player::SetActualCell(Cell * cell)
{
	actualCell = cell;
}

ofVec2f Player::getPos()
{
	return pos;
}

void Player::SetPos(ofVec3f p)
{
	pos.x = p.x;
	pos.y = p.y;
}

void Player::MoveToNeihborCell(std::vector<Cell*>& cell)
{
	Cell* tempCell=NULL;
	for (int i = 0; i < cell.size(); i++)
	{
		if (cell[i]->shortes&&i!=0)
		{
			tempCell = cell[i];
			break;
		}
	}
	if (tempCell != NULL) {
		float speed = 0.5;
		int indexActualCell = actualCell->index;
		int indexTemp = tempCell->index;
		if (actualCell->North != NULL)
		{
			if (actualCell->North->index == indexTemp) {
				pos.y -= speed;
				if (pos.y <= tempCell->center.y)
				{
					tempCell->shortes = false;
					pos.y = tempCell->center.y;
					actualCell = tempCell;
				}
			}

		}
		if (actualCell->Soth != NULL)
		{
			if (actualCell->Soth->index == indexTemp) {
				pos.y += speed;
				if (pos.y >= tempCell->center.y)
				{
					tempCell->shortes = false;
					pos.y = tempCell->center.y;
					actualCell = tempCell;
				}
			}
		}
		if (actualCell->East != NULL)
		{
			if (actualCell->East->index == indexTemp) {
				pos.x += speed;
				if (pos.x >= tempCell->center.x)
				{
					tempCell->shortes = false;
					pos.x = tempCell->center.x;
					actualCell = tempCell;
				}
			}
		}
		if (actualCell->West != NULL)
		{
			if (actualCell->West->index == indexTemp) {
				pos.x -= speed;
				if (pos.x <= tempCell->center.x)
				{
					tempCell->shortes = false;
					pos.x = tempCell->center.x;
					actualCell = tempCell;
				}
			}
		}
	}
	else
	 {
		 actualCell = cell.back();
	 }
}



