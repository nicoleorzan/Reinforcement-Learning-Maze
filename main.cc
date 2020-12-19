#include "Agent.h"
//#include "Experiment.h"

int main(){

    double epsilon = 0.05;
    double learning_rate = 0.7;
    double discount_rate = 0.99;
    int n_actions = 4;
    int n_states = 8;

    // in this way I can define a new agent
    Agent agent(n_states, n_actions, epsilon, learning_rate, discount_rate);

    return 0;
}