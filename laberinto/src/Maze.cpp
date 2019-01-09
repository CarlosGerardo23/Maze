
#include "Maze.h"

#include "ofMath.h"

#include <iostream>
#include "ofMain.h"


Maze::Maze()
{
}


Maze::Maze(ofVec3f pos, float size, float width, float height)
{
	position = pos;
	w = width;
	h = height;
	this->size = size;
	offset = w;
}


void Maze::BuildMaze()
{
	int inicialX = 0;
	inicialX = position.x;
	for (int i = 0; i < size*size; i++)
	{
		int flag = i%size;
		int end = size - 1;
		Cell* c = new Cell(position, w, h);
		c->buildWall(0);
		c->buildWall(1);
		c->buildWall(2);
		c->buildWall(3);
		c->index = i;
		//std::cerr << flag<< std::endl;
		maze.push_back(c);
		if (flag == end)
		{
			position.x =inicialX;
			position.y += offset;
		}
		else
		{		
			position.x += offset;
		}
	}
	SetNeighbor();

	player.SetPlayer(maze[0]->center.x, maze[0]->center.y, 10);
	player.SetActualCell(maze[0]);
	player.isdraw = true;
}

void Maze::SetPlayer()
{
	player.SetPlayer(maze[0]->center.x, maze[0]->center.y, 10);
	player.SetActualCell(maze[0]);
	player.isdraw = true;
}

void Maze::SetIa()
{
	ia.SetPlayer(maze.back()->center.x, maze.back()->center.y, 10);
	ia.SetActualCell(maze.back());
	ia.isdraw = true;
}

void Maze::SetGoal()
{
	int in = maze.size() / 2;
	object.SetPlayer(maze[in]->center.x, maze[in]->center.y, 10);
	object.SetActualCell(maze[in]);
	object.isdraw = true;
}




void Maze::BuildPath(int key)
{
	
	if (key == 'b')
		BinaryTree();
	else if (key == 'y')
		SideWinder();
	else if (key == 't')
		BackTracker();

		
}


bool Maze::randNumber()
{

	if (ofRandom(10) <= 5)
		return true;
	else
		return false;
	
}


void Maze::draw()
{
	ofColor c = (0, 0, 1);
	ofColor a = (1, 0, 0);
	int flag = size*size;
	for (int i = 0; i < flag; i++)
	{
		maze[i]->draw();
		
	}
	player.draw();
	ia.drawIa();
	object.drawObject();

}

void Maze::MovePlayer(int key)
{


	//Arreglar el movimiento del jugador y de la ia utilizando update cehcar pong 
	if (key == 'w')
	{
		if (player.actualCell->North != NULL&&!player.actualCell->north)
		{
			player.SetActualCell(player.actualCell->North);
			player.SetPos(player.actualCell->center);
		}

	}
	if (key == 's')
	{
		if (player.actualCell->Soth != NULL&&!player.actualCell->south)
		{
			player.SetActualCell(player.actualCell->Soth);
			player.SetPos(player.actualCell->center);
		}
	}
	if (key == 'd')
	{
		if (player.actualCell->East != NULL&&!player.actualCell->east)
		{
			player.SetActualCell(player.actualCell->East);
			player.SetPos(player.actualCell->center);
		}
	}
	if (key == 'a')
	{
		if (player.actualCell->West != NULL&&!player.actualCell->west)
		{
			player.SetActualCell(player.actualCell->West);
			player.SetPos(player.actualCell->center);
		}
	}
	if (key == 'm')
	{
		updateia = true;
	}
	if (key == 'k')
	{
		for (int i = 0; i < maze.size(); i++)
		{
			maze[i]->flagP = false;
		}
	}
	if (key == 'g')
	{
		int msize = maze.size() / 2;
		object.SetPlayer(maze[msize]->center.x, maze[msize]->center.y, 10);
		object.SetActualCell(maze[msize]);
		object.isdraw = true;
		ia.SetPlayer(maze.back()->center.x, maze.back()->center.y, 10);
		ia.SetActualCell(maze.back());
		ia.isdraw = true;
		maze[msize]->visitedP = true;
		SetPathIndex(maze[msize], 0);
		shortestPath.push_back(ia.actualCell);
		ShortestPath(ia.actualCell);
		setShortestpathNei();


	}
	
}

