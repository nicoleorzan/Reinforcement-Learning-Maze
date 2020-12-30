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

    int single_run(Agent &ag, Environment & env);

    void single_run_Boltzmann(Agent &ag, Environment & env, double T);

    void more_runs(Agent &ag, Environment & env, int experiment_number);

    void more_experiments(Agent &ag, Environment & env);

    void more_Boltzmann_exploration_runs(Agent &ag, Environment & env, double T);

    void evaluation(Agent &ag, Environment & env);

    void compute_average();
};

#endif