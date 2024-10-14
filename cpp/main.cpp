#include <iostream> 
#include <thread>
#include <termios.h>
#include <unistd.h>


enum marioState {IDLE, JUMPING};
marioState mario_state = IDLE;



// settings for the terminal (set in set_getChar(), restoreTerminal())
struct termios newt, oldt;

// thickness of mario sprite
const int mario_width = 16;
const int mario_height = 16;


// dimensions of play area 
const int wall_height = 20;
const int wall_width = 40;

// height of mario when he is on the floor
const int floor_height = wall_height - mario_height;

// set marios position to the bottom left of the play area
int mario_x = 0;
int mario_y = wall_height - mario_height;



char pixels[wall_height][wall_width];








bool gameRunning = false;

void setup();
void draw_border();
void draw_mario(int x, int y);
int draw_rectangle(int h, int w, int start_x, int start_y);
void drawScreen();

void setup(){
	// setup a clear canvas 
	
	// set all pixels to blank
	for(int i=0; i < wall_height; i++){
		for(int j=0; j< wall_width; j++){
			
			if(j == wall_width - 1) pixels[i][j] = '\n';
			else  pixels[i][j] = ' ';
		}
	}
	
	// draw the border of the game 
	draw_border();
}

void draw_border(){
	// draw the border of the game 
	for(int i=0; i < wall_height -1; i++){
		for(int j=0; j< wall_width -1; j++){
			
			if(i == 0 & j == wall_width -2) pixels[i][j] = '+';
			
			else if(i == 0) pixels[i][j] = '-';
			
			else if(j == wall_width - 2) pixels[i][j] = '|';
		}
	}
	
}


int draw_rectangle(int h, int w, int start_x, int start_y){
	// h       : height 
	// w       : width 
	// start_x : the left most x value 
	// start_y : the top-most y value 
	
	if(start_x <= 0) return 1;
	
	// draw the corners 
	pixels[start_y + h][start_x] = '+'; // top left corner 
	pixels[start_y][start_x] = '+';     // bottom left corner
	pixels[start_y][start_x + w] = '+';
	pixels[start_y + h][start_x + w] = '+';
	
	
	// draw top and bottom lines 
	for(int x=start_x +1; x< start_x + w; x++){
		
		pixels[start_y][x] = '-';
		pixels[start_y + h][x] = '-';
	}
	
	for(int y=start_y +1; y< start_y + h; y++){
		
		pixels[y][start_x] = '|';
		pixels[y][start_x + w] = '|';
	}
	
		/*
		// draw left corners 
		if(x == start_x) {
			pixels[start_y + h][x] = '+'; // top left corner 
			pixels[start_y][x] = '+';     // bottom left corner
		
		}
		
		// draw right corners 
		else if (x == (start_x + w -1)){
			pixels[start_y][x + w] = '+';
			pixels[start_y + h][x + w] = '+';
		}
		
		// draw top and bottom line of rectangle 
		else {
			pixels[start_y][x] = '-';
			pixels[start_y + h][x] = '-';
		}
		*/
	
	
	
	return 0;
	
}

void draw_slice(int start_x, int start_y, char arr[]){
	
	int x = start_x;
	int y = start_y;
	int i = 0;
	
	while(arr[i] != '\0') {
		pixels[y][x] = arr[i];
		i++;
		x++;
		
	}
}

void elevateMario(){
	if(mario_y > 1){
		mario_y--;
	}
	
	
	std::cout << mario_y;
	
}

void descendMario(){

	if(mario_y < floor_height){
		mario_y++;
	}
	
	
	std::cout << mario_y;
}

