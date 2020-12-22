#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"

#define N 4

int main(){

    double epsilon = 0.05;
    double learning_rate = 0.7;
    double discount_rate = 0.99;
    int n_actions = 4; // up, down, left, right
    int n_states = N*N;
    int starting_state = 12;
    int final_state = 3;

    // in this way I can define a new agent
    Agent agent(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state);

    Environment maze(N, final_state);
    maze.display_maze();

    Experiment e(agent, maze);

    return 0;
}