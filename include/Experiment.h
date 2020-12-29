#ifndef EXPERIMENT
#define EXPERIMENT

#include "Agent.h"
#include "Environment.h"

class Experiment{

    public:
        int n_runs;

    Experiment(int n_r);

    void single_run(Agent &ag, Environment & env);

    void single_run_Boltzmann(Agent &ag, Environment & env, double T);

    void more_runs(Agent &ag, Environment & env);

    void more_Boltzmann_exploration_runs(Agent &ag, Environment & env, double T);

    void evaluation(Agent &ag, Environment & env);

};

#endif