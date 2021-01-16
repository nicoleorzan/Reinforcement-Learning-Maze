#include "Experiment.h"
#include <iostream>
#include "stdlib.h"
#include <math.h>

Experiment::Experiment(int n_r, int n_exp, double Ti){ 
    n_runs = n_r;
    n_experiments = n_exp;
    num_steps_runs = new int[n_runs];
    num_steps_each_experiment = new int[n_experiments*n_runs];
    returns_each_experiment = new double[n_experiments*n_runs];
    average_steps = new double[n_runs];
    std_average_steps = new double[n_runs];
    average_returns = new double[n_runs];
    std_average_returns = new double[n_runs];

    T = Ti;
    c = 0;
};

Experiment::~Experiment(){
    delete[] num_steps_runs;
    delete[] num_steps_each_experiment;
    delete[] returns_each_experiment;
    delete[] average_steps;
    delete[] std_average_steps;
    delete[] average_returns; 
    delete[] std_average_returns;
};

void Experiment::set_reward_strategy(int r){
    if (r==0 || r==1){
        reward_strategy = r;
    }
}

int Experiment::take_action(Agent &ag, int s, std::vector<int> allow_act, int algorithm, int exploration_strategy){

    int a = 0;

    if (exploration_strategy == 0){
        a = ag.epsilon_greedy(s, allow_act, algorithm);  // 1 == Q_LEARNING
    } else if (exploration_strategy == 1){
        a = ag.boltzmann_exploration(s, allow_act, algorithm, T);  // 1 == Q_LEARNING  
    }   

    return a;
};

