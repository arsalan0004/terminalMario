#include <iostream>
#include "marioFx.h"

// thickness of mario sprite
const int MARIO_WIDTH  = 16;
const int MARIO_HEIGHT = 16;

// num of pixels mario moves when he jumps 
const int MARIO_JUMP_HEIGHT = 5;

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
	
	state = IDLE;
	
	// set mario at start of game 
	y = 0;
	x = 0;
}

void Mario::elevate(){
	
	bool mario_on_ground = true ;//y >= MAX_Y;
	bool mario_not_mid_jump = true ;//(jump_budget == 0); 
	
	if(mario_on_ground  && mario_not_mid_jump)
		jump_budget = MARIO_JUMP_HEIGHT;

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

void Mario::updatePosition(){
	
	// update the position of mario 
	
	// for calculating the jump
	if(jump_budget > 0){
		// move mario up
		y++;
		jump_budget--;
	}
	
	// if mario is not scheduled to jump 
	// or he is at the peak of his jump 
	// (i.e. his jump budget is 0)
	 else if(jump_budget == 0){
		if(y > 0){
			y--;
		}
	}
	
	
	// for moving mario forward 
	if(right_budget > 0){
		x++;
		right_budget --;
		
	}
	
	// for moving mario backwards
	if(left_budget > 0){
		x--;
		left_budget--;
	}
}


const char** get_mario_sprite(marioState state){
	
	

	
	switch(state){
		case IDLE:
			return mario_sprites::idle;
			
		case JUMPING:
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

void Mario::draw(char** pixels){
	
	// mario is off the ground 
	if(y > 0) {
		state = JUMPING;
	}
	 else if(y == 0 && right_budget == 0){
		state = IDLE;
		
	// mario should be walking 
	} else if(right_budget > 0){
		
		switch(state) {
			case IDLE     : state = WALKING1; break;
			case WALKING1 : state = WALKING2; break;
			case WALKING2 : state = WALKING3; break;
			case WALKING3 : state = WALKING1; break;
			//case default  : state = IDLE;     
		
		}
	}
		
		
	
	// offsets used to place the left most and 
	// bottom most pixels of Mario's foot 
	// in the left bottom corner of the screen 
	// when mario is positioned at (x,y) = (0,0)
	
	const char** mario_sprite = get_mario_sprite(state);
	
	// to put mario on ground when y = 0, we need to apply an offset
	// because the y coordinate begins at the top of the screen
	int height_offset = MAX_Y - MARIO_HEIGHT;
	
	for(int r=0; r < MARIO_HEIGHT; r++){
		for(int c=0; c < MARIO_WIDTH; c++){
			pixels[r + height_offset-y][c+x] = mario_sprite[r][c];
			
			
		}
	}
}