void draw_mario(int start_x, int start_y){

	
	
	if(mario_y < floor_height) {
		mario_state= JUMPING;
	} else if(mario_y >= floor_height){
		mario_state = IDLE;
	}
	
	
	char  l1[] ="   #####"         ;
		
	
	
	if(mario_state == IDLE){
		
		char  l2[] ="  #########"      ;
		char  l3[] ="  ###::#:"        ;
		char  l4[] =" #:#:::#:::"      ;
		char  l5[] =" #:##:::#::::"    ;
		char  l6[] =" ##:::::####"     ;
		char  l7[] ="   ::::::::"      ;
		char  l8[] ="  #######"         ;
		char  l9[] =" ###########"   ;
		char l10[] ="###############"   ;
		char l11[] ="::###:##:####::"   ;
		char l12[] =":::#########:::"   ;
		char l13[] ="::###########::"   ;
		char l14[] ="  ###     ###"     ;
		char l15[] =" ###       ####"   ;
		char l16[] ="####       #####"  ;
		
		draw_slice(start_x, start_y + 0, l1);
		draw_slice(start_x, start_y + 1, l2);
		draw_slice(start_x, start_y + 2, l3);
		draw_slice(start_x, start_y + 3, l4);
		draw_slice(start_x, start_y + 4, l5);
		draw_slice(start_x, start_y + 5, l6);
	
		draw_slice(start_x, start_y + 6,  l7);
		draw_slice(start_x, start_y + 7,  l8);
		draw_slice(start_x, start_y + 8,  l9);
		draw_slice(start_x, start_y + 9,  l10);
		draw_slice(start_x, start_y + 10, l11);
		draw_slice(start_x, start_y + 11, l12);
		draw_slice(start_x, start_y + 12, l13);
		draw_slice(start_x, start_y + 13, l14);
		draw_slice(start_x, start_y + 14, l15);
		draw_slice(start_x, start_y + 15, l16);
		
	} 
	
	else if (mario_state == JUMPING){
		
		char  l1[] ="   #####  ;;;;";
		char  l2[] ="  #########;;;";
		char  l3[] ="  ###::#:  ###";
		char  l4[] =" #:#:::#:::###";
		char  l5[] =" #:##:::#::::#";
		char  l6[] =" ##:::::#####"     ;
		char  l7[] ="   ::::::::#"      ;
		char  l8[] ="  #########"         ;
		char  l9[] =" ##########"   ;
		char l10[] ="###########  #"   ;
		char l11[] ="::###:##:##  #"   ;
		char l12[] =":::###########"   ;
		char l13[] ="::############"   ;
		char l14[] =" #############"     ;
		char l15[] ="##########    "   ;
		char l16[] ="#  ####       "  ;
		
		draw_slice(start_x, start_y + 0, l1);
	draw_slice(start_x, start_y + 1, l2);
	draw_slice(start_x, start_y + 2, l3);
	draw_slice(start_x, start_y + 3, l4);
	draw_slice(start_x, start_y + 4, l5);
	draw_slice(start_x, start_y + 5, l6);
	
	draw_slice(start_x, start_y + 6,  l7);
	draw_slice(start_x, start_y + 7,  l8);
	draw_slice(start_x, start_y + 8,  l9);
	draw_slice(start_x, start_y + 9,  l10);
	draw_slice(start_x, start_y + 10, l11);
	draw_slice(start_x, start_y + 11, l12);
	draw_slice(start_x, start_y + 12, l13);
	draw_slice(start_x, start_y + 13, l14);
	draw_slice(start_x, start_y + 14, l15);
	draw_slice(start_x, start_y + 15, l16);
		
	}
	
	
	
	
}


void set_getChar(){

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




void input(){
	
	int i=0;
	int j=0;
	char ch;

	while(true){
		ch = getchar(); // Call the getch function
        if (ch == 'q') {
			restoreTerminal();
			// clear the screen 
			system("clear");
			gameRunning = false;
			
			std::cout << "thank you for playing\n";
            break; // Exit on 'q'
        }
		
		else if (ch == 'w') {
			elevateMario();
		}
		
	}
	
	
}

void applyGravity(){
	
	while(gameRunning){
		
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
		descendMario();
	}
}



void drawScreen(){
	// clear the screen 
	system("clear");
	
	setup();          // add new lines where necessary 
	draw_border();   
	draw_mario(mario_x, mario_y); 
	
	
	// draw the 'pxiels' onto the screen 
	for(int i=0; i < wall_height; i++){
		for(int j=0; j< wall_width; j++){
			std::cout << pixels[i][j];
		}
	}
		
	
		// makes all players and enemies fall
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));	
}


// queue of things that will happen for mario 


// thread that executes the next item in the queue 

// one queue is for y movement and the other is for x movement 





int main(){
	
	
	
	
	
	gameRunning = true;
	
	// set up settings to read char from terminal 
	set_getChar();
	
	// start input thread 
	std::thread inputThread(input);
	
	// start gravity thread 
	std::thread gravityThread(applyGravity);
	
	while(gameRunning) {
		setup();
		drawScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));	
	}
	
	
	
	// start screen rendering 
	//std::thread renderThread(drawScreen);
	
	
	
	
	
	
	
	
	gravityThread.join();
	inputThread.join();
	
	return 0;
	
}