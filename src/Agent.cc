#include "Agent.h"
#include <iostream>


Agent::Agent(int n_stat, int n_act, double e, double l, double d){
    n_states = n_stat;
    n_actions = n_act;
    epsilon = e;
    learning_rate = l;
    discount_rate = d;

    Q = new double[n_stat];
};

Agent::~Agent(){
    delete[] Q;
}

//void Agent::agent_init(){
// };

int Agent::agent_start(int state){

};

int Agent::agent_step_epsilon_greedy(double reward, int state){
    int act = 0;
    return act;
};

void Agent::agent_end(double reward){

};

