#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>
#include <fstream>

#define N 8

int main(){

    double epsilon = 0.5;
    double learning_rate = 0.7;
    double discount_rate = 0.99;
    int n_actions = 4; // up, down, left, right
    int n_states = N*N;
    int starting_state = 56;
    int final_state = 7;
    int num_runs = 200;
    int num_experiments = 200;
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

    // Define the maze
    Environment maze(N, starting_state, final_state);
    maze.display_maze();


    // =============== RUN SARSA ===================
    std::cout<<"\n===> RUNNING SARSA"<<std::endl;
    int algorithm = 0; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV
    
    Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
    Experiment exp(num_runs, num_experiments);
    exp.more_experiments(ag, maze, algorithm);
    average_steps_sarsa = exp.compute_average();
 
    // =============== RUN Q LEARNING ================
    std::cout<<"\n===> RUNNING Q LEARNING"<<std::endl;
    algorithm = 1;
    
    Agent ag1(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
    Experiment exp1(num_runs, num_experiments);
    exp1.more_experiments(ag1, maze, algorithm);
    average_steps_q_learning = exp1.compute_average();
    

    // =============== RUN DOUBLE Q LEARNING ================
    std::cout<<"\n===> RUNNING DOUBLE Q LEARNING"<<std::endl;
    algorithm = 2;
    
    Agent ag2(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
    Experiment exp2(num_runs, num_experiments);
    exp2.more_experiments(ag2, maze, algorithm);
    average_steps_double_q_learning = exp2.compute_average();

    ag.print_QA();
    std::cout<<std::endl;
    ag.print_QB();
    

    // =============== RUN QV LEARNING ================
    std::cout<<"\n===> RUNNING QV LEARNING"<<std::endl;
    algorithm = 3;

    Agent ag3(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
    Experiment exp3(num_runs, num_experiments);
    exp3.more_experiments(ag3, maze, algorithm);
    average_steps_qv = exp3.compute_average();
    

    for (int i=0; i<num_runs; i++){
        myfile << i << "   " << average_steps_sarsa[i] << "   " << average_steps_q_learning[i] << "   " <<  average_steps_double_q_learning[i] << "   " <<  average_steps_qv[i] << "\n";
    }

    // ===============================================
    // ================= EVALUATION ==================
    // ===============================================


    std::cout<<"\n===> EVALUATION OF SARSA"<<std::endl;
    algorithm = 0;
    epsilon = 0;
    exp.evaluation(ag, maze, epsilon, algorithm);

    std::cout<<"\n===> EVALUATION OF Q LEARNING"<<std::endl;
    algorithm = 1;
    exp1.evaluation(ag1, maze, epsilon, algorithm);

    std::cout<<"\n===> EVALUATION OF DOUBLE Q LEARNING"<<std::endl;
    algorithm = 2;
    exp2.evaluation(ag2, maze, epsilon, algorithm);

    std::cout<<"\n===> EVALUATION OF QV LEARNING"<<std::endl;
    algorithm = 3;
    exp3.evaluation(ag3, maze, epsilon, algorithm);

    myfile.close();
    delete[] average_steps_sarsa;
    //delete[] average_steps_q_learning;
    //delete[] average_steps_double_q_learning;
    // delete[] average_steps_qv;

    return 0;
}