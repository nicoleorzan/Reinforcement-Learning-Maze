#include "Agent.h"
#include <iostream>
#include <random>
#include <algorithm>

Agent::Agent(int n_stat, int n_act, double e, double l, double d, int s){
    n_states = n_stat;
    n_actions = n_act;
    epsilon = e;
    learning_rate = l;
    discount_rate = d;
    starting_state = s;

    Q = new double[n_states*n_actions];
    Q_temperature = new double[n_states*n_actions];
    for (int i=0; i<n_states*n_actions; i++){
        Q[i] = 0;
        Q_temperature[i] = 0;
    }
};

Agent::~Agent(){
    delete[] Q;
    delete[] Q_temperature;
};

int Agent::get_initial_state(){
    return starting_state;
}

int Agent::agent_start(){
   return rand() % (( n_actions ));
};

int Agent::agent_step_epsilon_greedy(int state){
    int act = 0;

    double rand_num = ((double) rand() / (RAND_MAX));
    //std::cout<<"rand num="<<rand_num<<std::endl;
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

int Agent::agent_Boltzmann_exploration(int state, double T){

    int action = 0;
    double max_val = 0;
    double denom = 0;
    
    std::vector<double> weights;

    for (int i=0; i<n_actions; i++){
        Q_temperature[state*n_actions+i] = Q[state*n_actions+i]/T;
        if (Q[state*n_actions+i] > max_val){
            max_val = Q[state*n_actions+i];
        }
    }
    
    for (int i=0; i<n_actions; i++){
        denom += exp(Q_temperature[state*n_actions+i] - max_val);
    }

    for (int i=0; i<n_actions; i++){
        weights.push_back(exp(Q_temperature[state*n_actions+i] - max_val)/denom);
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::discrete_distribution<int> distribution (weights.begin(), weights.end());
    action = distribution(generator);

    return action;


};

void Agent::SARSA(int s, int a, double reward, int s_next, int a_next){
    Q[s*n_actions+a] += learning_rate*(reward + discount_rate*Q[s_next*n_actions + a_next] - Q[s*n_actions+a]);
};

void Agent::SARSA_final(int s, int a, double reward){
    Q[s*n_actions+a] += learning_rate*(reward - Q[s*n_actions+a]);
};

void Agent::print_Q(){
    for (int i=0; i<n_states; i++){
        for (int j=0; j<n_actions; j++){
            std::cout<<Q[i*n_actions+j]<<"  ";
        }
        std::cout<<std::endl;
    }
}
