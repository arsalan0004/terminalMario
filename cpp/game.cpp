#include <iostream>
#include "game.h"


const int BOX_HEIGHT = 2;


Game::Game(int h, int w): WALL_HEIGHT(h), WALL_WIDTH(w){
	
	mario = new Mario(h, w);
	
	// create a new array of pointers which point to a char 
	pixels = new char*[h]; 
			
	// each char pointer now points to a char which is the 
	// first element of a character array 
	for(int i=0; i < h; i++){
		pixels[i] = new char[w];
	}
		
	gameRunning = false;
	
	
	
}

void Game::clearScreen(){
	system("clear");
}

void Game::clearCanvas(){
	// 1. create the white space that the canvas will inhabit
	for(int i =0; i < WALL_HEIGHT; i++){
		for(int j =0; j < WALL_WIDTH; j++){
			pixels[i][j] = ' ';
		}
	}
}

void Game::drawCanvas(){
	// clear the screen 
	clearScreen();
	
	// clear the canvas 
	clearCanvas();
	
	// draw platform for Mario to stand on 
	drawBox(30,30, 20);
	
	// draw platform for Mario has to jump over
	drawBox(20,10, 20);
	
	// draw mario's new position on the screen
	mario->draw(pixels); 
	
	// draw the 'roof' of the game 
	std::cout << '|';
	for(int i=0; i< WALL_WIDTH; i++){
		std::cout << '-';
	}
	std::cout << "|\n";
	
	// draw the 'pixels' onto the screen, adding borders  
	for(int i=0; i < WALL_HEIGHT; i++){
		for(int j=0; j< WALL_WIDTH; j++){
			
			if(j == 0){
				std::cout << '|';
				std::cout << pixels[i][j];
			}
			
			else if(j == WALL_WIDTH-1){
				std::cout << ' ';
				std::cout << "|\n";
			}
			
			else {
				std::cout << pixels[i][j];
			}
		}
	}
	
	// draw the 'ground' of the game 
	//------------------------------
	
	for(int i=0; i< WALL_WIDTH+1; i++){
		std::cout << '~';
	}
	std::cout << "|\n";
	for(int i=0; i< WALL_WIDTH+1; i++){
		std::cout << '.';
	}
	std::cout << "|\n";
	for(int i=0; i< WALL_WIDTH+1; i++){
		std::cout << '.';
	}
	std::cout << "|\n";
	for(int i=0; i< WALL_WIDTH+1; i++){
		std::cout << '_';
	}
	std::cout << "|\n";
	
}

void Game::updateCharacterPositions(){
	mario->updatePosition(pixels);
	
	
}

int Game::drawBox(int x, int y, int width){
	
	// convert y so that y=0 refers to the bottom of the 
	// screen instead of the top of the screen
	int c_y = WALL_HEIGHT - y;
	

	int start_x = x;  // left side of the box 
	int stop_x  = start_x + width;
	int start_y = WALL_HEIGHT -1 -y;  // bottom of the box 
	int stop_y  = start_y - BOX_HEIGHT;
	
	
	// check that x, y and width do not place the box outside of the screen
	if(start_x < 0) return 1;
	if(start_y > WALL_HEIGHT) return 1;
	
	if(stop_x  > WALL_WIDTH) return 1;
	if(stop_y  < 0) return 1;
	
	
	// draw the top layer of the box 
	for(int x = start_x; x< stop_x; x++){
		pixels[stop_y][x] = '~';
	}
	
	// draw the middle of the box (the filling) 
	for(int h=0; h < BOX_HEIGHT -1; h++){
		for(int x = start_x; x< stop_x; x++){
		pixels[stop_y +1 + h][x] = '.';
	}
	}
	
	// draw the bottom of the box 
	for(int x = start_x; x< stop_x; x++){
		pixels[start_y][x] = '-';
	}
	
	// add the boundaries of the box to the game, so Mario cannot go through
	
	
	return 0;
	
}
