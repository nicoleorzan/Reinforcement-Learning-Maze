#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>

#define N 8

int main(){

    double epsilon = 0.1;
    double learning_rate = 0.7;
    double discount_rate = 0.99;
    int n_actions = 4; // up, down, left, right
    int n_states = N*N;
    int starting_state = 56;
    int final_state = 7;
    int num_runs = 200;
    double T = 10;

    if (starting_state < 0 || starting_state >=N*N || final_state < 0 || final_state >=N*N ){
        std::cout<<"Initial or final state outside the maze borders\n";
        return -1;
    }

    // in this way I can define a new agent
    Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state);

    // Define the maze
    Environment maze(N, starting_state, final_state);
    maze.display_maze();

    // Run the experiment (agent acts on the maze, maze gives back next state and reward, and loop goes on)
    Experiment exp(num_runs);
    //exp.single_run_Boltzmann(ag, maze, T);
    //exp.more_runs(ag, maze);
    exp.more_Boltzmann_exploration_runs(ag, maze, T);

    std::cout<<std::endl;
    //ag.print_Q();

    exp.evaluation(ag, maze);

    return 0;
}