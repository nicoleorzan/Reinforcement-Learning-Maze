#include "Agent.h"
#include "Experiment.h"
#include "Environment.h"
#include <iostream>
#include <fstream>
#include "time.h"

#define N 8

#define TCPU_TIME (clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &ts ), (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9)

int main() {

	double epsilon = 0.1;
	double learning_rate = 0.1;
	double discount_rate = 0.99;
	int n_actions = 4; // up, down, left, right
	int n_states = N * N;
	int starting_state = 56;
	int final_state = 7;
	int num_runs = 200; 
	int num_experiments = 100;
	double lambda = 0;
	int* average_steps_sarsa = new int[num_runs];
	int* average_steps_q_learning = new int[num_runs];
	int* average_steps_double_q_learning = new int[num_runs];
	int* average_steps_qv = new int[num_runs];
	double c = 0.1; //big c -> more exploration
	double T = 0.01;

	// timing-related variables
	double tstart, tstop, ctime;
	struct timespec ts;

	if (starting_state < 0 || starting_state >= N * N || final_state < 0 || final_state >= N * N) {
		std::cout << "Initial or final state outside the maze borders\n";
		return -1;
	}

	std::ofstream myfile;
	myfile.open("data.txt");
	myfile << "epsilon = " << epsilon << "\n" << "learning_rate = " << learning_rate << "\n" << "discount_rate = " << discount_rate << "\n" << "lambda = " << lambda << "\n" << "c = " << c << "\n" << "T = " << T << "\n";
	myfile << "SARSA   Q_learning   double_Q_learning   QV_learning\n";

	// Define the maze
	Environment maze(N, starting_state, final_state);
	maze.display_maze();

	// =============== RUN SARSA ===================
	std::cout << "\n===> RUNNING SARSA" << std::endl;
	int algorithm = 0; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV
	int exploraton_strategy = 2; // 0 = epsilon-greedy; 1 = boltzmann, 2 = UCB

	Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp(num_runs, num_experiments, T, c);
	exp.run_more_experiments(ag, maze, algorithm, exploraton_strategy);
	average_steps_sarsa = exp.compute_average();

	//ag.print(ag.get_Q(), n_states, n_actions);
	std::cout << "\nPrinting final policy obtained from SARSA:" << std::endl;
	maze.print_policy(ag.get_Q());

	// =============== RUN Q LEARNING ================
	std::cout << "\n===> RUNNING Q LEARNING" << std::endl;
	algorithm = 1;

	Agent ag1(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp1(num_runs, num_experiments, T, c);
	exp1.run_more_experiments(ag1, maze, algorithm, exploraton_strategy);
	average_steps_q_learning = exp1.compute_average();

	//ag1.print(ag1.get_Q(), n_states, n_actions);    
	std::cout << "\nPrinting final policy obtained from Q learning:" << std::endl;
	maze.print_policy(ag1.get_Q());

	// =============== RUN DOUBLE Q LEARNING ================
	std::cout << "\n===> RUNNING DOUBLE Q LEARNING" << std::endl;
	algorithm = 2;

	Agent ag2(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp2(num_runs, num_experiments, T, c);
	exp2.run_more_experiments(ag2, maze, algorithm, exploraton_strategy);
	average_steps_double_q_learning = exp2.compute_average();

	/*ag2.print(ag2.get_QA(), n_states, n_actions);
	std::cout<<std::endl;
	ag2.print(ag2.get_QB(), n_states, n_actions);
	*/
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

	//ag3.print(ag3.get_Q(), n_states, n_actions);
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

	std::cout << "Performing evaluation with greedy policy with starting state:" << starting_state << std::endl;
	epsilon = 0;

	std::cout << "\n===> EVALUATION OF SARSA" << std::endl;
	algorithm = 0;
	exp.evaluation(ag, maze, epsilon, algorithm, starting_state);

	std::cout << "\n===> EVALUATION OF Q LEARNING" << std::endl;
	algorithm = 1;
	exp1.evaluation(ag1, maze, epsilon, algorithm, starting_state);

	std::cout << "\n===> EVALUATION OF DOUBLE Q LEARNING" << std::endl;
	algorithm = 2;
	exp2.evaluation(ag2, maze, epsilon, algorithm, starting_state);

	std::cout << "\n===> EVALUATION OF QV LEARNING" << std::endl;
	algorithm = 3;
	exp3.evaluation(ag3, maze, epsilon, algorithm, starting_state);


	//==============================================================================
	//==============================================================================
	//==============================================================================

	/*std::cout<<"\n======================\nTrying Boltzmann exploration\n======================\n"<<std::endl;
	// =============== RUN SARSA ===================
	std::cout<<"\n===> RUNNING SARSA"<<std::endl;
	num_runs = 100;
	algorithm = 0; // algorithm number: 0=SARSA, 1=Q_learning, 2=double Q_learning, 3=QV
	exploraton_strategy = 1; // 0=epsilon-greedy; 1=boltzmann, 2=UCB
	T = 0.5;

	ag.initialize_Q();
	//Agent ag(n_states, n_actions, epsilon, learning_rate, discount_rate, starting_state, lambda);
	Experiment exp_new_1(num_runs, num_experiments, T, c);

	tstart = TCPU_TIME;
	exp_new_1.run_more_experiments(ag, maze, algorithm, exploraton_strategy);
	ctime = TCPU_TIME - tstart;
	std::cout<<"time="<<ctime<<std::endl;
	average_steps_sarsa = exp.compute_average();

	//ag.print(ag.get_Q(), n_states, n_actions);
	std::cout<<"\nPrinting final policy obtained from SARSA:"<<std::endl;
	maze.print_policy(ag.get_Q());*/




	myfile.close();
	delete[] average_steps_sarsa;
	//delete[] average_steps_q_learning;
	//delete[] average_steps_double_q_learning;
	// delete[] average_steps_qv;

	return 0;
}
