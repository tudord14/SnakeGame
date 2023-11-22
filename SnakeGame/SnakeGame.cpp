#include <iostream>
#include <math.h>
#include <Windows.h>
#include <conio.h>

//General variables
bool gameOver;
int score;
int x;
int y;
int fruitX;
int fruitY;

//Fruit variables
std::string fruit = "8";


//Window sizes
const int windowWidth = 80;
const int windowHeight = 20;

//Tail variables
int tailX[100];
int tailY[100];
int lengthTail;

//Directions for snake movement
enum directionsUser {
	STOP = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

directionsUser usrDir;


void PrepareTheGame() {
	gameOver = false;
	usrDir = STOP;

	//Start in the center of the screen
	x = windowWidth / 2;
	y = windowHeight / 2;

	fruitX = rand() % windowWidth + 1;
	fruitY = rand() % windowHeight + 1;

	score = 0;

}


void RenderGame() {

	system("cls");

	//Top border of the game screen
	for (int i = 0; i < windowWidth + 1; i++) {
		std::cout << "@";
	}
	std::cout << std::endl;

	//The rows and columns of the game window
	for (int i = 1; i <= windowHeight; i++) {
		for (int j = 1; j <= windowWidth; j++) {
			if (j == 1 || j == windowWidth)
				std::cout << "@";
			if (i == y && j == x) {
				std::cout << "O";
			}
			else if (j == fruitX && i == fruitY) {
				std::cout << fruit;
			}
			else {
				bool print = false;

				for (int m = 0; m < lengthTail; m++) {
					if (tailX[m] == j && tailY[m] == i) {
						std::cout << "O";
						print = "true";
					}
				}
				if (print == false) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}

	for (int w = 0; w < windowWidth + 1; w++) {
		std::cout << "@";
	}
	std::cout << std::endl;
	std::cout << "SCORE: " << score << std::endl;
}


void UserInput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			usrDir = LEFT;
			break;
		case 'd':
			usrDir = RIGHT;
			break;
		case 'w':
			usrDir = UP;
			break;
		case 's':
			usrDir = DOWN;
			break;
		case 'p':
			usrDir = STOP;
			break;
		}
	}
}


void UnderTheHood() {
	int prevX = tailX[0];
	int prevY = tailY[0];

	int prev2X;
	int prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < lengthTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (usrDir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}


	//If snake hits the border game ends
	if ((x > windowWidth || x < 0) || (y > windowHeight || y < 0)) {
		std::cout << "GAME OVER" << std::endl;
		std::cout << "YOU'VE HIT A WALL" << std::endl;
		gameOver = true;
	}

	//If snake hits his tail the game ends
	for (int i = 0; i < lengthTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			std::cout << "GAME OVER" << std::endl;
			std::cout << "YOU'VE HIT YOURSELF" << std::endl;
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score = score + 10;
		lengthTail = lengthTail + 1;
		fruitX = rand() % windowWidth + 1;
		fruitY = rand() % windowHeight + 1;
	}

}


int main() {
	PrepareTheGame();

	while (!gameOver) {
		RenderGame();
		UserInput();
		UnderTheHood();
		Sleep(1);
	}

	return 0;

}