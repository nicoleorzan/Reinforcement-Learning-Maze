#include "Agent.h"
#include <iostream>


Agent::Agent(int n_stat, int n_act, double e, double l, double d, int s){
    n_states = n_stat;
    n_actions = n_act;
    epsilon = e;
    learning_rate = l;
    discount_rate = d;
    starting_state = s;

    Q = new double[n_states*n_actions];
    for (int i=0; i<n_states*n_actions; i++){
        Q[i] = 0;
    }
};

Agent::~Agent(){
    delete[] Q;
};

int Agent::get_initial_state(){
    return starting_state;
}

int Agent::from_ij_to_idx(int state_i, int state_j){
    return state_i + n_actions*state_j;
}

int Agent::agent_start(){
   return rand() % (( n_actions ));
};

int Agent::agent_step_epsilon_greedy(double reward, int state){
    int act = 0;

    double rand_num = ((double) rand() / (RAND_MAX));
    if (rand_num < epsilon){       //random action
        act = rand() % (( n_actions ));
    } else {                       //greedy action
        int max_idx = 0;
        double max_val = 0;
        for (int j=0; j<n_actions; j++){
            if (Q[state*n_actions + j] > max_val){
                max_val = Q[state*n_actions + j];
                max_idx = j;
            }
        }
        act = max_idx;
    }
    return act;
};

void Agent::SARSA(int s, int a, double reward, int s_next, int a_next){
    Q[s*n_actions+a] += learning_rate*(reward + discount_rate*Q[s_next*n_actions + a_next] - Q[s*n_actions+a]);
};

void Agent::SARSA_final(int s, int a, double reward){
    Q[s*n_actions+a] += learning_rate*(reward - Q[s*n_actions+a]);
};