void Maze::SelectCell(int x, int y, int button)
{
	if (button == OF_MOUSE_BUTTON_1)
	{
		for (int i = 0; i < maze.size(); i++)
		{
			if (x >= maze[i]->pos.x&&x <= maze[i]->pos.x + maze[i]->width)
			{
				if (y >= maze[i]->pos.y&&y <= maze[i]->pos.y + maze[i]->height)
				{
					
					std::cerr << "Tu celda de inicio es : " << maze[i]->index << std::endl;
					maze[i]->visitedP = true;
					SetPathIndex(maze[i],0);
					Path.clear();
					
				}
			}
		}
	}
	
	if (button == OF_MOUSE_BUTTON_3)
	{
		for (int i = 0; i < maze.size(); i++)
		{
			if (x >= maze[i]->pos.x&&x <= maze[i]->pos.x + maze[i]->width)
			{
				if (y >= maze[i]->pos.y&&y <= maze[i]->pos.y + maze[i]->height)
				{

					std::cerr << "Tu celda de final es : " << maze[i]->index << std::endl;
					maze[i]->visitedP = true;
					
					ia.SetPlayer(maze[i]->center.x, maze[i]->center.y, 10);
					ia.SetActualCell(maze[i]);
					ia.isdraw = true;
					shortestPath.push_back(maze[i]);
					ShortestPath(maze[i]);
					setShortestpathNei();
					

				}
			}
		}
	}
	
}

//void Maze::CellGame()
//{
//	Path.push_back(object.actualCell);
//	SetPathIndex(object.actualCell, 0);
//	shortestPath.push_back(ia.actualCell);
//	setShortestpathNei();
//	
//		for (int i = 0; i < maze.size(); i++)
//		{
//			maze[i]->flagP = !maze[i]->flagP;
//		}
//	
//
//}


void Maze::SetNeighbor()
{
	for (int i = 0; i < size*size; i ++)
	{
		if (i == 0)
		{
			maze[i]->getNeighbor(NULL, maze[i + size], maze[i + 1], NULL);
			maze[i]->neighbor = true;
		}
		else if (i == size - 1)
		{
			maze[i]->getNeighbor(NULL, maze[i + size], NULL, maze[i - 1]);
			maze[i]->neighbor = true;
		}
		else if (i%size == size - 1&& i!=(size*size)-1)
		{
			maze[i]->getNeighbor(maze[i - size], maze[i + size], NULL, maze[i-1]);
			maze[i]->neighbor = true;
		}
		else if (i%size == 0&& i!=(size*size)-size)
		{
			maze[i]->getNeighbor(maze[i - size], maze[i + size], maze[i + 1], NULL);
			maze[i]->neighbor = true;
		}
		else if (i == (size*size) - size)
		{
			maze[i]->getNeighbor(maze[i - size], NULL, maze[i + 1], NULL);
			maze[i]->neighbor = true;
		}
		
		
		else if (i == (size*size)-1)
		{
			maze[i]->getNeighbor(maze[i - size],NULL, NULL, maze[i - 1]);
			maze[i]->neighbor = true;
		}
		else if(i<size&&!maze[i]->neighbor)
		{
			maze[i]->getNeighbor(NULL, maze[i + size], maze[i+1], maze[i - 1]);
			maze[i]->neighbor = true;
		}
		else if (i < (size*size) - size && !maze[i]->neighbor)
		{
			maze[i]->getNeighbor(maze[i - size], maze[i+size], maze[i + 1], maze[i - 1]);
			maze[i]->neighbor = true;
		}
		else if(!maze[i]->neighbor)
		{
			maze[i]->getNeighbor(maze[i-size], NULL, maze[i + 1], maze[i - 1]);
			maze[i]->neighbor = true;
		}
		maze[i]->Neighbors[0] = true;
		maze[i]->Neighbors[1] = true;
		maze[i]->Neighbors[2] = true;
		maze[i]->Neighbors[3] = true;
		if (maze[i]->North == NULL)
			maze[i]->Neighbors[North] = false;
		if (maze[i]->Soth == NULL)
			maze[i]->Neighbors[South] = false;
		if (maze[i]->East == NULL)
			maze[i]->Neighbors[East] = false;
		if (maze[i]->West == NULL)
			maze[i]->Neighbors[West] = false;
	}
	
}

