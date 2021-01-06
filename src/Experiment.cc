#include "Experiment.h"
#include <iostream>
#include "stdlib.h"

Experiment::Experiment(int n_r, int n_exp, double Ti, double ci){ 
    n_runs = n_r;
    n_experiments = n_exp;
    num_steps_runs = new int[n_runs];
    num_steps_each_experiment = new int[n_experiments*n_runs];
    average_steps = new int[n_runs];

    T = Ti;
    c = ci;
};

Experiment::~Experiment(){
    delete[] num_steps_runs;
    delete[] num_steps_each_experiment;
};

int Experiment::single_run_SARSA(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    if (exploration_strategy==0){
        a = ag.epsilon_greedy(s, allow_act, 0);  // 0 == SARSA
    } else if (exploration_strategy == 1){
        a = ag.boltzmann_exploration(s, allow_act, 0, T);  // 0 == SARSA        
    } else if (exploration_strategy == 2){
        a = ag.UCB(s, allow_act, 0, 1, c);  // 0 == SARSA                
    }

    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            ag.update_Q_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);

        if (exploration_strategy==0){
            a_new = ag.epsilon_greedy(s, allow_act, 0);  // 0 == SARSA
        } else if (exploration_strategy == 1){
            a_new = ag.boltzmann_exploration(s, allow_act, 0, T);  // 0 == SARSA        
        } else if (exploration_strategy == 2){
            a_new = ag.UCB(s, allow_act, 0, i, c);  // 0 == SARSA                
        }

        ag.update_Q_SARSA(s, a, rew, s_new, a_new);

        a = a_new;
        s = s_new;       
        i += 1;
    }
    return i-1;
};

int Experiment::single_run_QL(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);

    int i=1;
    while (i){
        
        if (exploration_strategy == 0){
            a = ag.epsilon_greedy(s, allow_act, 1);  // 1 == Q_LEARNING
        } else if (exploration_strategy == 1){
            a = ag.boltzmann_exploration(s, allow_act, 1, T);  // 1 == Q_LEARNING      
        } else if (exploration_strategy == 2){
            a = ag.UCB(s, allow_act, 1, 1, c); // 1 == Q_LEARNING               
        }

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            ag.update_Q_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);
        ag.update_Q_Learning(s, a, rew, s_new, allow_act);

        s = s_new;       
        i += 1;
    }
    return i-1;
};


int Experiment::single_run_double_QL(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state(); 
    allow_act = env.allowed_actions(s);

    int i=1;
    while (i){

        //a = ag.epsilon_greedy(s, allow_act, 2); // 2 == double Q leaning
        if (exploration_strategy==0){
            a = ag.epsilon_greedy(s, allow_act, 2);  // 2 == double Q leaning
        } else if (exploration_strategy == 1){
            a = ag.boltzmann_exploration(s, allow_act, 2, T); // 2 == double Q leaning     
        } else if (exploration_strategy == 2){
            a = ag.UCB(s, allow_act, 2, i, c); // 2 == double Q leaning           
        }
        rew = env.sample_reward(s);

        if (s == env.get_final_state()){
            ag.update_QA_QB_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);

        if ( ((double) rand() / (RAND_MAX)) < 0.5){
            ag.update_QA_QB(s, a, rew, s_new, allow_act, 0); // 0 == QA
        } else { 
            ag.update_QA_QB(s, a, rew, s_new, allow_act, 1); // 1 == QB
        }
        
        s = s_new;       
        i += 1;
    }
    return i-1;
};

int Experiment::single_run_QV(Agent &ag, Environment &env, int exploration_strategy){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state(); 

    int i=1;
    while (i){

        allow_act = env.allowed_actions(s);
        //a = ag.epsilon_greedy(s, allow_act, 3);
        if (exploration_strategy==0){
            a = ag.epsilon_greedy(s, allow_act, 3); // 3 == QV leaning
        } else if (exploration_strategy == 1){
            a = ag.boltzmann_exploration(s, allow_act, 3, T);  // 3 == QV leaning      
        } else if (exploration_strategy == 2){
            a = ag.UCB(s, allow_act, 3, i, c);   // 3 == QV leaning       
        }
        rew = env.sample_reward(s);

        if (s == env.get_final_state()){
            ag.update_QV_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);

        ag.update_QV(s, a, rew, s_new);
        
        s = s_new;       
        i += 1;
    }
    return i-1;
};

void Experiment::more_runs(Agent &ag, Environment &env, int experiment_number, int algorithm, int exp_str){

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
    }
};

