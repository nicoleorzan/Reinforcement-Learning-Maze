#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>
#include <fstream>

#define N 8

int main(){

    double epsilon = 0.2;
    double learning_rate = 0.7;
    double discount_rate = 0.99;
    int n_actions = 4; // up, down, left, right
    int n_states = N*N;
    int starting_state = 56;
    int final_state = 7;
    int num_runs = 10;
    int num_experiments = 1;
    double lambda = 0.3;
    int* average_steps_sarsa = new int[num_runs];
    int* average_steps_q_learning = new int[num_runs];
    int* average_steps_double_q_learning = new int[num_runs];
    int* average_steps_qv = new int[num_runs];
    //double T = 10;

    if (starting_state < 0 || starting_state >= N*N || final_state < 0 || final_state >= N*N ){
        std::cout<<"Initial or final state outside the maze borders\n";
        return -1;
    }

    std::ofstream myfile;
    myfile.open ("data.txt");
    myfile << "Run   sarsa   q_learning   double_q_learning   qv_learning\n";

    // in this way I can define a new agent
    Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);

    // Define the maze
    Environment maze(N, starting_state, final_state);
    maze.display_maze();

    // Run the experiment (agent acts on the maze, maze gives back next state and reward, and loop goes on)
    //Experiment exp(num_runs, num_experiments);

    // =============== RUN SARSA ================
    //exp.single_run_SARSA(ag, maze);
    //exp.more_runs(ag, maze, 0);
    Experiment exp(num_runs, num_experiments);
    /*int algorithm = 0; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV
    exp.more_experiments(ag, maze, algorithm);
    average_steps_sarsa = exp.compute_average();
 
    // =============== RUN Q LEARNING ================
    Experiment exp1(num_runs, num_experiments);
    algorithm = 1;
    exp1.more_experiments(ag, maze, algorithm);
    average_steps_q_learning = exp1.compute_average();
    */

    // =============== RUN DOUBLE Q LEARNING ================
    int algorithm = 2;
    Experiment exp2(num_runs, num_experiments);
    exp2.more_experiments(ag, maze, algorithm);
    average_steps_double_q_learning = exp2.compute_average();

    ag.print_QA();
    std::cout<<std::endl;
    ag.print_QB();
    

    // =============== RUN QV LEARNING ================
    /*Experiment exp3(num_runs, num_experiments);
    algorithm = 3;
    exp3.more_experiments(ag, maze, algorithm);
    average_steps_qv = exp3.compute_average();
    */

    for (int i=0; i<num_runs; i++){
        myfile << i << "   " << average_steps_sarsa[i] << "   " << average_steps_q_learning[i] << "   " <<  average_steps_double_q_learning[i] << "   " <<  average_steps_qv[i] << "\n";
    }

    //exp.evaluation(ag, maze);

    myfile.close();
    delete[] average_steps_sarsa;
    //delete[] average_steps_q_learning;
    //delete[] average_steps_double_q_learning;
    // delete[] average_steps_qv;

    return 0;
}