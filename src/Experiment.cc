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


void Experiment::single_run_Boltzmann(Agent &ag, Environment &env, double T){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;

    s = ag.get_initial_state();
    //std::cout<<"initial state="<<s<<std::endl; 
    allow_act = env.allowed_actions(s);
    /*std::cout<<"allowed actions:"<<std::endl; 
    for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
        std::cout << *i << ' ';
    std::cout<<std::endl;*/
    a = ag.agent_Boltzmann_exploration(s, allow_act, T);  
    //std::cout<<"chosen initial action="<<a<<std::endl;
    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            //std::cout<<"s="<<s<<std::endl;
            ag.SARSA_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        //std::cout<<"s="<<s_new<<std::endl; 
        allow_act = env.allowed_actions(s_new);
        /*for (std::vector<int>::const_iterator i = allow_act.begin(); i != allow_act.end(); ++i)
            std::cout << *i << ' ';
        std::cout<<std::endl;*/
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
};


int Experiment::single_run(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    std::vector<int> allow_act;
    double rew = 0;
    int num_steps = 0;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act); 

    int i=1;
    while (i){

        rew = env.sample_reward(s);

        if (s == env.get_final_state()){
            ag.SARSA_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        allow_act = env.allowed_actions(s_new);
        a_new = ag.agent_step_epsilon_greedy(s_new, allow_act);
        ag.SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;       
        i += 1;
        num_steps += 1;
    }
    return num_steps;
};

void Experiment::more_runs(Agent &ag, Environment &env, int experiment_number=0){

    for (int run_number=0; run_number<n_runs; run_number++){
        num_steps_each_experiment[experiment_number*n_runs+run_number] = single_run(ag, env);
    }

};

void Experiment::more_experiments(Agent &ag, Environment &env){

    std::cout<<"\nRunning "<<n_experiments<<" experiments, each one of "<<n_runs<<" runs."<<std::endl;
    for (int exp_number=0; exp_number<n_experiments; exp_number++){
        //std::cout<<"\nExperiment number="<<exp_number<<std::endl;
        ag.initialize_Q();
        this->more_runs(ag, env, exp_number);
        
    }
};

void Experiment::compute_average(){

    std::cout<<"Computing the average of the steps the agent needs to find the final block. \nAverage is computed on the group of "<<n_experiments<<" experiments.\n\n";
    for (int i=0; i<n_runs; i++){
        average_steps[i] = 0;
        for (int j=0; j<n_experiments; j++){
            average_steps[i] += num_steps_each_experiment[j*n_runs+i]; // CONTROLLARE QUI
        }
        average_steps[i] = average_steps[i]/n_experiments;
        std::cout<<"average steps of run number "<<i<<"= "<<average_steps[i]<<std::endl;
    }
};

void Experiment::evaluation(Agent &ag, Environment &env){

    int s = 0, a = 0;
    std::vector<int> allow_act;

    s = ag.get_initial_state();
    allow_act = env.allowed_actions(s);
    a = ag.agent_step_epsilon_greedy(s, allow_act); 
    std::cout<<"s="<<s<<", a="<<a<<std::endl;  
    int i=1;
    while (i){

        if (s == env.get_final_state()){
            break;
        }
        s = env.next_state(s, a);
        allow_act = env.allowed_actions(s);
        a = ag.agent_step_epsilon_greedy(s, allow_act);     

        std::cout<<"s="<<s<<", a="<<a<<std::endl;    
        i += 1;
    }

}