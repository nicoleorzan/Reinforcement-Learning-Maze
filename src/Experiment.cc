#include "Experiment.h"

Experiment::Experiment(int r){
    run_length = r;
}

void Experiment::single_run(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    double rew = 0;

    s = ag.get_initial_state();
    a = ag.agent_start();
    for (int i=0; i<run_length; i++){
        rew = env.sample_reward(a);
        s_new = env.next_state(s, a);
        a_new = ag.agent_step_epsilon_greedy(rew, s_new);
        ag.SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;
    }
    rew = env.sample_reward(a);
    ag.SARSA_final(s, a, rew);

}