void Maze::BinaryTree()
{
	
	int flag = size*size;
	int point = flag - size;

	while (point < flag - 1)
	{

		if (randNumber())
		{
			maze[point]->destroyWall(North);
			maze[point - size]->destroyWall(South);
		}
		else
		{
			maze[point]->destroyWall(East);
			maze[point + 1]->destroyWall(West);

		}

		maze[point]->isPoint = true;
		point++;
	}
	while (point != size - 1)
	{
		maze[point]->destroyWall(North);
		maze[point - size]->destroyWall(South);
		maze[point]->isPoint = true;
		point -= size;
	}
	point = 0;
	while (point < size - 1)
	{
		maze[point]->destroyWall(East);
		maze[point + 1]->destroyWall(West);
		maze[point]->isPoint = true;
		point += 1;
	}
	maze[size - 1]->isPoint = true;


	for (int i = 0; i < size*size; i++)
	{
		if (maze[i]->isPoint)
			continue;
		if (randNumber())
		{
			maze[i]->destroyWall(North);
			maze[i - size]->destroyWall(South);
		}
		else
		{
			maze[i]->destroyWall(East);
			maze[i + 1]->destroyWall(West);

		}

	}
}
void Maze::SideWinder()
{
	for (int i = 0; i < size-1; i++)
	{
		maze[i]->destroyWall(East);
		maze[i + 1]->destroyWall(West);
		maze[i]->isPoint = true;
	}
	maze[size - 1]->isPoint = true;
	std::vector<Cell*> tempCell;
	int cont = 0;
	
	for (int i = 0; i < size*size; i++)
	{
		if (maze[i]->isPoint)
			continue;
		else 
		{
			maze[i]->index = i;
			maze[i]->isPoint = true;
			tempCell.push_back(maze[i]);
			
			if (i%size == size - 1)
			{
				if (tempCell.size() > 1)
				{
					std::random_shuffle(tempCell.begin(), tempCell.end());
					tempCell[0]->destroyWall(North);
					maze[tempCell[0]->index-size]->destroyWall(South);
					tempCell.clear();
				}
				else
				{
					maze[i]->destroyWall(North);
					maze[i - size]->destroyWall(South);
					tempCell.clear();
				}
			}
			else
			{
				if (randNumber())
				{
					maze[i]->destroyWall(East);
					maze[i + 1]->destroyWall(West);
				}
				else 
				{
					if (tempCell.size()> 1)
					{
						std::random_shuffle(tempCell.begin(), tempCell.end());
						tempCell[0]->destroyWall(North);
						maze[tempCell[0]->index - size]->destroyWall(South);
					}
					else
					{
						tempCell[0]->destroyWall(North);
						maze[i - size]->destroyWall(South);
					}
						
					tempCell.clear();
				}
				
			}
			
		}
	}

}
void Maze::BackTracker()
{
	Cell* cellSelected;
	Cell* neighborSelected;
	for (int i = 0; i < maze.size(); i++)
		maze[i]->index = i;
	cellSelected = maze[0];
	BackT.push_back(cellSelected);
	PathBackTracker(cellSelected);


}

