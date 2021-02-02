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
        double* returns_each_experiment;

        double* average_steps;
        double* std_average_steps;
        double* average_returns;
        double* std_average_returns;

        double T;
        double retur = 0;

        int reward_strategy = 0;

    Experiment(int n_r, int n_exp, double Ti);

    ~Experiment();

    void set_reward_strategy(int r);

    void set_T(int t);

    int single_run_SARSA(Agent &ag, Environment & env, int exploration_strategy);

    int single_run_QL(Agent &ag, Environment & env, int exploration_strategy);

    int single_run_double_QL(Agent &ag, Environment &env, int exploration_strategy);

    int single_run_QV(Agent &ag, Environment &env, int exploration_strategy);

    int take_action(Agent &ag, int s, std::vector<int> allow_act, int algoithm, int exploration_strategy);

    void learning(Agent &ag, Environment & env, int experiment_number, int algorithm, int exploration_strategy);

    int single_eval(Agent &ag, Environment & env, double epsilon_evaluation, int algorithm, int starting_state);
   
    std::vector<int> evaluation(Agent &ag, Environment & env, int algorithm, int epsilon_evaluation, std::vector<int> starting_states);

    void more_experiments(Agent &ag, Environment & env, int algorithm, int exploration_strategy);

    double* compute_average_steps();

    double* compute_average_returns();

    double* get_std_average_steps();

    double* get_std_average_returns();

};

#endif
