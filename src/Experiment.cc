#include "Experiment.h"
#include <iostream>
#include "stdlib.h"

Experiment::Experiment(int n_r, int n_exp){ 
    n_runs = n_r;
    n_experiments = n_exp;
    num_steps_runs = new int[n_runs];
    num_steps_each_experiment = new int[n_experiments*n_runs];
    average_steps = new int[n_runs];
};

Experiment::~Experiment(){
    delete[] num_steps_runs;
    delete[] num_steps_each_experiment;
};

int Experiment::single_run_SARSA(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act, 0);  // 0 == SARSA

    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            ag.update_Q_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);
        a_new = ag.agent_step_epsilon_greedy(s_new, allow_act, 0);

        ag.update_Q_SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;       
        i += 1;
    }

    return i-1;
};

int Experiment::single_run_QL(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act, 1);  // 1 == Q_LEARNING

    int i=1;
    while (i){
        //std::cout<<"s="<<s<<", a="<<a<<std::endl;
        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            ag.update_Q_final(s, a, rew);
            break;
        }
       /* if (s == 21){
            std::cout<<"available actions="<<std::endl;
            for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
                std::cout << *i << ' ';
            std::cout<<std::endl;
        }*/
        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);
        ag.update_Q_Learning(s, a, rew, s_new, allow_act);

        a_new = ag.agent_step_epsilon_greedy(s_new, allow_act, 1);  // 1 == Q_LEARNING
        
        a = a_new;
        s = s_new;       
        i += 1;
    }
    return i-1;
};

int Experiment::single_run_double_QL(Agent &ag, Environment &env){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state(); 
    allow_act = env.allowed_actions(s);

    int i=1;
    while (i){

        a = ag.agent_step_epsilon_greedy(s, allow_act, 1); // 1 == double Q leaning
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

int Experiment::single_run_QV(Agent &ag, Environment &env){

    int a = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state(); 

    int i=1;
    while (i){

        allow_act = env.allowed_actions(s);
        a = ag.agent_step_epsilon_greedy(s, allow_act, 3);
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

void Experiment::more_runs(Agent &ag, Environment &env, int experiment_number, int algorithm){

    for (int run_number=0; run_number<n_runs; run_number++){
        //std::cout<<"Run number="<<run_number<<std::endl;
        if (algorithm == 0 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_SARSA(ag, env);
        } else if (algorithm == 1 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_QL(ag, env);
        } else if (algorithm == 2 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_double_QL(ag, env);
        } else if (algorithm == 3 ){
            num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run_QV(ag, env);
        }
    }
};

void Experiment::more_experiments(Agent &ag, Environment &env, int algorithm){

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
            this->more_runs(ag, env, exp_number, algorithm);
               
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

void Experiment::evaluation_SARSA(Agent &ag, Environment &env, int algorithm){

    std::cout<<"\nEvaluation of the learnt policy"<<std::endl;
    int s = 0, a = 0;
    std::vector<int> allow_act;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act, 0); 
    std::cout<<"s="<<s<<", a="<<a<<std::endl;  
    int i=1;
    while (i){

        if (s == env.get_final_state()){
            break;
        }
        s = env.next_state(s, a);
        allow_act = env.allowed_actions(s);
        a = ag.agent_step_epsilon_greedy(s, allow_act, 0);     

        std::cout<<"s="<<s<<", a="<<a<<std::endl;    
        i += 1;
    }
    std::cout<<"final number of steps="<<i<<std::endl;

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