#include "Experiment.h"
#include <iostream>
#include "stdlib.h"

Experiment::Experiment(int n_r){ 
    n_runs = n_r;
};

void Experiment::single_run(Agent &ag, Environment &env){

    int a = 0, a_new = 0;
    int s = 0, s_new = 0;
    double rew = 0;

    s = ag.get_initial_state();
    a = ag.agent_start();
    //std::cout<<"initial state="<<s<<std::endl; 
    //std::cout<<"initial action="<<a<<std::endl; 
    int i=1;
    while (i){

        rew = env.sample_reward(s);
        if (s == env.get_final_state()){
            //std::cout<<"s="<<s<<std::endl;
            ag.SARSA_final(s, a, rew);
            break;
        }

        s_new = env.next_state(s, a);
        a_new = ag.agent_step_epsilon_greedy(s_new);
        ag.SARSA(s, a, rew, s_new, a_new);
        a = a_new;
        s = s_new;       
        i += 1;
        //std::cout<<"s="<<s<<std::endl; 
        //std::cout<<"a="<<a<<std::endl; 
    }
};

void Experiment::more_runs(Agent &ag, Environment &env){

    for (int run_number=0; run_number<n_runs; run_number++){
        std::cout<<"\nRun="<<run_number<<std::endl;
        this->single_run(ag, env);
    }
};


void Experiment::evaluation(Agent &ag, Environment &env){

    int s = 0, a = 0;

    s = ag.get_initial_state();
    a = ag.agent_start();

    int i=1;
    while (i){

        if (s == env.get_final_state()){
            break;
        }
        s = env.next_state(s, a);
        a = ag.agent_step_epsilon_greedy(s);      

        std::cout<<"s="<<s<<", a="<<a<<std::endl;    
        i += 1;
    }

}