void Experiment::run_more_experiments(Agent &ag, Environment &env, int algorithm, int exploration_strategy){

    std::cout<<"\nRunning "<<n_experiments<<" experiments, each one of "<<n_runs<<" runs."<<std::endl;

    for (int exp_number=0; exp_number<n_experiments; exp_number++){
        //std::cout<<"\nExperiment number="<<exp_number<<std::endl;

            if (algorithm == 0 || algorithm == 1){
                ag.initialize_Q();
            } else if (algorithm == 2 ){
                ag.initialize_QA_QB();
            } else if (algorithm == 3 ){
                ag.initialize_Q();
                ag.initialize_V();
            }
            this->more_runs(ag, env, exp_number, algorithm, exploration_strategy);
               
    }
};

int* Experiment::compute_average(){

    std::cout<<"Computing the average of the steps the agent needs to find the final block. \nAverage is computed on the group of "<<n_experiments<<" experiments.\n\n";
    for (int i=0; i<n_runs; i++){
        average_steps[i] = 0;
        for (int j=0; j<n_experiments; j++){
            average_steps[i] += num_steps_each_experiment[j*n_runs+i]; // CONTROLLARE QUI
        }
        average_steps[i] = average_steps[i]/n_experiments;
        std::cout<<"average steps of run number "<<i<<"= "<<average_steps[i]<<std::endl;
    }
    return average_steps;
};

void Experiment::evaluation(Agent &ag, Environment &env, double epsilon, int algorithm){

    std::cout<<"\nEvaluation of the learnt policy with exploration rate of "<<epsilon<<std::endl;
    int s = 0, a = 0;
    std::vector<int> allow_act;

    ag.set_epsilon(epsilon);

    s = ag.get_initial_state();  

    int i=1;
    while (i){

        allow_act = env.allowed_actions(s);
        a = ag.epsilon_greedy(s, allow_act, algorithm); 
        std::cout<<"s="<<s<<", a="<<a<<std::endl; 

        if (s == env.get_final_state()){
            break;
        }
        s = env.next_state(s, a);

        i += 1;
    }
    std::cout<<"final number of steps="<<i<<std::endl;

};

void Experiment::single_run_SARSA_random(Agent &ag, Environment &env, int num_steps){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    int n = 0;
    int i = 1;
    int count_goals = 0;
    while (n < num_steps){

        s = env.random_start();
        //std::cout<<"new run from starting state "<<s<<std::endl;
        ag.set_initial_state(s);
        allow_act = env.allowed_actions(s);
        a = ag.epsilon_greedy(s, allow_act, 0);  // 0 == SARSA

        i=1;
        while (i){

            rew = env.sample_reward(s);
            if (s == env.get_final_state()){
                ag.update_Q_final(s, a, rew);
                count_goals += 1;
                break;
            }

            s_new = env.next_state(s, a);
            allow_act = env.allowed_actions(s_new);
            a_new = ag.epsilon_greedy(s_new, allow_act, 0);  // 0 == SARSA

            ag.update_Q_SARSA(s, a, rew, s_new, a_new);
            a = a_new;
            s = s_new;       
            i += 1;
            n += 1;
        }
    }
    //std::cout<<"num goals obtained = "<<count_goals<<std::endl;
};

void Experiment::single_run_QL_random(Agent &ag, Environment &env, int num_steps){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    int n = 0;
    int i = 1;
    int count_goals = 0;
    while (n < num_steps){

        s = env.random_start();
        ag.set_initial_state(s);
        allow_act = env.allowed_actions(s);
        a = ag.epsilon_greedy(s, allow_act, 1);  // 1 == Q_LEARNING

        i=1;
        while (i){

            rew = env.sample_reward(s);
            if (s == env.get_final_state()){
                ag.update_Q_final(s, a, rew);
                count_goals += 1;

                break;
            }

            s_new = env.next_state(s, a);
            allow_act = env.allowed_actions(s_new);
            ag.update_Q_Learning(s, a, rew, s_new, allow_act);

            a_new = ag.epsilon_greedy(s_new, allow_act, 1);  // 1 == Q_LEARNING
            
            a = a_new;
            s = s_new;       
            i += 1;
            n += 1;
        }
    }
};


/*void Experiment::single_run_Boltzmann(Agent &ag, Environment &env, double T){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    //std::cout<<"initial state="<<s<<std::endl; 
    allow_act = env.allowed_actions(s);
    
    a = ag.agent_Boltzmann_exploration(s, allow_act, T);  
    //std::cout<<"chosen initial action="<<a<<std::endl;
    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            //std::cout<<"s="<<s<<std::endl;
            ag.Update_Q_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //std::cout<<"s="<<s_new<<std::endl; 
        allow_act = env.allowed_actions(s_new);
        a_new = ag.agent_Boltzmann_exploration(s, allow_act, T); 
        ag.SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;       
        i += 1;
        //std::cout<<"chosen action="<<a<<std::endl;
    }
};

void Experiment::more_Boltzmann_exploration_runs(Agent &ag, Environment &env, double T){

    for (int run_number=0; run_number<n_runs; run_number++){
        this->single_run_Boltzmann(ag, env, T);
    }
};*/