int Experiment::single_run_SARSA(Agent &ag, Environment &env, int exploration_strategy){

    int algorithm = 0;
    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;
    this->retur = 0;

    s = env.random_start();
    ag.set_initial_state(s);
    allow_act = { 0,1,2,3 };
    //allow_act = env.allowed_actions(s);
    
    a = take_action(ag, s, allow_act, algorithm, exploration_strategy);

    int i=1;
    while (i){

        rew = env.sample_reward(s, reward_strategy);
        if (s == env.get_final_state()){
            ag.update_Q_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //allow_act = env.allowed_actions(s_new);

        a_new = take_action(ag, s, allow_act, algorithm, exploration_strategy);

        ag.update_Q_SARSA(s, a, rew, s_new, a_new);

        a = a_new;
        s = s_new;       
        i += 1;
        retur += rew;

    }

    return i + 1;
};

int Experiment::single_run_QL(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0;
    int s = 0, s_new = 0;
    int algorithm = 1;
    std::vector<int> allow_act;
    double rew = 0;
    this->retur = 0;

    s = env.random_start();
    ag.set_initial_state(s);
    //allow_act = env.allowed_actions(s);
    allow_act = { 0,1,2,3 };

    int i=1;
    while (i){

        a = take_action(ag, s, allow_act, algorithm, exploration_strategy);

        rew = env.sample_reward(s, reward_strategy);

        if (s == env.get_final_state()){
            ag.update_Q_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //allow_act = env.allowed_actions(s_new);
        ag.update_Q_Learning(s, a, rew, s_new, allow_act);

        s = s_new;       
        i += 1;
        retur += rew;

    }
    return i + 1;
};

int Experiment::single_run_double_QL(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;
    this->retur = 0;
    int algorithm = 2;

    s = env.random_start();
    ag.set_initial_state(s);
    //allow_act = env.allowed_actions(s);
    allow_act = { 0,1,2,3 };

    int i=1;
    while (i){

        a = take_action(ag, s, allow_act, algorithm, exploration_strategy);
        rew = env.sample_reward(s, reward_strategy);

        if (s == env.get_final_state()){
            ag.update_QA_QB_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //allow_act = env.allowed_actions(s_new);

        if ( ((double) rand() / (RAND_MAX)) < 0.5){
            ag.update_QA_QB(s, a, rew, s_new, allow_act, 0); // 0 == QA
        } else { 
            ag.update_QA_QB(s, a, rew, s_new, allow_act, 1); // 1 == QB
        }
        
        s = s_new;       
        i += 1;
        retur += rew;

    }
    
    return i + 1;
};

int Experiment::single_run_QV(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;
    this->retur = 0;
    int algorithm = 3;

    s = env.random_start();
    ag.set_initial_state(s);
    allow_act = { 0,1,2,3 };

    int i=1;
    while (i){

        //allow_act = env.allowed_actions(s);
        a = take_action(ag, s, allow_act, algorithm, exploration_strategy); 
        rew = env.sample_reward(s, reward_strategy);

        if (s == env.get_final_state()){
            ag.update_QV_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //allow_act = env.allowed_actions(s_new);

        ag.update_QV(s, a, rew, s_new);
        
        s = s_new;       
        i += 1;
        retur += rew;
    }
    return i+1;
};

void Experiment::learning(Agent &ag, Environment &env, int experiment_number, int algorithm, int exp_str){

    if ( algorithm == 0 || algorithm == 1 ) { ag.initialize_Q(); }
    else if ( algorithm == 2 ) { ag.initialize_QA_QB(); }
    else if ( algorithm == 3 ){
        ag.initialize_Q();
        ag.initialize_V();
    }
   
    for (int run_number=0; run_number<n_runs; run_number++){
        //std::cout<<"Run number="<<run_number<<std::endl;
        if (algorithm == 0 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_SARSA(ag, env, exp_str);
        } else if (algorithm == 1 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_QL(ag, env, exp_str);
        } else if (algorithm == 2 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_double_QL(ag, env, exp_str);
        } else if (algorithm == 3 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_QV(ag, env, exp_str);
        }
        // /std::cout<<"return="<<retur<<std::endl;
        returns_each_experiment[experiment_number*n_runs+run_number] = retur;
    }
};

void Experiment::more_experiments(Agent &ag, Environment &env, int algorithm, int exploration_strategy){

    std::cout<<"\nRunning "<<n_experiments<<" experiments, each one of "<<n_runs<<" runs."<<std::endl;

    for (int exp_number=0; exp_number<n_experiments; exp_number++){
        std::cout<<"\nExperiment number="<<exp_number<<std::endl;
        this->learning(ag, env, exp_number, algorithm, exploration_strategy);
    }
};

std::vector<int> Experiment::evaluation(Agent &ag, Environment &env, int algorithm, int epsilon, std::vector<int> starting_states ){

    std::cout<<"\nRunning "<<starting_states.size()<<" evaluations."<<std::endl;
    std::vector<int> evaluation_steps;

    for (int i=0; i<(int)starting_states.size(); i++){
        evaluation_steps.push_back(single_eval(ag, env, epsilon, algorithm, starting_states[i]));
               
    }
    return evaluation_steps;
};

double* Experiment::compute_average_steps(){

    std::cout<<"Computing the average of the steps the agent needs to find the final block. \nAverage is computed on the group of "<<n_experiments<<" experiments.\n\n";
    for (int i=0; i<n_runs; i++){
        average_steps[i] = 0;
        std_average_steps[i] = 0;
        for (int j=0; j<n_experiments; j++){
            average_steps[i] += num_steps_each_experiment[j*n_runs+i]; // CONTROLLARE QUI
        }

        for (int j=0; j<n_experiments; j++){
            std_average_steps[i] += (num_steps_each_experiment[j*n_runs+i]-average_steps[i])*(num_steps_each_experiment[j*n_runs+i]-average_steps[i]); // CONTROLLARE QUI
        }
        average_steps[i] = average_steps[i]/n_experiments;
        std_average_steps[i] = sqrt(std_average_steps[i]/n_experiments);
        //std::cout<<"average steps of run number "<<i<<"= "<<average_steps[i]<<std::endl;
    }
    return average_steps;
};

double* Experiment::compute_average_returns(){

    std::cout<<"Computing the average of the returns the agent obtained in each epsode. \nAverage is computed on the group of "<<n_experiments<<" experiments.\n\n";
    for (int i=0; i<n_runs; i++){
        average_returns[i] = 0;
        std_average_returns[i] = 0;
        for (int j=0; j<n_experiments; j++){
            average_returns[i] += returns_each_experiment[j*n_runs+i];
        }
        for (int j=0; j<n_experiments; j++){
            std_average_returns[i] += (returns_each_experiment[j*n_runs+i]-average_returns[i])*(returns_each_experiment[j*n_runs+i]-average_returns[i]); // CONTROLLARE QUI
        }
        average_returns[i] = average_returns[i]/n_experiments;
        std_average_returns[i] = sqrt(std_average_returns[i]/n_experiments);
        //std::cout<<"average steps of run number "<<i<<"= "<<average_steps[i]<<std::endl;
    }
    return average_returns;
};

double* Experiment::get_std_average_steps(){
    return std_average_steps;
};

double* Experiment::get_std_average_returns(){
    return std_average_returns;
};

int Experiment::single_eval(Agent &ag, Environment &env, double epsilon, int algorithm, int starting_state){

    int s = 0, a = 0;
    std::vector<int> allow_act;

    ag.set_epsilon(epsilon);

    s = starting_state;

    int i=1;
    while (i){

        allow_act = env.allowed_actions(s);
        a = ag.epsilon_greedy(s, allow_act, algorithm);
        //std::cout<<"s="<<s<<", a="<<a<<std::endl; 

        if (s == env.get_final_state()){
            break;
        }
        s = env.next_state(s, a);

        i += 1;
    }
    //std::cout<<"final number of steps="<<i-1<<std::endl;
    return i-1;
};
