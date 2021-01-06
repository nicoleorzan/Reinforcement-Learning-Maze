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

    int single_run_double_QL(Agent &ag, Environment &env, int exploration_strategy);

    int single_run_QV(Agent &ag, Environment &env, int exploration_strategy);


    void more_runs(Agent &ag, Environment & env, int experiment_number, int algorithm,  int exploration_strategy);

    void run_more_experiments(Agent &ag, Environment & env, int algorithm, int exploration_strategy);

    int* compute_average();


    void evaluation(Agent &ag, Environment & env, double epsilon, int algorithm);

    void single_run_SARSA_random(Agent &ag, Environment & env, int num_steps);

    void single_run_QL_random(Agent &ag, Environment & env, int num_steps);


    //void single_run_Boltzmann(Agent &ag, Environment & env, double T);

    //void more_Boltzmann_exploration_runs(Agent &ag, Environment & env, double T);
};

#endif