#pragma once


enum marioState {IDLE, 
			     JUMPING,
 				 WALKING1, 
				 WALKING2,
				 WALKING3};

class Mario{
	
	marioState state;
	
	// the height of the floor, that we need to know 
	// to prevent rendering mario under the floor 
	
	const int FLOOR_HEIGHT;
	const int MAX_X; // max x value mario can take on
	const int MAX_Y; // max y value that mario can take on 
	
	
	int x;     // x position of mario 
	int y;     // y position of mario
	
	// how many units mario will move in the next frames 
	int right_budget;
	int left_budget;
	int jump_budget;
	
	
	public:
		void draw(char** pixels);
		
		// moving functions 
		void move_left();
		void move_right();
		void elevate();
		void descend();
		
		// update position of mario based on current xy value 
		// and the movement budget (ex. right_budget)
		void updatePosition();
		
		// constructor 
		Mario(int max_y, int max_x);
	
};




