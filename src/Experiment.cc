#include "Experiment.h"

void Experiment::single_run(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    double rew = 0;

    for (int i=0; i<run_length; i++){
        a = ag.agent_step_epsilon_greedy(rew, s);
        rew = env.sample_reward(a);
        s_new = env.next_state(s, a);
        a_new = ag.agent_step_epsilon_greedy(rew, s_new);
    }

}