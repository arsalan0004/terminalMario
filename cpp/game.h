#include "marioFx.h"

class Game{
	private:
		// borders of the game 
		const int WALL_HEIGHT=10;
		const int WALL_WIDTH=10;
		
		bool gameRunning;
		
		// 'pixels' of the game 
		char** pixels;
		
		// draw a box that mario can stand on 
		// int x : x coordinate of the box's left side
		// int y : y coordinate of the box's bottom side 
		// int width : width of the box  
		// height of the box is fixed 
		int drawBox(int x, int y, int width);
		
		
	public:
		
		Mario* mario;
		
		Game(int h, int w);
		
		void clearCanvas();
		
		void drawCanvas();
		
		void clearScreen();
		
		void updateCharacterPositions();
};