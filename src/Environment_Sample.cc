#include "Environment.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 12

Environment::Environment(int n, int fs) {
	N = n;
	final_state = fs; // if here the simulation terminates
	maze = new int[N*N];
	fill_maze();
};

Environment::~Environment() {
	delete[] maze;
};

void Environment::display_maze(char maze[][12], int row) {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (maze[i][j] == '1')
				printf("бс");
			else if (maze[i][j] == 'y')
				printf("б┌");
			else if (maze[i][j] == '0')
				printf("бр");
			else
				printf("в║");
		}
		puts("");
	}
};

void Environment::fill_maze() {
	char maze[MAX_SIZE][MAX_SIZE] = { { '1','1','1','1','1','1','1','1','1','1','1','1' },
									 { 'x','0','0','0','1','1','0','0','0','0','0','1' },
									 { '0','1','1','0','1','1','1','1','0','1','1','1' },
									 { '0','1','1','0','0','1','0','0','0','0','0','1' },
									 { '0','0','0','1','1','1','0','1','1','1','0','1' },
									 { '1','1','0','1','1','1','0','1','1','1','0','1' },
									 { '1','1','0','0','0','0','0','1','1','1','0','1' },
									 { '1','1','0','1','1','0','1','1','1','1','0','1' },
									 { '1','0','0','1','1','0','1','0','0','0','0','1' },
									 { '1','0','1','1','1','0','1','0','1','1','1','1' },
									 { '1','0','1','0','0','0','1','0','0','0','0','0' },
									 { '1','1','1','1','1','1','1','1','1','1','1','y' },
	};
};

int Environment::next_state(int state, int action, double epsilon) {
	int next_state = 0;
	// env gets a state and an action and returns the next state
	char *direction = NULL;
	char *action[4] = { "up", "right", "down", "left" };

	//printf("s: %d\n", state);
	srand((unsigned)time(NULL)); //prevent rand() generate same number

	if (((double)rand() / RAND_MAX) < epsilon) {
		action = rand() % 5; // select one of four actions randomly
	}
	else {
		//select action that maximizes Q[state]
	}

	printf("action? %s\n", direction);

	if (direction == "up") {
		next_state = maze[x - 1][y];
	}
	else if (direction == "right") {
		next_state = maze[x][y + 1];
	}
	else if (direction == "down") {
		next_state = maze[x + 1][y];
	}
	else if (direction == "left") {
		next_state = maze[x][y - 1];
	}
	else {
		next_state = maze[x][y];
	}


	return next_state;
};

double Environment::sample_reward(int state) {
	// for the moment I am using a dummy reward function
	int reward = 0;
	if (state == final_state) {
		reward = 1;
	}
	return reward;
};