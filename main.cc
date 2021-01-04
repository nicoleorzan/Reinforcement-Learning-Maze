#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>
#include <fstream>

#define N 8

int main(){

    double epsilon = 0.4;
    double learning_rate = 0.7;
    double discount_rate = 0.99;
    int n_actions = 4; // up, down, left, right
    int n_states = N*N;
    int starting_state = 56;
    int final_state = 7;
    int num_runs = 600;
    int num_experiments = 30;
    double lambda = 0.3;
    //double T = 10;

    if (starting_state < 0 || starting_state >= N*N || final_state < 0 || final_state >= N*N ){
        std::cout<<"Initial or final state outside the maze borders\n";
        return -1;
    }

    std::ofstream myfile;
    myfile.open ("data/data_N10_gradient_alpha01.txt");
    myfile << "step   sarsa     q_learning     double_q_learning    qv_learning\n";

    // in this way I can define a new agent
    Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);

    // Define the maze
    Environment maze(N, starting_state, final_state);
    maze.display_maze();

    // Run the experiment (agent acts on the maze, maze gives back next state and reward, and loop goes on)
    Experiment exp(num_runs, num_experiments);

    // =============== RUN SARSA ================
    //exp.single_run_SARSA(ag, maze);
    //exp.more_runs(ag, maze, 0);

    int algorithm = 1; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV

    exp.more_experiments(ag, maze, algorithm);

    exp.compute_average();

    ag.print_Q();

    //exp.evaluation(ag, maze);

    myfile.close();

    return 0;
}