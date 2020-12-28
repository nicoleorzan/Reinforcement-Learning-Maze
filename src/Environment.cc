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

void Environment::display_maze(){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("%d ",maze[i*N+j]);
        }
        printf("\n");
    }    
};

void Environment::fill_maze(){
    //Random_maze Rmaze(N, initial_state, final_state);
    //std::vector<int> states = Rmaze.create();

    //std::cout<<"sono qui\n";
    /*for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (std::find_if(states.begin(), states.end(), compare(i*N+j)) != states.end()){
                maze[i*N+j] = 0;
            }
            else {
                maze[i*N+j] = 1;
            }
        }
    }*/

    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            maze[i*N+j] = 0;
            if ((i==0 & j==0) || (i==1 & j==0) || (i==2 & j==0) || (i==1 & j==1) || (i==3 & j==2)){
                maze[i*N+j] = 1;
            }
        }
    }
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
    //std::cout<<"next_state="<<next_state<<std::endl;
    //std::cout<<maze[next_state]<<std::endl;
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