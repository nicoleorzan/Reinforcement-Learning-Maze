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
    int run_length = 10;

    // in this way I can define a new agent
    Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state);
    
    // Define the maze
    Environment maze(N, final_state);
    maze.display_maze();

    // Run the experiment (agent acts on the maze, maze gives back next state and reward, and loop goes on)
    Experiment exp(run_length);
    exp.single_run(ag, maze);

    return 0;
}