#include <iostream>
#include "marioFx.h"

// thickness of mario sprite
const int MARIO_WIDTH  = 16;
const int MARIO_HEIGHT = 16;

// num of pixels mario moves when he jumps 
const int MARIO_JUMP_HEIGHT = 10;

namespace mario_sprites{
	const char* idle[MARIO_WIDTH] = {
		
									 "   #####        ",
									 "  #########     ",
									 "  ###::#:       ",
									 " #:#:::#:::     ",
									 " #:##:::#::::   ",
									 " ##:::::####    ",
									 "   ::::::::     ",
									 "  #######       ",
									 " ###########    ",
									 "############### ",
									 "::###:##:####:: ",
									 ":::#########::: ",
									 "::###########:: ",
									 "  ###     ###   ",
									 " ###       #### ",
									 "####       #####"};
									 
												
	const char* walking1[MARIO_WIDTH] = {
		
		                             "    #####       ",
		                             "   #########    ",
		                             "   ###::#:      ",
		                             "  #:#:::#:::    ",
		                             "  #:##:::#::::  ",
		                             "  ##:::::####   ",
		                             "    ::::::::    ",
		                             " #########      ",
		                             ":#############::",
		                             ":: ############:",
		                             ":  #####:####   ",
		                             "  #########    #",
		                             " ###############",
		                             "#####    #######",
		                             "###             ",
		                             " ###            "};
									 
									 
	const char* walking2[MARIO_WIDTH] = {
									
		                             "     #####      ",
		                             "    #########   ",
		                             "    ###::#:     ",
		                             "   #:#:::#:::   ",
		                             "   #:##:::#:::: ",
		                             "   ##:::::####  ",
		                             "     ::::::::   ",
		                             "   ########     ",
		                             "  ##########    ",
		                             "  ###########:  ",
		                             "  ######:#####  ",
		                             "  ############  ",
		                             "   ##########   ",
		                             "    #########   ",
		                             "    ##########  ",
		                             "    #####       "};


	const char* walking3[MARIO_WIDTH] = {
		
									 "     #####      ",
									 "    #########   ",
									 "    ###::#:     ",
									 "   #:#:::#:::   ",
									 "   #:##:::#:::: ",
									 "   ##:::::####  ",
									 "     ::::::::   ",
									 "   ########  :  ",
									 "  :########:::: ",
									 " ::##########   ",
									 " #######:####   ",
									 " ###########    ",
									 "#####  ####     ",
									 "#      ###      ",
									 "     ####       ",
									 "     #####      "};
									 
									 
										
	
	const char* jumping[MARIO_WIDTH] = {
		
		                             "     #####  ::::",
		                             "    #########:::",
		                             "    ###::#:  ###",
		                             "   #:#:::#:::###",
		                             "   #:##:::#::::#",
		                             "   ##:::::##### ",
		                             "     ::::::::#  ",
		                             "    #########   ",
		                             "  ###########   ",
		                             " :###########   ",
		                             ":: ###:##:##   #",
		                             ":: ##########  #",
		                             "   #############",
		                             "  ############# ",
		                             "############    ",
		                             "#               "};
									 
	
	
}


Mario::Mario(int max_y, int max_x) : FLOOR_HEIGHT(max_y - MARIO_HEIGHT), MAX_X(max_x), MAX_Y(max_y){
	
	// mario is just chilling 
	state = IDLE;
	
	facing_right = true;
	
	// set mario at start of game 
	y = 0;
	x = 0;
}

void Mario::elevate(){
		
	// if mario is idle, then make him jump!
	if(state != JUMPING && state != DOUBLE_JUMP)
		jump_budget += MARIO_JUMP_HEIGHT;
}

void Mario::descend(){

	if(y < FLOOR_HEIGHT)
		y++;
}


void Mario::move_right(){
	
	if(x < MAX_X)
		right_budget++;
}

void Mario::move_left(){
	
	if(x > 0)
		left_budget ++;
}


int Mario::convertToWorldCoordinates(int y){
	return MAX_Y - MARIO_HEIGHT -y;
}

void Mario::updatePosition(char** pixels){
	// update the position of mario 
	
	// determine direction that Mario is facing
	if(right_budget == left_budget){
		// don't change mario's direction
		facing_right = facing_right;
	}
	else if(right_budget >= left_budget){
		facing_right = true;
	} else {
		facing_right = false;
	}
	
	// for calculating the jump
	if(jump_budget > 0){ 
		
		// check if boundary ontop of Mario's head 
		if(senseBoundary(pixels) == ABOVE){
			// don't jump, and also remove all potential to 
			// jump while under the boundary
			jump_budget = 0;
		}
		
		else {
			// move mario up
			y++;
			jump_budget--;
			}
	}
	
	// if mario is not scheduled to jump 
	// or he is at the peak of his jump 
	// (i.e. his jump budget is 0)
	 if(jump_budget == 0){
		if(!onGround(pixels)){
			y--;
		}
	}
	
	// for moving mario forward 
	if(right_budget > 0){
		
		// check if hit a boundary  ie. a wall 
		if(senseBoundary(pixels) == RIGHT){
			right_budget = 0;
		}
		
		else {
			x++;
			right_budget --;
		}
		
		
	}
	
	// for moving mario backwards
	if(left_budget > 0){
		
		// check if hit a boundary  ie. a wall 
		if(senseBoundary(pixels) == LEFT){
			right_budget = 0;
		}
		else {
			x--;
			left_budget--;
		}
		
	}
	
	
}


