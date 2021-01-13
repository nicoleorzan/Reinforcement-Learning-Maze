#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>
#include <fstream>
#include "time.h"

#define N 8

//#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9)

int main() {

	double epsilon = 0.5;
	double learning_rate = 0.3;
	double discount_rate = 0.99;
	int n_actions = 4; // up, down, left, right
	int n_states = N * N;
	int starting_state = 56;
	int final_state = 7;
	int num_runs = 1000; 
	int num_experiments = 1;
	double lambda = 0.5;
	int* average_steps_sarsa = new int[num_runs];
	int* average_steps_q_learning = new int[num_runs];
	int* average_steps_double_q_learning = new int[num_runs];
	int* average_steps_qv = new int[num_runs];
	double c = 20; //big c -> more exploration
	double T = 0.01;

	// timing-related variables
	// double tstart, tstop, ctime;
	// struct timespec ts;

	// read maze from file

	std::ifstream in;
    in.open("wall_states.txt");
  
	std::vector<int> walls;
    int element;

    if (in.is_open()) {
        while (in >> element) {
			walls.push_back(element);
        }
    }

    in.close();


	if (starting_state < 0 || starting_state >= N * N || final_state < 0 || final_state >= N * N) {
		std::cout << "Initial or final state outside the maze borders\n";
		return -1;
	}

	std::ofstream myfile;
	myfile.open("data.txt");
	myfile << "epsilon = " << epsilon << "\n" << "learning_rate = " << learning_rate << "\n" << "discount_rate = " << discount_rate << "\n" << "lambda = " << lambda << "\n" << "c = " << c << "\n" << "T = " << T << "\n";
	myfile << "SARSA   Q_learning   double_Q_learning   QV_learning\n";

	// Define the maze
	Environment maze(N, starting_state, final_state, walls);
	maze.display_maze();

	// =============== RUN SARSA ===================
	std::cout << "\n===> RUNNING SARSA" << std::endl;
	int algorithm = 0; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV
	int exploraton_strategy = 0; // 0 = epsilon-greedy; 1 = boltzmann, 2 = UCB

	Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp(num_runs, num_experiments, T, c);
	exp.run_more_experiments(ag, maze, algorithm, exploraton_strategy);
	average_steps_sarsa = exp.compute_average();

	ag.print(ag.get_Q(), n_states, n_actions);
	std::cout << "\nPrinting final policy obtained from SARSA:" << std::endl;
	maze.print_policy(ag.get_Q());

	// =============== RUN Q LEARNING ================
	std::cout << "\n===> RUNNING Q LEARNING" << std::endl;
	algorithm = 1;

	Agent ag1(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp1(num_runs, num_experiments, T, c);
	exp1.run_more_experiments(ag1, maze, algorithm, exploraton_strategy);
	average_steps_q_learning = exp1.compute_average();

	ag1.print(ag1.get_Q(), n_states, n_actions);    
	std::cout << "\nPrinting final policy obtained from Q learning:" << std::endl;
	maze.print_policy(ag1.get_Q());

	// =============== RUN DOUBLE Q LEARNING ================
	std::cout << "\n===> RUNNING DOUBLE Q LEARNING" << std::endl;
	algorithm = 2;

	Agent ag2(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp2(num_runs, num_experiments, T, c);
	exp2.run_more_experiments(ag2, maze, algorithm, exploraton_strategy);
	average_steps_double_q_learning = exp2.compute_average();

	ag2.print(ag2.get_QA(), n_states, n_actions);
	std::cout<<std::endl;
	ag2.print(ag2.get_QB(), n_states, n_actions);
	
	std::cout << "\nPrinting final policy obtained from double Q learning (QA):" << std::endl;
	maze.print_policy(ag2.get_QA());
	std::cout << "\nPrinting final policy obtained from double Q learning (QB):" << std::endl;
	maze.print_policy(ag2.get_QB());

	// =============== RUN QV LEARNING ================
	std::cout << "\n===> RUNNING QV LEARNING" << std::endl;
	algorithm = 3;

	Agent ag3(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp3(num_runs, num_experiments, T, c);
	exp3.run_more_experiments(ag3, maze, algorithm, exploraton_strategy);
	average_steps_qv = exp3.compute_average();

	ag3.print(ag3.get_Q(), n_states, n_actions);
	std::cout << "\nPrinting final policy obtained from QV learning:" << std::endl;
	maze.print_policy(ag3.get_Q());

	// ===============================================
	// ================= FILLING FILE ================
	// ===============================================


	for (int i = 0; i < num_runs; i++) {
		myfile << "   " << average_steps_sarsa[i] << "   " << average_steps_q_learning[i] << "   " << average_steps_double_q_learning[i] << "   " << average_steps_qv[i] << "\n";
	}

	// ===============================================
	// ================= EVALUATION ==================
	// ===============================================

	std::cout << "Performing evaluation with greedy policy with random starting state:" << std::endl;
	epsilon = 0.1;

	std::cout << "\n===> EVALUATION OF SARSA" << std::endl;
	algorithm = 0;
	//exp.evaluation(ag, maze, epsilon, algorithm);
	std::vector<int> starting_states = {0, 9, 56, 8, 10, 32, 46, 61, 28, 31, 63};

	std::vector<int> evals = exp.run_more_evaluations(ag, maze, algorithm, epsilon, starting_states);

	std::cout << "\n===> EVALUATION OF Q LEARNING" << std::endl;
	algorithm = 1;
	//exp1.evaluation(ag1, maze, epsilon, algorithm);
	std::vector<int> evals1 = exp1.run_more_evaluations(ag1, maze, algorithm, epsilon, starting_states);

	std::cout << "\n===> EVALUATION OF DOUBLE Q LEARNING" << std::endl;
	algorithm = 2;
	//exp2.evaluation(ag2, maze, epsilon, algorithm);
	std::vector<int> evals2 = exp2.run_more_evaluations(ag2, maze, algorithm, epsilon, starting_states);

	std::cout << "\n===> EVALUATION OF QV LEARNING" << std::endl;
	algorithm = 3;
	//exp3.evaluation(ag3, maze, epsilon, algorithm);
	std::vector<int> evals3 = exp3.run_more_evaluations(ag3, maze, algorithm, epsilon, starting_states);

	std::ofstream myfile_evals;
	myfile_evals.open("data_evals.txt");
	myfile_evals << "SARSA   Q_learning   double_Q_learning   QV_learning\n";
	for (int i = 0; i < starting_states.size(); i++) {
		myfile_evals << "   " << evals[i] << "   " << evals1[i] << "   " << evals2[i] << "   " << evals3[i] << "\n";
	}

	myfile.close();
	myfile_evals.close();
	delete[] average_steps_sarsa;
	//delete[] average_steps_q_learning;
	//delete[] average_steps_double_q_learning;
	// delete[] average_steps_qv;

	return 0;
}
