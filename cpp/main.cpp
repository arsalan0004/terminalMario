#include <iostream> 
#include <thread>
#include <termios.h>
#include <unistd.h>

#include "game.h"



// settings for the terminal (set in set_getChar(), restoreTerminal())
struct termios newt, oldt;

//void getInput();
//void setupInput();
void restoreTerminal();



void setupInput(Mario* mario){

    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
	
	newt = oldt;
	
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
	
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set new terminal settings
	
}


void restoreTerminal(){
	
	// Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	
}



void getInput(Mario* mario, bool* gameRunning){
	
	char ch;
	
	while(*gameRunning){
		ch = getchar(); // Call the getch function
        if (ch == 'q') {
			restoreTerminal();
			// clear the screen 
			
			system("clear");
			
			*gameRunning = false;
			
			std::cout << "thank you for playing\n";
            break; // Exit on 'q'
        }
		
		else if (ch == 'w') {
			std:: cout << "pressed w";
			mario->elevate();
		}
		
		else if(ch == 'd'){
			mario->move_right();
		}
		
		else if(ch == 'a'){
			mario->move_left();
		}
	}
}



void updatePositions(){
	// update the positions of all the players 
	// called before the screen is redrawn 
	
}



int main(){
	
	bool gameRunning = true;
	
	Game* g = new Game(40, 100);
	g->drawCanvas();
	
	// setup input 
	setupInput(g->mario);
	
	// start collecting the player's input 
	std::thread inputThread(getInput, g->mario, &gameRunning);
	
	while(gameRunning){
		
		g->updateCharacterPositions();
		
		g->drawCanvas();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		
	}
	
	inputThread.join();
	
	restoreTerminal();
	
	return 0;
}