void Maze::PathBackTracker(Cell * selectedCell)
{
	int debugIndex = selectedCell->index;
	Cell* tempN;
	int idNeighbor;
	tempN = ChoseNeighbor(selectedCell);
	int debugNeihbor;
	if (tempN != NULL)
	{
		debugNeihbor = tempN->index;
		idNeighbor = GetNeighborID(selectedCell, tempN);
		selectedCell->destroyNeighborWall(idNeighbor);
		BackT.push_back(tempN);
		PathBackTracker(tempN);
	}
	else if(selectedCell->neighbor)
	{
		PathBackTracker(selectedCell);	
	}
	else if(BackT.size()>1)
	{
		BackT.pop_back();
		PathBackTracker(BackT.back());
	}
	
}

int Maze::GetNeighborID(Cell * cell, Cell * Neighbor)
{
	if (Neighbor == cell->North)
		return North;
	else if (Neighbor == cell->Soth)
		return South;
	else if (Neighbor == cell->East)
		return East;
	else if (Neighbor == cell->West)
		return West;
	else
		return -1;
}

Cell* Maze::ChoseNeighbor(Cell * cell)
{
	int lastCell;
	std::vector<Cell*> tempNeighbors;
	if (cell->Neighbors[0])
	{
		tempNeighbors.push_back(cell->North);
		cell->North->Neighbors[South] = false;
		lastCell = North;
	}
	else if(cell->North!=NULL)
	{
		cell->North->Neighbors[South] = false;
	}
	if (cell->Neighbors[1])
	{
		tempNeighbors.push_back(cell->Soth);
		cell->Soth->Neighbors[North] = false;
		lastCell = South;
	}
	else if (cell->Soth != NULL)
	{
		cell->Soth->Neighbors[North] = false;
	}
	if (cell->Neighbors[2])
	{
		tempNeighbors.push_back(cell->East);
		cell->East->Neighbors[West] = false;
		lastCell = East;
	}
	else if (cell->East != NULL)
	{
		cell->East->Neighbors[West] = false;
	}
		
	if (cell->Neighbors[3])
	{
		tempNeighbors.push_back(cell->West);
		cell->West->Neighbors[East] = false;
		lastCell = West;
	}	
	else if (cell->West != NULL)
	{
		cell->West->Neighbors[East] = false;
	}
	if (tempNeighbors.size() > 1)
	{
		//El problema es que una vez que se selecciona una casilla debe estar inaccesible para todos sus vecinos porque ya fue visitada
		std::random_shuffle(tempNeighbors.begin(), tempNeighbors.end());
		int debug=tempNeighbors[0]->index;
		if (tempNeighbors[0] == cell->North&&tempNeighbors[0]!=NULL)
		{
			cell->Neighbors[North] = false;
			
			tempNeighbors[0]->Neighbors[South] = false;
		}	
		else if (tempNeighbors[0] == cell->Soth&&tempNeighbors[0] != NULL)
		{
			cell->Neighbors[South] = false;
			tempNeighbors[0]->Neighbors[North] = false;
		}		
		else if (tempNeighbors[0] == cell->East&&tempNeighbors[0] != NULL)
		{
			cell->Neighbors[East] = false;
			tempNeighbors[0]->Neighbors[West] = false;
		}		
		else if (tempNeighbors[0] == cell->West&&tempNeighbors[0] != NULL)
		{
			cell->Neighbors[West] = false;
			tempNeighbors[0]->Neighbors[East] = false;
		}
		return tempNeighbors[0];
	}
	else if(tempNeighbors.size()==1)
	{
		
			cell->Neighbors[lastCell] = false;
		
		return tempNeighbors[0];
	}
	else
	{
		cell->neighbor = false;
		return NULL;
	}

	

}

