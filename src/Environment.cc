#include "Environment.h"
#include "stdio.h"

Environment::Environment(int n, int fs){
    N = n;
    final_state = fs; // if here the simulation terminates
    maze = new int[N*N];
    fill_maze();
};

Environment::~Environment(){
    delete[] maze;
};

void Environment::display_maze(){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("%d ",maze[i+N*j]);
        }
        printf("\n");
    }    
};

void Environment::fill_maze(){
    // loop throught the maxe and fill it with ones and zeros. For the moment use a fixed maze. 
    // You can also think how we can dynamicize it! I have no idea up to now   
    // NB: to fill the maze use the expression maze[i+N*j], not maze[i][j], as I did above
};

int Environment::next_state(int state, int action){
    int next_state = 0;
    // env gets a state and an action and returns the next state
    return next_state;
};

double Environment::sample_reward(int state){
    // for the moment I am using a dummy reward function
    int reward = 0;
    if (state == final_state){
        reward = 1;
    }
    return reward;
};