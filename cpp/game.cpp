#include <iostream>
#include "game.h"

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
	mario->updatePosition();
	
	
}

