#ifndef EXPERIMENT
#define EXPERIMENT

#include "Agent.h"
#include "Environment.h"

class Experiment{

    public:
        int n_runs;
        int n_experiments;
        int* num_steps_runs;
        int* num_steps_each_experiment;
        int* average_steps;

        double T;
        double c;

    Experiment(int n_r, int n_exp, double Ti, double ci);

    ~Experiment();

    int single_run_SARSA(Agent &ag, Environment & env, int exploration_strategy);

    int single_run_QL(Agent &ag, Environment & env, int exploration_strategy);

    //int single_run_DYNAQ(Agent &ag, Environment & env, int exploration_strategy);

    int single_run_double_QL(Agent &ag, Environment &env, int exploration_strategy);

    int single_run_QV(Agent &ag, Environment &env, int exploration_strategy);

    //int single_run_semi_gradient_SARSA(Agent &ag, Environment &env, int exploration_strategy);



    void more_runs(Agent &ag, Environment & env, int experiment_number, int algorithm,  int exploration_strategy);

    void run_more_experiments(Agent &ag, Environment & env, int algorithm, int exploration_strategy);

    std::vector<int> run_more_evaluations(Agent &ag, Environment & env, int algorithm, int epsilon, std::vector<int> starting_states);

    int* compute_average();


    int evaluation(Agent &ag, Environment & env, double epsilon, int algorithm, int starting_state);
};

#endif