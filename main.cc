#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>
#include <fstream>
#include "time.h"

//#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9)

int main() {

	int N = 12;
	double epsilon = 0.3;
	double learning_rate = 0.3;
	double discount_rate = 0.99;
	int n_actions = 4; // up, down, left, right
	int num_runs = 10000; 
	int num_experiments = 10;
	double lambda = 0.5;
	double* average_steps_sarsa = new double[num_runs];
	double* average_steps_q_learning = new double[num_runs];
	double* average_steps_double_q_learning = new double[num_runs];
	double* average_steps_qv = new double[num_runs];

	double* std_average_steps_sarsa = new double[num_runs];
	double* std_average_steps_q_learning = new double[num_runs];
	double* std_average_steps_double_q_learning = new double[num_runs];
	double* std_average_steps_qv = new double[num_runs];
	
	double* average_returns_sarsa = new double[num_runs];
	double* average_returns_q_learning = new double[num_runs];
	double* average_returns_double_q_learning = new double[num_runs];
	double* average_returns_qv = new double[num_runs];	

	double T = 0.01;

	// timing-related variables
	// double tstart, tstop, ctime;
	// struct timespec ts;

	// read maze from file

	std::ifstream in;
    in.open("maze_definition.txt");
  
	std::vector<int> walls;
    int element;

	int i=0;
    if (in.is_open()) {
        while (in >> element) {
			if (i==0){
				N = element;
			} else{
				walls.push_back(element);
			}
			i++;
        }
    }

    in.close();

	int n_states = N * N;
	int starting_state = 56;
	int final_state = N-1;

	// Define the maze
	Environment maze(N, final_state, walls);
	maze.display_maze();

	if (starting_state < 0 || starting_state >= N * N || final_state < 0 || final_state >= N * N) {
		std::cout << "Initial or final state outside the maze borders\n";
		return -1;
	}

	std::ofstream myfile;
	std::ofstream returns_data;
	myfile.open("data/data.txt");
	returns_data.open("data/returns_data.txt");
	myfile << "epsilon = " << epsilon << "\n" << "learning_rate = " << learning_rate << "\n" << "discount_rate = " << discount_rate << "\n" << "lambda = " << lambda << "\n"<< "\n" << "T = " << T << "\n";
	myfile << "step,SARSA,Q_learning,double_Q_learning,QV_learning,std_SARSA,std_Q,std_double_Q,std_QV\n";
	returns_data << "step,SARSA,Q_learning,double_Q_learning,QV_learning\n";


	int algorithm = 0; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV
	int exploraton_strategy = 0; // 0 = epsilon-greedy; 1 = boltzmann
	int reward_strategy = 1; // 0 = old reward strategy, 1 = new reward strategy


	// =============== RUN SARSA ===================
	std::cout << "\n===> RUNNING SARSA" << std::endl;

	Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp(num_runs, num_experiments, T);
	exp.set_reward_strategy(reward_strategy);
	exp.more_experiments(ag, maze, algorithm, exploraton_strategy);
	average_steps_sarsa = exp.compute_average_steps();
	std_average_steps_sarsa = exp.get_std_average_steps();
	average_returns_sarsa = exp.compute_average_returns();

	ag.print(ag.get_Q(), n_states, n_actions);
	std::cout << "\nPrinting final policy obtained from SARSA:" << std::endl;
	maze.print_policy(ag.get_Q());

	// =============== RUN Q LEARNING ================
	std::cout << "\n===> RUNNING Q LEARNING" << std::endl;
	algorithm = 1;

	Agent ag1(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp1(num_runs, num_experiments, T);
	exp1.set_reward_strategy(reward_strategy);
	exp1.more_experiments(ag1, maze, algorithm, exploraton_strategy);
	average_steps_q_learning = exp1.compute_average_steps();
	std_average_steps_q_learning = exp1.get_std_average_steps();
	average_returns_q_learning = exp1.compute_average_returns();

	ag1.print(ag1.get_Q(), n_states, n_actions);    
	std::cout << "\nPrinting final policy obtained from Q learning:" << std::endl;
	maze.print_policy(ag1.get_Q());

	// =============== RUN DOUBLE Q LEARNING ================
	std::cout << "\n===> RUNNING DOUBLE Q LEARNING" << std::endl;
	algorithm = 2;

	Agent ag2(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp2(num_runs, num_experiments, T);
	exp2.set_reward_strategy(reward_strategy);
	exp2.more_experiments(ag2, maze, algorithm, exploraton_strategy);
	average_steps_double_q_learning = exp2.compute_average_steps();
	std_average_steps_double_q_learning = exp2.get_std_average_steps();
	average_returns_double_q_learning = exp2.compute_average_returns();

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
	Experiment exp3(num_runs, num_experiments, T);
	exp3.set_reward_strategy(reward_strategy);
	exp3.more_experiments(ag3, maze, algorithm, exploraton_strategy);
	average_steps_qv = exp3.compute_average_steps();
	std_average_steps_qv = exp3.get_std_average_steps();
	average_returns_qv = exp3.compute_average_returns();

	ag3.print(ag3.get_Q(), n_states, n_actions);
	std::cout << "\nPrinting final policy obtained from QV learning:" << std::endl;
	maze.print_policy(ag3.get_Q());

	// ===============================================
	// ================= FILLING FILE ================
	// ===============================================

	for (int i = 0; i < num_runs; i++) {
		myfile << i <<"," << average_steps_sarsa[i] <<"," << average_steps_q_learning[i] << "," << average_steps_double_q_learning[i]<< "," << average_steps_qv[i];
		myfile <<"," << std_average_steps_sarsa[i] << "," << std_average_steps_q_learning[i] << "," << std_average_steps_double_q_learning[i] << "," << std_average_steps_qv[i] << "\n";
		returns_data << i <<"," << average_returns_sarsa[i] << "," << average_returns_q_learning[i] << "," << average_returns_double_q_learning[i] << "," << average_returns_qv[i] << "\n";
	}



	// ===============================================
	// ================= EVALUATION ==================
	// ===============================================

	/*std::cout << "Performing evaluation with greedy policy with random starting state:" << std::endl;
	epsilon = 0.1;
	std::cout << "\n===> EVALUATION OF SARSA" << std::endl;
	algorithm = 0;
	//exp.evaluation(ag, maze, epsilon, algorithm);
	std::vector<int> starting_states = {0, 9, 56, 8, 16, 10, 32, 46, 61, 28, 31, 63, 11, 46, 47, 107, 121, 136, 12, 72, 84, 100, 76, 115, 117, 12, 120};

	std::vector<int> evals = exp.evaluation(ag, maze, algorithm, epsilon, starting_states);

	std::cout << "\n===> EVALUATION OF Q LEARNING" << std::endl;
	algorithm = 1;
	//exp1.evaluation(ag1, maze, epsilon, algorithm);
	std::vector<int> evals1 = exp1.evaluation(ag1, maze, algorithm, epsilon, starting_states);

	std::cout << "\n===> EVALUATION OF DOUBLE Q LEARNING" << std::endl;
	algorithm = 2;
	//exp2.evaluation(ag2, maze, epsilon, algorithm);
	std::vector<int> evals2 = exp2.evaluation(ag2, maze, algorithm, epsilon, starting_states);

	std::cout << "\n===> EVALUATION OF QV LEARNING" << std::endl;
	algorithm = 3;
	//exp3.evaluation(ag3, maze, epsilon, algorithm);
	std::vector<int> evals3 = exp3.evaluation(ag3, maze, algorithm, epsilon, starting_states);

	// ==========================================================
	// ================= FILLING EVALUATION FILE ================
	// ==========================================================

	std::ofstream myfile_evals;
	myfile_evals.open("data/data_evals.txt");
	myfile_evals << "step,SARSA,Q_learning,double_Q_learning,QV_learning\n";
	for (int i = 0; i < (int)starting_states.size(); i++) {
		myfile_evals << i <<"," << evals[i] << "," << evals1[i] << "," << evals2[i] << "," << evals3[i] << "\n";
	}*/

	//myfile_evals.close();

	//delete[] average_steps_sarsa;
	/*delete[] average_steps_q_learning;
	delete[] average_steps_double_q_learning;
	delete[] average_steps_qv;

	delete[] std_average_steps_sarsa;
	delete[] std_average_steps_q_learning;
	delete[] std_average_steps_double_q_learning;
	delete[] std_average_steps_qv;

	delete[] average_returns_sarsa;
	delete[] average_returns_q_learning;
	delete[] average_returns_double_q_learning;
	delete[] average_returns_qv;*/

	myfile.close();
	returns_data.close();

	return 0;
}