void Maze::SetPathIndex(Cell* cell, int pindex)
{
	
	int debugindex = cell->index;
	if (!cell->flagP)
	{
		cell->pIndex = pindex;
		cell->flagP = true;
	}
	cell->visitedP = true;
	
	pindex=cell->pIndex+1;
	if (cell->North != NULL && !cell->North->flagP&&!cell->north)
	{
		cell->North->pIndex = pindex;
		cell->North->flagP = true;
		Path.push_back(cell->North);
	}

	if (cell->Soth != NULL && !cell->Soth->flagP&&!cell->south)
	{
		cell->Soth->pIndex = pindex;
		cell->Soth->flagP = true;
		Path.push_back(cell->Soth);
	}

	if (cell->East != NULL && !cell->East->flagP&&!cell->east)
	{
		cell->East->pIndex = pindex;
		cell->East->flagP = true;
		Path.push_back(cell->East);
	}
	if (cell->West != NULL && !cell->West->flagP&&!cell->west)
	{
		cell->West->pIndex = pindex;
		cell->West->flagP = true;
		Path.push_back(cell->West);
	}

	/*if (cell->West != NULL && !cell->West->flagP)
		  SetPathIndex(cell->West, pindex);
		if (cell->North != NULL && !cell->North->flagP)
		  SetPathIndex(cell->North, pindex);
		if (cell->Soth != NULL && !cell->Soth->flagP)
		  SetPathIndex(cell->Soth, pindex);
		if (cell->East != NULL && !cell->East->flagP)
		  SetPathIndex(cell->East, pindex);*/
	if (Path.size() > 0)
	{
		int tampsize = Path.size();
		for (int i = 0; i < tampsize; i++)
		{
			if(!Path[i]->visitedP)
			SetPathIndex(Path[i], cell->pIndex);
		}
	}
	
		
}

void Maze::ShortestPath(Cell * cell)
{
	Cell* temp = new Cell();
	temp=GetNextNeiPath(cell);

	if (temp == NULL)
		std::cerr << "Error, no hay mas camino " << std::endl;
	else
	{
		shortestPath.push_back(temp);
		if (temp->pIndex == 0)
		{
			std::cerr << "Acabe" << std::endl;
			for (int i = 0; i < shortestPath.size(); i++)
			{
				std::cerr << "Index de celda: " << shortestPath[i]->index;
				std::cerr << " " << "Valor del index " << shortestPath[i]->pIndex << std::endl;
			}
		}
		else
		{
			ShortestPath(temp);
		}
	}
	
	
	
}

void Maze::MoveIa()
{
	if (updateia)
	{		
 			ia.MoveToNeihborCell(shortestPath);
	}
}

Cell * Maze::GetNextNeiPath(Cell* cell)
{
	int shortesnum;
	bool first = false;
	int temp[4];
	if (cell->North != NULL && !cell->north)
		temp[0] = cell->North->pIndex;
	else
		temp[0] = -1;
	if (cell->Soth != NULL && !cell->south)
		temp[1] = cell->Soth->pIndex;
	else
		temp[1] = -1;
	if (cell->East != NULL && !cell->east)
		temp[2] = cell->East->pIndex;
	else
		temp[2] = -1;
	if (cell->West != NULL && !cell->west)
		temp[3] = cell->West->pIndex;
	else
		temp[3] = -1;

	for (int i = 0; i < 4; i++)
	{
		if (temp[i] != -1)
		{
			if (!first)
			{
				shortesnum = temp[i];
				first = true;
			}
			else
			{
				shortesnum = shortesnum < temp[i] ? shortesnum : temp[i];
			}
		}
	}

	if (cell->North != NULL&&cell->North->pIndex == shortesnum&&temp[0] != -1)
	{
		/*cell->North->iamove = true;
		shortestPath.push_back(cell->North);*/
		return (cell->North);
	}
	else if (cell->Soth != NULL&&cell->Soth->pIndex == shortesnum&&temp[1] != -1)
	{
		return (cell->Soth);
	}
	else if (cell->East != NULL&&cell->East->pIndex == shortesnum&&temp[2] != -1)
	{
		
		return (cell->East);
	}
	else if (cell->West != NULL&&cell->West->pIndex == shortesnum&&temp[3] != -1)
	{
		
		return (cell->West);
	}
	return nullptr;
}

void Maze::ChangueCellPath()
{

}

void Maze::setShortestpathNei()
{
	for (int i = 0; i < shortestPath.size(); i++)
	{
		shortestPath[i]->shortes = true;
	}
}
	







