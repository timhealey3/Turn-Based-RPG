#include "pch.h"
#include <iostream>

Player* MainCharacter = nullptr;
char the_map[12][13] =
{ "xxxxxxxxxxxx",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "x          x",
  "xxxxxxxxxxxx" };

struct Player {
	Player(PlayerCharacterDelegate* charClass) : us(charClass) {}
	Player() = delete;
	PlayerCharacter us;
	int prev_xpos = 3;
	int prev_ypos = 3;
	int xpos = 3;
	int ypos = 3;
};

void moveplayeronmap(Player& player1) {
	// if they haven't move, return and do nothing
	if (player1.xpos == player1.prev_xpos && player1.ypos == player1.prev_ypos)
		return;

	if (the_map[player1.xpos][player1.ypos] == 'M') {
		//enterfightsequence(player1);
	}

	// check that the player hasn't moved into a wall
	if (the_map[player1.xpos][player1.ypos] != 'x') {
		// draw the charater at new location
		the_map[player1.xpos][player1.ypos] = 'P';
		// make old location a black area
		the_map[player1.prev_xpos][player1.prev_ypos] = ' ';
		// update current location to be previous before next update
		player1.prev_xpos = player1.xpos;
		player1.prev_ypos = player1.ypos;
	}
	else {
		// hit a wall, move back to prev location
		player1.xpos = player1.prev_xpos;
		player1.ypos = player1.prev_ypos;
	}
}


void showmap() {
	system("CLS");
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 13; j++)
		{
			std::cout << the_map[i][j];
		}
		std::cout << "\n";
	}
}
int main(int argc, char** argv) {

	bool running = true;

	std::cout << "Choose a class: \n"
		<< "1 = Cleric    2 = Warrior\n"
		<< "3 = Rogue     4 = Wizard\n";
	int choice = 0;
	while (choice == 0) {
		choice = getchar();
		if (choice < 1 || choice > 4)
			choice = 0;
	}
	switch (choice) {
	case 1:
	{
		MainCharacter = new Player(new Cleric());
	}
	break;
	case 2:
	{
		MainCharacter = new Player(new Warrior());
	}
	break;
	case 3:
	{
		MainCharacter = new Player(new Rogue());
	}
	break;
	case 4:
	{
		MainCharacter = new Player(new Wizard());
	}
	break;
	default:
		return -12;  // failed to make player character
	}
	the_map[MainCharacter->xpos][MainCharacter->ypos] = 'P';
	showmap();

	while (running) {
		std::cout << "\nmove(wasd): ";
		char c = getchar();
		switch (c) {
		case 'w':
			MainCharacter->xpos--;
			break;
		case 's':
			MainCharacter->xpos++;
			break;
		case 'a':
			MainCharacter->ypos--;
			break;
		case 'd':
			MainCharacter->ypos++;
			break;
		default:
			break;
		}
		moveplayeronmap(*MainCharacter);
		showmap();
	}
	return EXIT_SUCCESS;
}

