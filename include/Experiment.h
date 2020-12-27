#ifndef EXPERIMENT
#define EXPERIMENT

#include "Agent.h"
#include "Environment.h"

class Experiment{

    public:
        int n_runs;

    Experiment(int n_r);

    void single_run(Agent &ag, Environment & env);

    void more_runs(Agent &ag, Environment & env);

    void evaluation(Agent &ag, Environment & env);

};

#endif