#include "Agent.h"
#include <iostream>
#include <random>
#include <algorithm>

Agent::Agent(int n_stat, int n_act, double e, double l, double d, int s, int lam){
    n_states = n_stat;
    n_actions = n_act;
    epsilon = e;
    learning_rate = l;
    discount_rate = d;
    starting_state = s;
    lambda = lam;

    Q = new double[n_states*n_actions];
    V = new double[n_states];
    et = new double[n_states];
    QA = new double[n_states*n_actions];
    QB = new double[n_states*n_actions];
    Q_temperature = new double[n_states*n_actions];
    UCB_values = new double[n_states*n_actions];
    nt = new int[n_states*n_actions];

    for (int i=0; i<n_states; i++){
        V[i] = 0;
        et[s] = 0;
        for (int j=0; j<n_actions; j++){
            Q[i*n_actions+j] = 0;
            QA[i*n_actions+j]= 0;
            QB[i*n_actions+j] = 0;
            Q_temperature[i*n_actions+j] = 0;
            UCB_values[i*n_actions+j] = 0;
            nt[i*n_actions+j] = 0;
        }
    }
};

Agent::~Agent(){
    delete[] Q;
    delete[] V;
    delete[] et;
    delete[] QA;
    delete[] QB;
    delete[] Q_temperature;
    delete[] UCB_values;
    delete[] nt;
};

int Agent::get_initial_state(){
    return starting_state;
};

void Agent::set_initial_state(int s){
    starting_state = s;;
};

void Agent::set_epsilon(double e){
    epsilon = e;
};

double* Agent::get_Q(){
    return Q;
};

double* Agent::get_QA(){
    return QA;
};

double* Agent::get_QB(){
    return QB;
};

int Agent::epsilon_greedy(int state, std::vector<int> allowed_actions, int algorithm){
    int act = 0;

    double rand_num = ((double) rand() / (RAND_MAX));

    if (rand_num < epsilon){       //random action
        act = allowed_actions[rand() % allowed_actions.size()];
    } else {                       //greedy action
        int max_idx = allowed_actions[0];
        double max_val;

        if (algorithm == 0 || algorithm == 1 || algorithm == 3) { // SARSA or Q_LEARNING or QV_LEARNING
            max_val = Q[state*n_actions+allowed_actions[0]];
        } else if (algorithm == 2) { // double Q_learning
            max_val = QA[state*n_actions+allowed_actions[0]]+QB[state*n_actions+allowed_actions[0]];
        }

        for (int j=0; j<n_actions; j++){    
            if (std::find(allowed_actions.begin(), allowed_actions.end(), j) != allowed_actions.end()) {
                //std::cout<<"action "<<j<<" is present in the actions array"<<std::endl;
                if (algorithm == 0 || algorithm == 1 || algorithm == 3) { // SARSA or Q_LEARNING or QV_LEARNING
                    if (Q[state*n_actions + j] > max_val){
                        max_val = Q[state*n_actions + j];
                        max_idx = j;
                    }
                }  else if (algorithm == 2) { // double Q_learning
                    if (QA[state*n_actions + j]+QB[state*n_actions + j] > max_val){
                        max_val = QA[state*n_actions + j]+QB[state*n_actions + j];
                        max_idx = j;
                    }
                }
                
            }
        }
        act = max_idx;
    }
    return act;
};

