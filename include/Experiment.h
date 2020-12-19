#ifndef EXPERIMENT
#define EXPERIMENT

#include "Agent.h"
#include "Environment.h"


class Experiment{

    public:
        int run_length;

    Experiment();

    void single_run(Agent &ag, Environment & env);

};

#endif