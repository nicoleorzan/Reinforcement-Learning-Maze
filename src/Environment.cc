#include "Environment.h"

Environment::Environment(int n, int fs){
    N = n;
    final_state = fs; // if here the simulation terminates
};

// for the moment I am using the simplest reward function ever
double Environment::sample_reward(int state){
    
    int reward = 0;
    if (state == final_state){
        reward = 1;
    }
    return reward;
};

int Environment::sample_next_state(int state, int action){
    int s = 0;
    return s;
};