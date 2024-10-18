#include "marioFx.h"

class Game{
	private:
		// borders of the game 
		const int WALL_HEIGHT=10;
		const int WALL_WIDTH=10;
		
		bool gameRunning;
		
		// 'pixels' of the game 
		char** pixels;
		
		
	public:
		
		Mario* mario;
		
		Game(int h, int w);
		
		void clearCanvas();
		
		void drawCanvas();
		
		void clearScreen();
		
		void updateCharacterPositions();
};