int Agent::boltzmann_exploration(int state, std::vector<int> allowed_actions, int algorithm, double T){

    int act = 0;
    double max_val = 0;
    double denom = 0;
    double Qvalue = 0;

    std::vector<double> weights;

    for (int i=0; i<n_actions; i++){
        if (std::find(allowed_actions.begin(), allowed_actions.end(), i) != allowed_actions.end()) {
            if (algorithm == 3){
                Qvalue = QA[state*n_actions+i]+QB[state*n_actions+i];
                Q_temperature[state*n_actions+i] = Qvalue/T;
                if ( Qvalue > max_val){
                    max_val = Qvalue;
                }            
            } else {
                Q_temperature[state*n_actions+i] = Q[state*n_actions+i]/T;
                if (Q[state*n_actions+i] > max_val){
                    max_val = Q[state*n_actions+i];
                }
            }
        }
    }
    
    for (int i=0; i<n_actions; i++){
        if (std::find(allowed_actions.begin(), allowed_actions.end(), i) != allowed_actions.end()) {
            denom += exp(Q_temperature[state*n_actions+i] - max_val);
        }
    }

    for (int i=0; i<n_actions; i++){
        if (std::find(allowed_actions.begin(), allowed_actions.end(), i) != allowed_actions.end()) {
            weights.push_back(exp(Q_temperature[state*n_actions+i] - max_val)/denom);
        }
        else {
            weights.push_back(0); // CHRCK IF 0 IS OKAY TO BE PUT INT HE VECTOR
        }
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::discrete_distribution<int> distribution (weights.begin(), weights.end());
    act = distribution(generator);

    return act;
};

int Agent::UCB(int state, std::vector<int> allowed_actions, int algorithm, int t, double c){

    int act = 0;

    for (int j=0; j<n_actions; j++){
        if (std::find(allowed_actions.begin(), allowed_actions.end(), j) != allowed_actions.end()) {
            if (nt[j] != 0){
                if (algorithm ==3){
                    UCB_values[state*n_actions+j] = QA[state*n_actions+j]+QB[state*n_actions+j] + c*sqrt(log(float(t))/nt[state*n_actions+j]);
                } else {
                    UCB_values[state*n_actions+j] = Q[state*n_actions+j] + c*sqrt(log(float(t))/nt[state*n_actions+j]);
                }
            }
            else{
                UCB_values[state*n_actions+j] = 10000;
            }
        }
    }
    for (int j=0; j<n_actions; j++){
        std::cout<<"value j="<<j<<UCB_values[state*n_actions+j]<<std::endl;
    }
    act = std::distance(UCB_values + state*n_actions, std::max_element(UCB_values + state*n_actions, UCB_values + state*n_actions + n_actions));

    std::cout<<"chosen action="<<act<<std::endl;
    
    nt[state*n_actions+act] += 1;

    return act;
};

void Agent::initialize_Q(){
    for (int i=0; i<n_states*n_actions; i++){
        Q[i] = 0;
        Q_temperature[i] = 0;
    }
};

void Agent::initialize_QA_QB(){
    for (int i=0; i<n_states*n_actions; i++){
        QA[i] = 0;
        QB[i] = 0;
    }
};

void Agent::initialize_V(){
    for (int i=0; i<n_states; i++){
        V[i] = 0;
    }
};

void Agent::update_Q_SARSA(int s, int a, double reward, int s_next, int a_next){
    Q[s*n_actions+a] += learning_rate*(reward + discount_rate*Q[s_next*n_actions + a_next] - Q[s*n_actions+a]);
};

void Agent::update_Q_Learning(int s, int a, double reward, int s_next, std::vector<int> allowed_actions_s_next) {

	int maximizing_action = allowed_actions_s_next[0];
	double max_val = Q[s_next*n_actions + maximizing_action];

	for (int j = 0; j < n_actions; j++) {
		if (std::find(allowed_actions_s_next.begin(), allowed_actions_s_next.end(), j) != allowed_actions_s_next.end()) {

			if (Q[s_next*n_actions + j] > max_val) {
				max_val = Q[s_next*n_actions + j];
				maximizing_action = j;
			}
		}
	}
	Q[s*n_actions+a] += learning_rate*(reward + discount_rate*Q[s_next*n_actions + maximizing_action] - Q[s*n_actions+a]);
};

void Agent::update_Q_final(int s, int a, double reward){ // both for SARSA and Q learning
    Q[s*n_actions+a] += learning_rate*(reward - Q[s*n_actions+a]);
};

void Agent::update_QA_QB(int s, int a, double reward, int s_next, std::vector<int> allowed_actions, int update_index){

	int maximizing_action = allowed_actions[0];
    double max_val;

    //if (s==22|| s==14 || s==15 || s == 7){
        //std::cout<<"s="<<s<<", a="<<a<<", s_next="<<s_next<<std::endl;
    //}

    if (update_index == 0){  // 0 == QA
    	max_val = QA[s_next*n_actions + allowed_actions[0]];
    } else if (update_index == 1){  // 1 == QB
	    max_val = QB[s_next*n_actions + allowed_actions[0]];
    }

	for (int j = 0; j < n_actions; j++) {
		if (std::find(allowed_actions.begin(), allowed_actions.end(), j) != allowed_actions.end()) {
			//std::cout<<"action "<<j<<" is present in the actions array"<<std::endl;
            if (update_index == 0){  // 0 == QA
                if (QA[s_next*n_actions + j] > max_val) {
                    max_val = QA[s_next*n_actions + j];
                    maximizing_action = j;
                }
            } else if (update_index == 1){  // 1 == QB
                if (QB[s_next*n_actions + j] > max_val) {
                    max_val = QB[s_next*n_actions + j];
                    maximizing_action = j;
                }
            }
	    }
    }
    //if (s==22|| s==14 || s==15 || s == 7){
        /*std::cout<<"maximizing action in s_next="<<maximizing_action<<std::endl;
        std::cout<<"QA[s*n_actions + a]="<<QA[s*n_actions + a]<<std::endl;
        std::cout<<"QB[s*n_actions + a]="<<QB[s*n_actions + a]<<std::endl;
        std::cout<<"QA[s_next*n_actions + maximizing_action]="<<QA[s_next*n_actions + maximizing_action]<<std::endl;
        std::cout<<"QB[s_next*n_actions + maximizing_action]="<<QB[s_next*n_actions + maximizing_action]<<std::endl;
        std::cout<<"proceed with update..."<<std::endl;*/
    //}

    if (update_index == 0){  // 1 == QA
	    QA[s*n_actions + a] += learning_rate * (reward + discount_rate*QB[s_next*n_actions + maximizing_action] - QA[s*n_actions + a]);
    } else if (update_index == 1){  // 1 == QB
        QB[s*n_actions + a] += learning_rate * (reward + discount_rate*QA[s_next*n_actions + maximizing_action] - QB[s*n_actions + a]);
    }
    //if (s==22|| s==14 || s==15 || s == 7){
    /*    std::cout<<"...done"<<std::endl;
        std::cout<<"QA[s*n_actions + a]="<<QA[s*n_actions + a]<<std::endl;
        std::cout<<"QB[s*n_actions + a]="<<QB[s*n_actions + a]<<std::endl;
        std::cout<<std::endl;*/
    //}
};

void Agent::update_QA_QB_final(int s, int a, double reward){
    for (int aa=0; aa<4; aa++){
        QA[s*n_actions+aa] += learning_rate*(reward - QA[s*n_actions+aa]);
        QB[s*n_actions+aa] += learning_rate*(reward - QB[s*n_actions+aa]);
    }
};


void Agent::update_QV(int s, int a, double reward, int s_new){
    delta = reward + discount_rate*V[s_new] - V[s];
    et[s] = discount_rate*lambda*et[s] + 1; // eta[s];
    V[s] += learning_rate*delta*et[s];
    Q[s*n_actions + a] += learning_rate * (reward + discount_rate*V[s_new] - Q[s*n_actions + a]);
};

void Agent::update_QV_final(int s, int a, double reward){
    delta = reward - V[s];
    et[s] = discount_rate*lambda*et[s] + 1; // eta[s];
    V[s] += learning_rate*delta*et[s];
    Q[s*n_actions + a] += learning_rate * (reward - Q[s*n_actions + a]);
};

void Agent::print(double *matrix, int n_rows, int n_cols){
    for (int i=0; i<n_rows; i++){
        std::cout<<"state "<<i<<"  ";
        for (int j=0; j<n_cols; j++){
            std::cout<<matrix[i*n_actions+j]<<"  ";
        }
        std::cout<<std::endl;
    }
};