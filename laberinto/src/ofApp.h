#pragma once

#include "ofMain.h"
#include "ofGraphics.h"
#include "Cell.h"
#include "Maze.h"
#include "Player.h"
#include "Game.h"


#include "ofxGui.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		Game* game;
		ofVec3f x;
		Cell* cell;
		Maze* maze;
		Player* player;
		
		ofxPanel gui;

	
		ofxIntSlider size;
		
		ofxToggle startGame;
		ofxToggle start;
		ofxToggle mazeStay;;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
