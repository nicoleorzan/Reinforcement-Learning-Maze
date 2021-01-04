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

Environment::Environment(int n, int is, int fs){
    N = n;
    initial_state = is;
    final_state = fs; // if here the simulation terminates
    maze = new int[N*N];
    fill_maze();
};

Environment::~Environment(){
    delete[] maze;
};

int Environment::get_final_state(){
    return final_state;
}

/*void Environment::display_maze(){
    for (int i=0; i<N; i++){
        std::cout<<i*N<<"  ";
        for (int j=0; j<N; j++){
            printf("%d ",maze[i*N+j]);
        }
        printf("\n");
    }    
};*/

void Environment::display_maze() {
	for (int i = 0; i < N; i++) {
		//std::cout<<i*N<<"  ";
		for (int j = 0; j < N; j++) {
			if ((i*N + j) == initial_state) {
				printf("▶ ");
			}
			else if ((i*N + j) == final_state) {
				printf("◎ ");
			}
			else if (maze[i*N + j] == 1) {
				printf("■ ");
			}
			else {
				printf("□ ");
			}
		}
		printf("\n");
	}
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
    /*Random_maze Rmaze(N, initial_state, final_state);
    std::vector<int> states = Rmaze.create();

    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (std::find_if(states.begin(), states.end(), compare(i*N+j)) != states.end()){
                maze[i*N+j] = 0;
            }
            else {
                maze[i*N+j] = 1;
            }
        }
    }*/

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
	}
    /*
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            maze[i*N+j] = 0;
            if ((i==0 & j==0) || (i==1 & j==0) || (i==2 & j==0) || (i==1 & j==1) || (i==3 & j==2)){
                maze[i*N+j] = 1;
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