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

    Experiment(int n_r, int n_exp);

    ~Experiment();

    int single_run_SARSA(Agent &ag, Environment & env);

    int single_run_QL(Agent &ag, Environment & env);

    int single_run_double_QL(Agent &ag, Environment &env);

    int single_run_QV(Agent &ag, Environment &env);


    void more_runs(Agent &ag, Environment & env, int experiment_number, int algorithm);

    void more_experiments(Agent &ag, Environment & env, int algorithm);

    void evaluation_SARSA(Agent &ag, Environment & env, int algorithm);

    int* compute_average();


    //void single_run_Boltzmann(Agent &ag, Environment & env, double T);

    //void more_Boltzmann_exploration_runs(Agent &ag, Environment & env, double T);
};

#endif