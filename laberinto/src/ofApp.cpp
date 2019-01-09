#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	x.x = 15;
	x.y = 15;
	x.z = 0;
	/*cell = new Cell(x,250,250);
	cell->buildWall(0);
	cell->buildWall(1);
	cell->buildWall(2);
	cell->buildWall(3);

	player = new Player();
	player->cell = cell;
	player->SetPlayer(200, 200, 20, 10, 10);*/
	maze = new Maze(x, 8,30,30);
	maze->BuildMaze();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	maze->MoveIa();
}

//--------------------------------------------------------------
void ofApp::draw(){
	/*cell->draw();
	player->draw();*/
	maze->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
		maze->BuildPath(key);
		maze->MovePlayer(key);
	//player->Move(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	maze->SelectCell(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
