#include "Environment.h"
#include "Random_maze.h"
#include <iostream>
#include <vector>
#include <algorithm>

struct compare
{
    int key;
    compare(int const &i): key(i) { }
 
    bool operator()(int const &i)
    {
        return (i == key);
    }
};

Environment::Environment(int n, int is, int fs, std::vector<int> w){
    N = n;
    initial_state = is;
    final_state = fs; // if here the simulation terminates
    maze = new int[N*N];
    walls = w;
    fill_maze();
};

Environment::~Environment(){
    delete[] maze;
};

int Environment::random_start(){
    //srand (time(NULL));
    int randval = rand() % N*N;

    while ( maze[randval] == 1 ){
        randval = rand() % N*N;
    }
    initial_state = randval;
    return randval;
};

int Environment::get_final_state(){
    return final_state;
}

void Environment::display_maze() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			/*if ((i*N + j) == initial_state) {
				printf("▶ ");
			}*/
			if ((i*N + j) == final_state) {
				printf("◎ ");
			}
			else if (maze[i*N + j] == 1) {
				printf("■ ");
			}
			else {
				printf("□ ");
                //std::cout<<i*N+j<<" ";
			}
		}
		printf("\n");
	}
    printf("\n");
};

std::vector<int> Environment::allowed_actions(int state){

    std::vector<int> allow_act;
    if ( state/N-1>=0 && maze[state-N] == 0 ){
        allow_act.push_back(0); // up
    }
    if ( state/N+1<N && maze[state+N] == 0 ){
        allow_act.push_back(1); // down
    }
    if ( (state)%N-1>=0 && maze[state-1] == 0 ){
        allow_act.push_back(2); // left
    }
    if ( (state)%N+1<N && maze[state+1] == 0 ){
        allow_act.push_back(3); // right
    }

    return allow_act;
};

void Environment::fill_maze(){

    for (int i=0; i<N*N; i++){
        if (std::find(walls.begin(), walls.end(), i) != walls.end()) {
            maze[i] = 1;
        } else { maze[i] = 0;}
    }

    /*
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			maze[i*N + j] = 0;
			if ((i == 0 & j == 0) || (i == 0 & j == 1) || (i == 0 & j == 2) || (i == 0 & j == 3) || (i == 0 & j == 4) || (i == 0 & j == 5)
				|| (i == 0 & j == 6)
				|| (i == 1 & j == 0) || (i == 1 & j == 5)
				|| (i == 2 & j == 0) || (i == 2 & j == 3) || (i == 2 & j == 4) || (i == 2 & j == 5)
				|| (i == 3 & j == 0) || (i == 4 & j == 0) || (i == 5 & j == 0) || (i == 5 & j == 2) || (i == 5 & j == 3) || (i == 5 & j == 4)
				|| (i == 1 & j == 1) || (i == 4 & j == 4) || (i == 4 & j == 5) || (i == 4 & j == 6)
				|| (i == 3 & j == 2) || (i == 7 & j == 1) || (i == 7 & j == 2) || (i == 7 & j == 3)
				|| (i == 7 & j == 4) || (i == 7 & j == 5) || (i == 7 & j == 6) || (i == 7 & j == 7)
				|| (i == 2 & j == 7) || (i == 3 & j == 7) || (i == 4 & j == 7) || (i == 5 & j == 7)
				|| (i == 6 & j == 7) || (i == 6 & j == 6)) {
				maze[i*N + j] = 1;
			}
		}
	}*/

    /*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			maze[i*N + j] = 0;
			if ( (i == 2 & j == 0) || (i == 2 & j == 1) || (i == 2 & j == 2) || (i == 2 & j == 3) || (i == 2 & j == 4) || (i == 2 & j == 5) ||
            (i == 5 & j == 4) || (i == 5 & j == 5) || (i == 5 & j == 6) || (i == 5 & j == 7) ) {
				maze[i*N + j] = 1;
			}
		}
    }*/
};

int Environment::next_state(int state, int action){
    int next_state = state;

    if (action == 0){
        if (state - N >= 0){
            next_state = state - N;
        }
    } 
    
    else if (action == 1){
        if (state + N < N*N){
            next_state = state + N;
        }
    } 
    
    else if (action == 2){
        if (state%N != 0){
            next_state = state - 1;
        }

    } 
    
    else if (action == 3){
        if (state+1%N != 0){
        next_state = state + 1;
        }
    }

    if (maze[next_state] == 1){
        next_state = state;
    }

    return next_state;
};

double Environment::sample_reward(int state){

    int reward = 0;
    if (state == final_state){
        reward = 1;
    }

    return reward;
};

void Environment::print_policy(double *Q){

    double max_val;
    double max_idx;

    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
            if ((i*N + j) == final_state) {
				printf("◎ ");
			}
            else if (maze[i*N + j] == 1) {
				printf("■ ");
			}
            else{
                max_val = 0;
                max_idx = 4;
                for (int act=0; act<4; act++){
                    if ( Q[(i*N+j)*4+act] > max_val ){
                        max_val = Q[(i*N+j)*4+act];
                        max_idx = act;
                    }
                }
                if (max_idx==0){ printf("^ "); }
                else if (max_idx==1){ printf("V "); }
                else if (max_idx==2){ printf("< "); }
                else if (max_idx==3){ printf("> "); }
                else if (max_idx==4){ printf("□ "); }
            }
        }
        printf("\n");
    }
    printf("\n");
};