const char** get_mario_sprite(marioState state){
	
	
	switch(state){
		case IDLE:
			return mario_sprites::idle;
			
		case JUMPING:
			return mario_sprites::jumping;
			
		case FALLING:
			return mario_sprites::jumping;
		
		case DOUBLE_JUMP:
			return mario_sprites::jumping;
			
		case WALKING1:
			return mario_sprites::walking1;
			
		case WALKING2:
			return mario_sprites::walking2;
			
		case WALKING3:
			return mario_sprites::walking3;
			
		default: 
			return mario_sprites::idle;
	}
}

boundarySenseResult Mario::senseBoundary(char** pixels){
	/* checks if Mario bumps into something in the game*/
	
	boundarySenseResult res = NONE;
	
	// convert y coordinate of mario to world coordinate
	int worldY = convertToWorldCoordinates(y);
	
	
	// check if there is anything on top of mario
	for(int i =x; i< x + MARIO_WIDTH -1; i++){
		if (pixels[worldY -1][i] != ' ') res = ABOVE;
	}
	
	
	for(int i = worldY; i< worldY + MARIO_HEIGHT; i++){
		if (pixels[i][x + MARIO_WIDTH] != ' ') res = RIGHT;
	}
	
	for(int i = worldY; i< worldY + MARIO_HEIGHT; i++){
		if (pixels[i][x -1] != ' ') res = LEFT;
	}
	
	return res;
	
	
}

bool Mario::onGround(char** pixels){
	// check the pixles under Mario's feet and see if 
	// he is on a surface that he can stand on 
	
	
	// 1. if mario is at the bottom of the screen, 
	// then he is on the ground 
	if(y==0){
		return true;
	}
	
	
	// 2. if mario is in on a platform, then he is on the ground too. 
	int worldY = convertToWorldCoordinates(y);
	
	for(int i =x; i< x + MARIO_WIDTH; i++){
		if(pixels[worldY + MARIO_HEIGHT][i] == '~') return true;
	}
	
	return false;
	
}

void Mario::updateState(char** pixels){
	
	// mario is off the ground, 
	if(!onGround(pixels)) {
		
		switch(state){
			case JUMPING:
				if(jump_budget == 0) state = FALLING;
				break;
			case FALLING:
				if(jump_budget != 0) state = DOUBLE_JUMP;
				break;
			case DOUBLE_JUMP:
				break; // nothing to do but wait until on ground 
			default:
				state = JUMPING;

		}
	}
		
	
	else /* if Mario is on the ground, or landed on on surface*/ {
		
		
		if /* if mario had landed on a platform during the course of a jump */
		(state == JUMPING || state == FALLING || state == DOUBLE_JUMP){
			
			// then he should become IDLE
			state = IDLE;
			
			// make it so he won't jump in the next frame 
			jump_budget = 0;
			
		}
		
		if /* Mario hasn't been commanded to move right or left*/
		(right_budget == 0 && left_budget == 0){
			state = IDLE;
			
		// mario should be walking 
		} else if(right_budget > 0 || left_budget > 0){
			
			switch(state) {
				case IDLE     : state = WALKING1; break;
				case WALKING1 : state = WALKING2; break;
				case WALKING2 : state = WALKING3; break;
				case WALKING3 : state = WALKING1; break;
				//case default  : state = IDLE;     
			
			}
		}
	}
}

void Mario::draw(char** pixels){
	
	// get most recent state of mario
	updateState(pixels);
	

	// offsets used to place the left most and 
	// bottom most pixels of Mario's foot 
	// in the left bottom corner of the screen 
	// when mario is positioned at (x,y) = (0,0)
	
	const char** mario_sprite = get_mario_sprite(state);
	
	
	
	// to put mario on ground when y = 0, we need to apply an offset
	// because the y coordinate begins at the top of the screen
	int worldY = convertToWorldCoordinates(y);
	
	
	// facing left, so draw the reverse sprite 
	if(facing_right == 0) {
		for(int r=0; r < MARIO_HEIGHT; r++){
		for(int c=0; c < MARIO_WIDTH; c++){
			pixels[r + worldY][c+x] = mario_sprite[r][MARIO_WIDTH -1 -c];
			
			}
		}
		
	
	} else /* mario is facing right */{
	
		for(int r=0; r < MARIO_HEIGHT; r++){
			for(int c=0; c < MARIO_WIDTH; c++){
				pixels[r + worldY][c+x] = mario_sprite[r][c];
				
				
			}
		}
	}
}

